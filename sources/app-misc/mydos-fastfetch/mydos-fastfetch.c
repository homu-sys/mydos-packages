#include "mydos/user_api.h"

#define COLOR_BLUE 0x01u
#define COLOR_CYAN 0x03u
#define COLOR_WHITE 0x0Fu
#define COLOR_LIGHT_GREY 0x07u
#define COLOR_LIGHT_CYAN 0x0Bu
#define COLOR_LIGHT_GREEN 0x0Au
#define COLOR_YELLOW 0x0Eu
#define COLOR_RED 0x04u

static void put_text(const mydos_user_api_t *api, const char *text,
                     uint8_t color, int x, int y) {
    api->print(text, color, x, y);
}

static void put_line(const mydos_user_api_t *api, const char *label,
                     const char *value, uint8_t color, int y) {
    put_text(api, label, color, 0, y);
    put_text(api, value, COLOR_WHITE, 20, y);
}

int main(int argc, char **argv, const mydos_user_api_t *api) {
    (void)argc;
    (void)argv;

    if (api->version < MYDOS_USER_API_VERSION) {
        put_text(api, "mydos-fastfetch: kernel API is too old", COLOR_RED, 0, 0);
        return 1;
    }

    int row = api->cursor_y();
    api->set_cursor_y(row);
    api->run_command("clear", &row);
    row = api->cursor_y();

    put_text(api, "      ___  ___  ____    _ ", COLOR_LIGHT_CYAN, 0, row);
    api->scroll(&row);
    put_text(api, "     |  \\/  ||  _ \\  / \\ ", COLOR_LIGHT_CYAN, 0, row);
    api->scroll(&row);
    put_text(api, "     | |\\/| || | | |/ _ \\", COLOR_LIGHT_CYAN, 0, row);
    api->scroll(&row);
    put_text(api, "     |_|  |_||_| |_/_/ \\_\\", COLOR_LIGHT_CYAN, 0, row);
    api->scroll(&row);
    put_text(api, "+-------------------------------+", COLOR_BLUE, 0, row);
    api->scroll(&row);

    put_line(api, "User", api->username(), COLOR_LIGHT_GREEN, row);
    api->scroll(&row);
    put_line(api, "Host", api->hostname(), COLOR_YELLOW, row);
    api->scroll(&row);
    put_line(api, "OS", "MyDOS", COLOR_LIGHT_CYAN, row);
    api->scroll(&row);
    put_line(api, "Shell", "mydos-shell 1.0.0", COLOR_WHITE, row);
    api->scroll(&row);
    put_line(api, "License", "MIT", COLOR_LIGHT_GREY, row);
    api->scroll(&row);
    put_line(api, "Repository", "homu-sys/mydos-packages", COLOR_LIGHT_GREY, row);
    api->scroll(&row);
    put_text(api, "+-------------------------------+", COLOR_BLUE, 0, row);
    api->scroll(&row);

    for (unsigned int i = 0; i < 8; i++) {
        put_text(api, "[]", COLOR_LIGHT_CYAN, (int)i * 2, row);
    }
    api->scroll(&row);
    return 0;
}
