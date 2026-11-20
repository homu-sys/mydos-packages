#include "../fastfetch.h"

void ff_module_init_separator(FFModuleArgs *args) {
    ff_strcpy(args->key, "Separator", sizeof(args->key));
    ff_strcpy(args->icon, "-", sizeof(args->icon));
    ff_strcpy(args->format, "------------------------------", sizeof(args->format));
    args->color = FF_BLUE;
}

void ff_module_print_separator(FFModuleArgs *args) {
    char line[64];
    unsigned int index = 0;
    while (index + 1 < sizeof(line) && index < 40) {
        line[index++] = '-';
    }
    line[index] = '\0';
    ff_print_key(args, args->color);
    ff_print_value(line, args->color, ff_key_x() + ff_strlen(args->key) + 2);
}
