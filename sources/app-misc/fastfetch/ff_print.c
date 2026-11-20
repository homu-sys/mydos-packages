#include "fastfetch.h"

int ff_key_x(void) {
    return ffInstance.show_logo ? ffInstance.logo_width + 2 : 2;
}

int ff_value_x(void) {
    int x = ff_key_x();
    if (x < 26) x = 26;
    return x + 2;
}

void ff_print_key(const FFModuleArgs *args, uint8_t color) {
    ff_logo_print_line();
    int x = ff_key_x();
    if (args->icon[0] != '\0') {
        ff_put_text(args->icon, color, x, ffInstance.row);
        x += (int)ff_strlen(args->icon) + 1;
    }
    ff_put_text(args->key, color, x, ffInstance.row);
}

void ff_print_value(const char *value, uint8_t color, int x) {
    ff_put_text(value, color, x, ffInstance.row);
}

void ff_print_error(const FFModuleArgs *args, const char *message) {
    ff_put_text(args->key, FF_LIGHT_RED, ff_key_x(), ffInstance.row);
    ff_put_text(message, FF_LIGHT_RED, ff_value_x(), ffInstance.row);
}

void ff_print_format(const FFModuleArgs *args, const char *name, const char *value) {
    char formatted[FF_MODULE_ARGS_VALUE_SIZE];
    ff_parse_format(args->format, name, value, formatted, sizeof(formatted));
    ff_print_value(formatted, args->color, ff_value_x());
}

static int ff_field_equals(const char *format, unsigned int start,
                          unsigned int length, const char *expected) {
    unsigned int expected_length = ff_strlen(expected);
    if (length != expected_length) return 0;
    for (unsigned int i = 0; i < length; i++) {
        char actual = format[start + i];
        char wanted = expected[i];
        if (actual >= 'A' && actual <= 'Z') actual = (char)(actual + 32);
        if (wanted >= 'A' && wanted <= 'Z') wanted = (char)(wanted + 32);
        if (actual != wanted) return 0;
    }
    return 1;
}

void ff_parse_format(const char *format, const char *name, const char *value,
                     char *out, unsigned int capacity) {
    unsigned int out_index = 0;
    unsigned int index = 0;
    if (capacity == 0) return;

    while (format[index] != '\0' && out_index + 1 < capacity) {
        if (format[index] == '{') {
            if (format[index + 1] == '{') {
                out[out_index++] = '{';
                index += 2;
                continue;
            }
            unsigned int end = index + 1;
            while (format[end] != '\0' && format[end] != '}') end++;
            if (format[end] != '}') {
                out[out_index++] = format[index++];
                continue;
            }
            unsigned int field_length = end - index - 1;
            const char *replacement = "";
            if (field_length == 0 || (field_length == 1 && format[index + 1] == '0') ||
                ff_field_equals(format, index + 1, field_length, "value") ||
                ff_field_equals(format, index + 1, field_length, "result")) {
                replacement = value;
            } else if (ff_field_equals(format, index + 1, field_length, "name") ||
                       ff_field_equals(format, index + 1, field_length, "user-name") ||
                       ff_field_equals(format, index + 1, field_length, "host-name")) {
                replacement = name;
            }
            unsigned int replace_index = 0;
            while (replacement[replace_index] != '\0' && out_index + 1 < capacity) {
                out[out_index++] = replacement[replace_index++];
            }
            index = end + 1;
            continue;
        }
        if (format[index] == '}' && format[index + 1] == '}') {
            out[out_index++] = '}';
            index += 2;
            continue;
        }
        out[out_index++] = format[index++];
    }
    out[out_index] = '\0';
}
