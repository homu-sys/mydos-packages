#include "../fastfetch.h"

void ff_module_init_uptime(FFModuleArgs *args) {
    ff_strcpy(args->key, "Uptime", sizeof(args->key));
    ff_strcpy(args->icon, "^", sizeof(args->icon));
    ff_strcpy(args->format, "{uptime}", sizeof(args->format));
    args->color = FF_LIGHT_GREY;
}

void ff_module_print_uptime(FFModuleArgs *args) {
    const char *uptime = ffInstance.api->getenv("UPTIME");
    ff_print_key(args, args->color);
    ff_print_format(args, "uptime", uptime != 0 && uptime[0] != '\0' ? uptime : "running");
}
