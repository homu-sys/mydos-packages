#include "fastfetch.h"

static const char *ffLogoLines[] = {
    "  __  __    _  ____  _____ _____  ",
    " |  \\/  |  / \\|  _ \\| ____|_   _| ",
    " | |\\/| | / _ \\| | | |  _|   | |   ",
    " | |  | |/ ___ \\| |_| | |___  | |   ",
    " |_|  |_/_/   \\_\\____/|_____| |_|   "
};

static const uint8_t ffLogoColors[] = {
    FF_LIGHT_CYAN,
    FF_LIGHT_BLUE,
    FF_LIGHT_GREEN,
    FF_YELLOW,
    FF_LIGHT_MAGENTA
};

static unsigned int ffLogoLineCount(void) {
    return sizeof(ffLogoLines) / sizeof(ffLogoLines[0]);
}

void ff_logo_set_width(int width) {
    ffInstance.logo_width = width;
}

void ff_logo_print_line(void) {
    if (!ffInstance.show_logo || ffInstance.logo_row < 0) return;
    if ((unsigned int)ffInstance.logo_row >= ffLogoLineCount()) return;
    ff_put_text(ffLogoLines[ffInstance.logo_row],
                ffLogoColors[ffInstance.logo_row], 0, ffInstance.row);
    ffInstance.logo_row++;
}

void ff_logo_finish(void) {
    while (ffInstance.show_logo &&
           (unsigned int)ffInstance.logo_row < ffLogoLineCount()) {
        int row = ffInstance.row;
        ff_logo_print_line();
        ffInstance.row = row;
        ff_scroll();
    }
}
