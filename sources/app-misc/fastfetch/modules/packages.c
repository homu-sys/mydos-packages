#include "../fastfetch.h"

void ff_module_init_packages(FFModuleArgs *args) {
    ff_strcpy(args->key, "Packages", sizeof(args->key));
    ff_strcpy(args->icon, "+", sizeof(args->icon));
    ff_strcpy(args->format, "{count} (flint + gpkg)", sizeof(args->format));
    args->color = FF_LIGHT_GREEN;
}

void ff_module_print_packages(FFModuleArgs *args) {
    ff_print_key(args, args->color);
    ff_print_value("flint + gpkg", args->color, ff_value_x());
}
