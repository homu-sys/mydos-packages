#include "../fastfetch.h"

void ff_module_init_shell(FFModuleArgs *args) {
    ff_strcpy(args->key, "Shell", sizeof(args->key));
    ff_strcpy(args->icon, "$", sizeof(args->icon));
    ff_strcpy(args->format, "{name} {version}", sizeof(args->format));
    args->color = FF_LIGHT_MAGENTA;
}

void ff_module_print_shell(FFModuleArgs *args) {
    const char *shell = ffInstance.api->getenv("SHELL");
    ff_print_key(args, args->color);
    ff_print_format(args, "shell", shell != 0 && shell[0] != '\0' ? shell : "mydos-shell 1.0.0");
}
