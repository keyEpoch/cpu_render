#pragma once
#include "api.h"

typedef struct {
    int width, height;
    unsigned char* color_buffer;    // unsigned char 来表示 0 ~ 255
    float* depth_buffer;
} framebuffer_t;

typedef struct program {
    vertex_shader_t* vertex_shader;
    fragment_shader_t* fragment_shader_t;
    
    int sizeof_attribs;
    int sizeof_varyings;
    int sizeof_uniforms;
    int double_sided;
    int enable_blender;

    /* for shaders */
    
    /* for clipping */
} program_t;

/* framebuffer management */
framebuffer_t* framebuffer_create(int width, int height);
void framebuffer_release(framebuffer_t* framebuffer);

void buffer_clear_color(framebuffer_t* framebuffer, vec4_t color);
void buffer_clear_depth(framebuffer_t* framebuffer, float depth);