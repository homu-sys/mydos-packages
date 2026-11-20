#include "../fastfetch.h"

void ff_module_init_kernel(FFModuleArgs *args) {
    ff_strcpy(args->key, "Kernel", sizeof(args->key));
    ff_strcpy(args->icon, "#", sizeof(args->icon));
    ff_strcpy(args->format, "{name} {version}", sizeof(args->format));
    args->color = FF_LIGHT_BLUE;
}

void ff_module_print_kernel(FFModuleArgs *args) {
    ff_print_key(args, args->color);
    ff_print_format(args, "kernel", "MyDOS i386");
}
