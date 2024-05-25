#include <stdio.h>
#include <errno.h>
#include <string.h>

#define global static
#define return_defer(value) do { result = (value); goto defer; } while (0)

#define WIDTH 800
#define HEIGHT 600

typedef int Errno;

void g_fill(
    u_int32_t *pixels,
    size_t width,
    size_t height,
    u_int32_t color
) {
    for (size_t i = 0; i < width * height; ++i) {
        pixels[i] = color;
    }
}

Errno g_save_to_ppm_file(
    const u_int32_t *pixels,
    size_t width,
    size_t height,
    const char *file_path
) {
    int result = 0;

    FILE *f = fopen(file_path, "wb");
    if (!f) return_defer(-1);

    fprintf(f, "P6\n%zu %zu 255\n", width, height);
    if (ferror(f)) return_defer(-1);

    for (size_t i = 0; i < width * height; ++i) {
        u_int32_t pixel = pixels[i];
        u_int8_t bytes[3] = {
            [0] = (pixel >> (8 * 0)) & 0xFF,
            [1] = (pixel >> (8 * 1)) & 0xFF,
            [2] = (pixel >> (8 * 2)) & 0xFF,
        };

        fwrite(bytes, sizeof(bytes), 1, f);
        if (ferror(f)) return_defer(-1);
    }

    defer:
    if (f) fclose(f);
    return result;
}

#if 0
global u_int32_t pixels[WIDTH * HEIGHT];

int main(void) {
    g_fill(pixels, WIDTH, HEIGHT, 0xFFFF0000);

    const char *file_path = "out.ppm";
    Errno err = g_save_to_ppm_file(pixels, WIDTH, HEIGHT, "out.ppm");
    if (err) {
        fprintf(stderr, "error: could not save file %s: %s\n", file_path, strerror(errno));
        return -1;
    }

    return 0;
}
#endif
