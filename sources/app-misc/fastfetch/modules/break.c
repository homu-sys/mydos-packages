#include "../fastfetch.h"

void ff_module_init_break(FFModuleArgs *args) {
    ff_strcpy(args->key, "Break", sizeof(args->key));
    ff_strcpy(args->icon, "", sizeof(args->icon));
    ff_strcpy(args->format, "", sizeof(args->format));
    args->color = FF_WHITE;
}

void ff_module_print_break(FFModuleArgs *args) {
    (void)args;
    ff_logo_print_line();
}
