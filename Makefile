.DEFAULT_GOAL := all

MYDOS_DIR ?= /home/homu/MyDOS
CC ?= gcc
ZSTD ?= zstd
BUILD := build
BUILD_DIR := $(BUILD)
USER_LD := $(MYDOS_DIR)/user.ld
CPPFLAGS := -Iinclude
CFLAGS := -m32 -ffreestanding -fno-pie -fno-stack-protector -Wall -Wextra -mno-sse -mno-sse2 -mfpmath=387
SHELL_ELF := $(BUILD_DIR)/bin/mydos-shell.elf
FASTFETCH_ELF := $(BUILD_DIR)/bin/mydos-fastfetch.elf
SHELL_PKG := packages/app-shells/mydos-shell-1.0.0.gpkg.tar
FASTFETCH_PKG := packages/app-misc/mydos-fastfetch-1.0.0.gpkg.tar

.PHONY: all clean publish

all: $(SHELL_PKG) $(FASTFETCH_PKG) Packages

$(BUILD_DIR)/bin/mydos-shell.elf: sources/app-shells/mydos-shell/mydos-shell.c include/mydos/user_api.h $(USER_LD)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -nostdlib -static -Wl,-T,$(USER_LD) $< -o $@

$(BUILD_DIR)/bin/mydos-fastfetch.elf: sources/app-misc/mydos-fastfetch/mydos-fastfetch.c include/mydos/user_api.h $(USER_LD)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -nostdlib -static -Wl,-T,$(USER_LD) $< -o $@

$(BUILD_DIR)/gpkg/mydos-shell/image.tar.zst: $(SHELL_ELF)
	mkdir -p $(BUILD_DIR)/gpkg/mydos-shell/image/usr/bin
	cp $(SHELL_ELF) $(BUILD_DIR)/gpkg/mydos-shell/image/usr/bin/mydos-shell.elf
	tar -C $(BUILD_DIR)/gpkg/mydos-shell -cf $(BUILD_DIR)/gpkg/mydos-shell/image.tar image
	$(ZSTD) -q -19 -f -o $@ $(BUILD_DIR)/gpkg/mydos-shell/image.tar

$(BUILD_DIR)/gpkg/mydos-fastfetch/image.tar.zst: $(FASTFETCH_ELF)
	mkdir -p $(BUILD_DIR)/gpkg/mydos-fastfetch/image/usr/bin
	cp $(FASTFETCH_ELF) $(BUILD_DIR)/gpkg/mydos-fastfetch/image/usr/bin/mydos-fastfetch.elf
	tar -C $(BUILD_DIR)/gpkg/mydos-fastfetch -cf $(BUILD_DIR)/gpkg/mydos-fastfetch/image.tar image
	$(ZSTD) -q -19 -f -o $@ $(BUILD_DIR)/gpkg/mydos-fastfetch/image.tar

$(SHELL_PKG): $(BUILD_DIR)/gpkg/mydos-shell/image.tar.zst
	mkdir -p $(dir $@)
	tar -C $(BUILD_DIR)/gpkg/mydos-shell -cf $@ image.tar.zst

$(FASTFETCH_PKG): $(BUILD_DIR)/gpkg/mydos-fastfetch/image.tar.zst
	mkdir -p $(dir $@)
	tar -C $(BUILD_DIR)/gpkg/mydos-fastfetch -cf $@ image.tar.zst

Packages: $(SHELL_PKG) $(FASTFETCH_PKG)
	printf '%s\n' \
		'CPV: app-shells/mydos-shell-1.0.0' \
		'PATH: packages/app-shells/mydos-shell-1.0.0.gpkg.tar' \
		'DESCRIPTION: Interactive MyDOS package-repository shell.' \
		'DESCRIPTION_PT: Shell interativo do repositorio de pacotes MyDOS.' \
		'DESCRIPTION_DE: Interaktive MyDOS Paket-Repository-Shell.' \
		'HOMEPAGE: https://github.com/homu-sys/mydos-packages' \
		'LICENSE: MIT' \
		'' \
		'CPV: app-misc/mydos-fastfetch-1.0.0' \
		'PATH: packages/app-misc/mydos-fastfetch-1.0.0.gpkg.tar' \
		'DESCRIPTION: Small system information tool for MyDOS.' \
		'DESCRIPTION_PT: Pequena ferramenta de informacoes do sistema para MyDOS.' \
		'DESCRIPTION_DE: Kleines Systeminformationswerkzeug fuer MyDOS.' \
		'HOMEPAGE: https://github.com/homu-sys/mydos-packages' \
		'LICENSE: MIT' \
		'' > $@

publish: all
	git add Packages packages sources include Makefile
	git commit -m "Build MyDOS shell and fastfetch packages" || true
	git push -u origin HEAD

clean:
	rm -rf $(BUILD_DIR)
