#include "mydos/user_api.h"

#define COLOR_WHITE 0x0Fu
#define COLOR_LIGHT_GREY 0x07u
#define COLOR_LIGHT_CYAN 0x0Bu
#define COLOR_LIGHT_GREEN 0x0Au
#define COLOR_YELLOW 0x0Eu
#define COLOR_RED 0x04u
#define LINE_MAX 128

static unsigned int text_length(const char *text) {
    unsigned int length = 0;
    while (text[length] != '\0') {
        length++;
    }
    return length;
}

static int text_equal(const char *left, const char *right) {
    while (*left != '\0' && *right != '\0') {
        if (*left != *right) {
            return 0;
        }
        left++;
        right++;
    }
    return *left == '\0' && *right == '\0';
}

static void put_text(const mydos_user_api_t *api, const char *text,
                     uint8_t color, int x, int y) {
    api->print(text, color, x, y);
}

static void render_prompt(const mydos_user_api_t *api, int *x, int *y) {
    const char *user = api->username();
    const char *host = api->hostname();

    put_text(api, "[ ", COLOR_LIGHT_CYAN, *x, *y);
    *x += 2;
    put_text(api, user, COLOR_LIGHT_GREEN, *x, *y);
    *x += (int)text_length(user);
    put_text(api, " @ ", COLOR_LIGHT_CYAN, *x, *y);
    *x += 3;
    put_text(api, host, COLOR_YELLOW, *x, *y);
    *x += (int)text_length(host);
    put_text(api, " ] $ ", COLOR_WHITE, *x, *y);
    *x += 5;
}

int main(int argc, char **argv, const mydos_user_api_t *api) {
    (void)argc;
    (void)argv;

    if (api->version < MYDOS_USER_API_VERSION) {
        put_text(api, "mydos-shell: kernel API is too old", COLOR_RED, 0, 0);
        return 1;
    }

    char line[LINE_MAX];
    unsigned int length = 0;
    int y = api->cursor_y();
    int x = 0;

    render_prompt(api, &x, &y);

    for (;;) {
        char character = api->getchar();

        if (character == '\b') {
            if (length > 0) {
                length--;
                line[length] = '\0';
                x--;
                put_text(api, " ", COLOR_WHITE, x, y);
            }
            continue;
        }

        if (character == '\n') {
            line[length] = '\0';
            api->scroll(&y);
            api->set_cursor_y(y);

            if (length > 0 && text_equal(line, "exit")) {
                return 0;
            }
            if (length > 0) {
                api->run_command(line, &y);
            }

            y = api->cursor_y();
            x = 0;
            length = 0;
            render_prompt(api, &x, &y);
            continue;
        }

        if (character >= 32 && character <= 126 && length + 1 < sizeof(line)) {
            char text[2] = {character, '\0'};
            line[length++] = character;
            line[length] = '\0';
            put_text(api, text, COLOR_WHITE, x, y);
            x++;
        }
    }
}
