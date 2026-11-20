#include "../fastfetch.h"

void ff_module_init_title(FFModuleArgs *args) {
    ff_strcpy(args->key, "Title", sizeof(args->key));
    ff_strcpy(args->icon, ">", sizeof(args->icon));
    ff_strcpy(args->format, "{user-name}@{host-name}", sizeof(args->format));
    args->color = FF_LIGHT_CYAN;
}

void ff_module_print_title(FFModuleArgs *args) {
    char value[FF_MODULE_ARGS_VALUE_SIZE];
    const char *user = ffInstance.api->username();
    const char *host = ffInstance.api->hostname();

    value[0] = '\0';
    ff_strcpy(value, user != 0 ? user : "unknown", sizeof(value));
    unsigned int length = ff_strlen(value);
    if (length + 1 < sizeof(value)) {
        value[length++] = '@';
        value[length] = '\0';
    }
    ff_strcpy(value + length, host != 0 ? host : "unknown", sizeof(value) - length);

    ff_print_key(args, args->color);
    ff_print_format(args, "title", value);
}
