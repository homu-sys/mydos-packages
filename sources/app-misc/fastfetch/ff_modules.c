#include "fastfetch.h"

FFModuleBaseInfo *ffModuleInfos[26];

static void ff_register(FFModuleBaseInfo *module) {
    if (module == 0 || module->name == 0 || module->name[0] == '\0') return;
    char first = module->name[0];
    if (first >= 'a' && first <= 'z') first = (char)(first - 32);
    if (first < 'A' || first > 'Z') return;
    ffModuleInfos[first - 'A'] = module;
}

void ff_modules_init(void) {
    static FFModuleBaseInfo title = {"Title", ff_module_init_title, ff_module_print_title, 0};
    static FFModuleBaseInfo separator = {"Separator", ff_module_init_separator, ff_module_print_separator, 0};
    static FFModuleBaseInfo os = {"OS", ff_module_init_os, ff_module_print_os, 0};
    static FFModuleBaseInfo host = {"Host", ff_module_init_host, ff_module_print_host, 0};
    static FFModuleBaseInfo kernel = {"Kernel", ff_module_init_kernel, ff_module_print_kernel, 0};
    static FFModuleBaseInfo shell = {"Shell", ff_module_init_shell, ff_module_print_shell, 0};
    static FFModuleBaseInfo uptime = {"Uptime", ff_module_init_uptime, ff_module_print_uptime, 0};
    static FFModuleBaseInfo packages = {"Packages", ff_module_init_packages, ff_module_print_packages, 0};
    static FFModuleBaseInfo break_module = {"Break", ff_module_init_break, ff_module_print_break, 0};
    static FFModuleBaseInfo colors = {"Colors", ff_module_init_colors, ff_module_print_colors, 0};

    ff_register(&title);
    ff_register(&separator);
    ff_register(&os);
    ff_register(&host);
    ff_register(&kernel);
    ff_register(&shell);
    ff_register(&uptime);
    ff_register(&packages);
    ff_register(&break_module);
    ff_register(&colors);
}

const FFModuleBaseInfo *ff_find_module(const char *name) {
    if (name == 0 || name[0] == '\0') return 0;
    char first = name[0];
    if (first >= 'a' && first <= 'z') first = (char)(first - 32);
    if (first < 'A' || first > 'Z') return 0;

    FFModuleBaseInfo *module = ffModuleInfos[first - 'A'];
    if (module != 0 && ff_stricmp(module->name, name) == 0) return module;

    for (unsigned int i = 0; i < 26; i++) {
        module = ffModuleInfos[i];
        if (module != 0 && ff_stricmp(module->name, name) == 0) return module;
    }
    return 0;
}
