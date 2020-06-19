#include "texture.h"
#include <cassert>
#include <cstring>

/* texture related functions */
texture_t* texture_create(int width, int height) {
    assert(width > 0 && height > 0);
    int buffer_size = sizeof(vec4_t) * width * height;
    // 为火车头申请空间
    texture_t* texture = (texture_t*)malloc(sizeof(texture_t));

    texture->width = width;
    texture->height = height;
    // 挂一长串火车尾
    texture->buffer = (vec4_t*)malloc(buffer_size);
    
    memset(texture->buffer, 0, buffer_size);

    return texture;
}