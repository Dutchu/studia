#include <stdio.h>
#include <string.h>
#include <stddef.h>

void show(const void* ptr, size_t count) {
    if (!ptr || count == 0) {
        return;
    }

    const unsigned char* bytes = (const unsigned char*)ptr;
    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%02x", (unsigned int)bytes[i]);
    }
}

void inverse_bits(void* ptr, size_t offset, size_t count) {
    if (!ptr || count == 0) {
        return;
    }

    unsigned char* bytes = (unsigned char*)ptr;
    bytes += offset;
    for (size_t i = 0; i < count; ++i) {
        bytes[i] = (unsigned char)~bytes[i];
    }
}

int main(void) {
    char text[101];

    printf("Podaj tekst: ");
    if (!fgets(text, (int)sizeof(text), stdin)) {
        return 0; // no input
    }

    // Strip trailing newline if present
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        --len;
    }

    // Include the terminator in representation
    size_t bytes_to_show = len + 1;

    show((const void*)text, bytes_to_show);
    putchar('\n');

    inverse_bits((void*)text, 0, bytes_to_show);

    show((const void*)text, bytes_to_show);
    putchar('\n');

    return 0;
}
