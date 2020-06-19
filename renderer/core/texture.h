#pragma once

#include "maths.h"

typedef struct {
    int width, height;
    vec4_t* buffer;
} texture_t;


/* texture related functions */ 
texture_t* texture_create(int width, int height);