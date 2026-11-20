#include "../fastfetch.h"

static const uint8_t ff_colors[] = {
    FF_BLACK, FF_BLUE, FF_GREEN, FF_CYAN, FF_RED, FF_MAGENTA, FF_BROWN, FF_LIGHT_GREY,
    FF_DARK_GREY, FF_LIGHT_BLUE, FF_LIGHT_GREEN, FF_LIGHT_CYAN, FF_LIGHT_RED,
    FF_LIGHT_MAGENTA, FF_YELLOW, FF_WHITE
};

void ff_module_init_colors(FFModuleArgs *args) {
    ff_strcpy(args->key, "Colors", sizeof(args->key));
    ff_strcpy(args->icon, "*", sizeof(args->icon));
    ff_strcpy(args->format, "", sizeof(args->format));
    args->color = FF_WHITE;
}

void ff_module_print_colors(FFModuleArgs *args) {
    int x = ff_value_x();
    ff_print_key(args, FF_WHITE);
    for (unsigned int i = 0; i < sizeof(ff_colors) / sizeof(ff_colors[0]); i++) {
        ff_put_text("###", ff_colors[i], x + (int)i * 3, ffInstance.row);
    }
}
