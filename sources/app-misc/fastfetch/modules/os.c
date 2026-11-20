#include "../fastfetch.h"

void ff_module_init_os(FFModuleArgs *args) {
    ff_strcpy(args->key, "OS", sizeof(args->key));
    ff_strcpy(args->icon, "~", sizeof(args->icon));
    ff_strcpy(args->format, "{name}", sizeof(args->format));
    args->color = FF_LIGHT_GREEN;
}

void ff_module_print_os(FFModuleArgs *args) {
    const char *version = ffInstance.api->getenv("OS_VERSION");
    char value[FF_MODULE_ARGS_VALUE_SIZE];
    ff_strcpy(value, "MyDOS", sizeof(value));
    if (version != 0 && version[0] != '\0' && ff_strlen(value) + ff_strlen(version) + 2 < sizeof(value)) {
        unsigned int length = ff_strlen(value);
        value[length++] = ' ';
        value[length] = '\0';
        ff_strcpy(value + length, version, sizeof(value) - length);
    }
    ff_print_key(args, args->color);
    ff_print_format(args, "os", value);
}
