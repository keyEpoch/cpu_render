#pragma once

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
    float mat3[3][3];
} mat3_t;

typedef struct {
    float mat4[4][4];
} mat4_t;








