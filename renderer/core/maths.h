#pragma once
#include <cassert>

/* vector */
typedef struct {
    float x, y;
} vec2_t;

typedef struct {
    float x, y, z;
} vec3_t;

typedef struct {
    float x, y, z, w;
} vec4_t;

/* matrix */
typedef struct {
    float m[3][3];
} mat3_t;

typedef struct {
    float m[4][4];
} mat4_t;


/* vec3 related vectors */
vec3_t vec3_new(float x, float y, float z);

vec3_t vec3_min(vec3_t a, vec3_t b);

vec3_t vec3_max(vec3_t a, vec3_t b);

vec3_t vec3_add(vec3_t a, vec3_t b);

vec3_t vec3_sub(vec3_t a, vec3_t b);

vec3_t vec3_mul(vec3_t a, float factor);

vec3_t vec3_div(vec3_t a, float divisor);

/* vec4 related vectors */

vec4_t vec4_new(float x, float y, float z, float w);

vec4_t vec4_from_vec3(vec3_t v, float w);

/* float related functions */
unsigned char float_to_uchar(float f);   // f is in [0, 1]














