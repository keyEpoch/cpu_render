#include "graphics.h"
#include "api.h"
#include "maths.h"

/* framebuffer management */
framebuffer_t* framebuffer_create(int width, int height) {
    int color_buffer_size = width * height * 4;
    int depth_buffer_size = sizeof(float) * width * height;
    vec4_t default_color = {0, 0, 0, 1};
    float default_depth = 1;
    framebuffer_t* framebuffer;

    assert(width > 0 && height > 0);

    framebuffer = (framebuffer_t*)malloc(sizeof(framebuffer_t));
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->color_buffer = (unsigned char*)malloc(color_buffer_size);
    framebuffer->depth_buffer = (float*)malloc(depth_buffer_size);

    buffer_clear_color(framebuffer, default_color);
    buffer_clear_depth(framebuffer, default_depth);    
}

void framebuffer_release(framebuffer_t* framebuffer) {
    free(framebuffer->color_buffer);
    free(framebuffer->depth_buffer);
    free(framebuffer);
}

void buffer_clear_color(framebuffer_t* framebuffer, vec4_t color) {
    int num_pixels = framebuffer->width * framebuffer->height;
    unsigned char r, g, b, a;
    r = float_to_uchar(color.x);
    g = float_to_uchar(color.y);
    b = float_to_uchar(color.z);
    a = float_to_uchar(color.w);
    for (int i = 0; i < num_pixels; ++i) {
        framebuffer->color_buffer[4 * i + 0] = r;
        framebuffer->color_buffer[4 * i + 1] = g;
        framebuffer->color_buffer[4 * i + 2] = b;
        framebuffer->color_buffer[4 * i + 3] = a;
    }
}

void buffer_clear_depth(framebuffer_t* framebuffer, float depth) {
    int num_pixels = framebuffer->width * framebuffer->height;
    for (int i = 0; i < num_pixels; ++i)
        framebuffer->depth_buffer[i] = depth;
} 