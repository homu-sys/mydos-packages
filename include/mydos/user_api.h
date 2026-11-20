#ifndef MYDOS_USER_API_H
#define MYDOS_USER_API_H

#include <stdint.h>

#define MYDOS_USER_API_VERSION 3u

typedef void (*mydos_print_fn)(const char *message, uint8_t color, int x, int y);
typedef void (*mydos_scroll_fn)(int *cursor_y);
typedef char (*mydos_getchar_fn)(void);
typedef int (*mydos_run_command_fn)(const char *command, int *cursor_y);
typedef const char *(*mydos_getenv_fn)(const char *name);
typedef int (*mydos_cursor_fn)(void);
typedef void (*mydos_set_cursor_fn)(int cursor_y);
typedef const char *(*mydos_string_fn)(void);

typedef struct {
    uint32_t version;
    mydos_print_fn print;
    mydos_scroll_fn scroll;
    mydos_getchar_fn getchar;
    mydos_run_command_fn run_command;
    mydos_getenv_fn getenv;
    mydos_string_fn hostname;
    mydos_string_fn username;
    mydos_cursor_fn cursor_y;
    mydos_set_cursor_fn set_cursor_y;
} mydos_user_api_t;

typedef int (*mydos_user_entry_t)(int argc, char **argv,
                                  const mydos_user_api_t *api);

#endif
