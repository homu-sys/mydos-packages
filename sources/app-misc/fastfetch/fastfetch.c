#include "fastfetch.h"

FFInstance ffInstance;

static void ff_print_line(const char *text, uint8_t color) {
    ff_put_text(text, color, 0, ffInstance.row);
    ff_scroll();
}

static void ff_usage(void) {
    ff_print_line("fastfetch " FF_VERSION, FF_LIGHT_CYAN);
    ff_print_line("Usage: fastfetch [--version] [--help] [--clear] [--no-logo]", FF_WHITE);
    ff_print_line("                 [--structure Module:Module:...]", FF_WHITE);
    ff_print_line("Modules: Title Separator OS Host Kernel Shell Uptime Packages Break Colors", FF_LIGHT_GREY);
}

static void ff_run_structure(void) {
    const char *cursor = ffInstance.structure;

    while (*cursor != '\0') {
        char name[48];
        unsigned int length = 0;

        while (*cursor == ':' || *cursor == ' ') cursor++;
        while (*cursor != '\0' && *cursor != ':' && length + 1 < sizeof(name)) {
            name[length++] = *cursor++;
        }
        name[length] = '\0';
        while (*cursor != '\0' && *cursor != ':') cursor++;
        if (*cursor == ':') cursor++;

        if (length == 0) continue;

        const FFModuleBaseInfo *module = ff_find_module(name);
        if (module == 0) {
            char message[64];
            ff_strcpy(message, "no implementation for ", sizeof(message));
            ff_strcpy(message + ff_strlen(message), name, sizeof(message) - ff_strlen(message));
            ff_print_line(message, FF_LIGHT_RED);
            continue;
        }

        FFModuleArgs args;
        args.key[0] = '\0';
        args.icon[0] = '\0';
        args.format[0] = '\0';
        args.color = FF_WHITE;

        if (module->init != 0) module->init(&args);
        if (module->print != 0) module->print(&args);
        if (module->destroy != 0) module->destroy(&args);
        ff_scroll();
    }
}

static void ff_parse_arguments(int argc, char **argv) {
    const char *environment_structure = ffInstance.api->getenv("FASTFETCH_STRUCTURE");
    if (environment_structure != 0 && environment_structure[0] != '\0') {
        ff_strcpy(ffInstance.structure, environment_structure, sizeof(ffInstance.structure));
    } else {
        ff_strcpy(ffInstance.structure,
                  "Title:Separator:OS:Host:Kernel:Shell:Uptime:Packages:Break:Colors",
                  sizeof(ffInstance.structure));
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i] == 0) continue;
        if (ff_strcmp(argv[i], "--version") == 0) {
            ff_print_line("fastfetch " FF_VERSION, FF_LIGHT_CYAN);
            return;
        }
        if (ff_strcmp(argv[i], "--help") == 0) {
            ff_usage();
            return;
        }
        if (ff_strcmp(argv[i], "--clear") == 0) {
            ffInstance.clear_screen = 1;
            continue;
        }
        if (ff_strcmp(argv[i], "--no-logo") == 0) {
            ffInstance.show_logo = 0;
            continue;
        }
        if (ff_strcmp(argv[i], "--structure") == 0 && i + 1 < argc && argv[i + 1] != 0) {
            ff_strcpy(ffInstance.structure, argv[i + 1], sizeof(ffInstance.structure));
            i++;
            continue;
        }
        char message[96];
        ff_strcpy(message, "fastfetch: unknown option ", sizeof(message));
        ff_strcpy(message + ff_strlen(message), argv[i], sizeof(message) - ff_strlen(message));
        ff_print_line(message, FF_LIGHT_RED);
        return;
    }

    if (ffInstance.clear_screen) {
        int row = ffInstance.row;
        ffInstance.api->run_command("clear", &row);
        ffInstance.row = row;
    }

    ff_modules_init();
    ff_logo_set_width(35);
    ff_run_structure();
    ff_logo_finish();
}

int main(int argc, char **argv, const mydos_user_api_t *api) {
    ffInstance.api = api;
    ffInstance.row = api->cursor_y();
    ffInstance.logo_width = 0;
    ffInstance.logo_height = 5;
    ffInstance.logo_row = 0;
    ffInstance.show_logo = 1;
    ffInstance.clear_screen = 0;
    ffInstance.structure[0] = '\0';

    if (api->version < MYDOS_USER_API_VERSION) {
        ff_put_text("fastfetch: kernel API is too old", FF_RED, 0, 0);
        return 1;
    }

    ff_parse_arguments(argc, argv);
    return 0;
}
