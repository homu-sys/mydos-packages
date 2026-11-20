#include "fastfetch.h"

unsigned int ff_strlen(const char *text) {
    unsigned int length = 0;
    while (text[length] != '\0') length++;
    return length;
}

int ff_strcmp(const char *left, const char *right) {
    while (*left != '\0' && *left == *right) {
        left++;
        right++;
    }
    return (unsigned char)*left - (unsigned char)*right;
}

static char ff_lower(char value) {
    if (value >= 'A' && value <= 'Z') return (char)(value + 32);
    return value;
}

int ff_stricmp(const char *left, const char *right) {
    while (*left != '\0' && ff_lower(*left) == ff_lower(*right)) {
        left++;
        right++;
    }
    return ff_lower(*left) - ff_lower(*right);
}

void ff_strcpy(char *destination, const char *source, unsigned int capacity) {
    unsigned int index = 0;
    if (capacity == 0) return;
    while (source[index] != '\0' && index + 1 < capacity) {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
}

void ff_uint_to_str(unsigned int value, char *out, unsigned int capacity) {
    char reverse[16];
    unsigned int length = 0;
    if (capacity == 0) return;
    if (value == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    while (value != 0 && length < sizeof(reverse)) {
        reverse[length++] = (char)('0' + value % 10);
        value /= 10;
    }
    unsigned int index = 0;
    while (length > 0 && index + 1 < capacity) {
        out[index++] = reverse[--length];
    }
    out[index] = '\0';
}

void ff_put_text(const char *text, uint8_t color, int x, int y) {
    ffInstance.api->print(text, color, x, y);
}

void ff_scroll(void) {
    ffInstance.api->scroll(&ffInstance.row);
}

void ff_next_line(void) {
    ff_scroll();
}
