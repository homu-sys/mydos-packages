#include "../fastfetch.h"

void ff_module_init_host(FFModuleArgs *args) {
    ff_strcpy(args->key, "Host", sizeof(args->key));
    ff_strcpy(args->icon, "@", sizeof(args->icon));
    ff_strcpy(args->format, "{host-name}", sizeof(args->format));
    args->color = FF_YELLOW;
}

void ff_module_print_host(FFModuleArgs *args) {
    const char *host = ffInstance.api->hostname();
    ff_print_key(args, args->color);
    ff_print_format(args, "host", host != 0 ? host : "unknown");
}
