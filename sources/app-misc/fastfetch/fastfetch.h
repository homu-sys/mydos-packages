#ifndef MYDOS_FASTFETCH_H
#define MYDOS_FASTFETCH_H

#include "mydos/user_api.h"

#define FF_VERSION "2.71.0-mydos"
#define FF_UPSTREAM_COMMIT "216d3b24f32871da92c630e19d49c67d7b5ca7ef"

#define FF_BLACK 0x00u
#define FF_BLUE 0x01u
#define FF_GREEN 0x02u
#define FF_CYAN 0x03u
#define FF_RED 0x04u
#define FF_MAGENTA 0x05u
#define FF_BROWN 0x06u
#define FF_LIGHT_GREY 0x07u
#define FF_DARK_GREY 0x08u
#define FF_LIGHT_BLUE 0x09u
#define FF_LIGHT_GREEN 0x0Au
#define FF_LIGHT_CYAN 0x0Bu
#define FF_LIGHT_RED 0x0Cu
#define FF_LIGHT_MAGENTA 0x0Du
#define FF_YELLOW 0x0Eu
#define FF_WHITE 0x0Fu

#define FF_MODULE_ARGS_KEY_SIZE 24
#define FF_MODULE_ARGS_ICON_SIZE 8
#define FF_MODULE_ARGS_FORMAT_SIZE 128
#define FF_MODULE_ARGS_VALUE_SIZE 192
#define FF_STRUCTURE_SIZE 320

typedef struct {
    char key[FF_MODULE_ARGS_KEY_SIZE];
    char icon[FF_MODULE_ARGS_ICON_SIZE];
    char format[FF_MODULE_ARGS_FORMAT_SIZE];
    uint8_t color;
} FFModuleArgs;

typedef struct {
    const mydos_user_api_t *api;
    int row;
    int logo_width;
    int logo_height;
    int logo_row;
    int show_logo;
    int clear_screen;
    char structure[FF_STRUCTURE_SIZE];
} FFInstance;

typedef struct FFModuleBaseInfo {
    const char *name;
    void (*init)(FFModuleArgs *args);
    void (*print)(FFModuleArgs *args);
    void (*destroy)(FFModuleArgs *args);
} FFModuleBaseInfo;

extern FFInstance ffInstance;
extern FFModuleBaseInfo *ffModuleInfos[26];

unsigned int ff_strlen(const char *text);
int ff_strcmp(const char *left, const char *right);
int ff_stricmp(const char *left, const char *right);
void ff_strcpy(char *destination, const char *source, unsigned int capacity);
void ff_uint_to_str(unsigned int value, char *out, unsigned int capacity);
void ff_put_text(const char *text, uint8_t color, int x, int y);
void ff_scroll(void);
void ff_next_line(void);

const FFModuleBaseInfo *ff_find_module(const char *name);
void ff_modules_init(void);
void ff_logo_print_line(void);
void ff_logo_finish(void);
void ff_logo_set_width(int width);
int ff_key_x(void);
int ff_value_x(void);
void ff_print_key(const FFModuleArgs *args, uint8_t color);
void ff_print_value(const char *value, uint8_t color, int x);
void ff_print_error(const FFModuleArgs *args, const char *message);
void ff_print_format(const FFModuleArgs *args, const char *name, const char *value);
void ff_parse_format(const char *format, const char *name, const char *value,
                     char *out, unsigned int capacity);

void ff_module_init_title(FFModuleArgs *args);
void ff_module_print_title(FFModuleArgs *args);
void ff_module_init_separator(FFModuleArgs *args);
void ff_module_print_separator(FFModuleArgs *args);
void ff_module_init_os(FFModuleArgs *args);
void ff_module_print_os(FFModuleArgs *args);
void ff_module_init_host(FFModuleArgs *args);
void ff_module_print_host(FFModuleArgs *args);
void ff_module_init_kernel(FFModuleArgs *args);
void ff_module_print_kernel(FFModuleArgs *args);
void ff_module_init_shell(FFModuleArgs *args);
void ff_module_print_shell(FFModuleArgs *args);
void ff_module_init_uptime(FFModuleArgs *args);
void ff_module_print_uptime(FFModuleArgs *args);
void ff_module_init_packages(FFModuleArgs *args);
void ff_module_print_packages(FFModuleArgs *args);
void ff_module_init_break(FFModuleArgs *args);
void ff_module_print_break(FFModuleArgs *args);
void ff_module_init_colors(FFModuleArgs *args);
void ff_module_print_colors(FFModuleArgs *args);

#endif
