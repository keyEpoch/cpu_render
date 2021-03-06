#pragma once
#include <cassert>
#include "macro.h"
#include <math.h>

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

typedef struct {
    float x, y, z, w;
} quat_t;            // quaternion 四元数

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

vec3_t vec3_from_vec4(vec4_t v);

vec3_t vec3_lerp(vec3_t a, vec3_t b, float t);

/* vec4 related vectors */

vec4_t vec4_new(float x, float y, float z, float w);

vec4_t vec4_from_vec3(vec3_t v, float w);

/* float related functions */
unsigned char float_to_uchar(float f);   // f is in [0, 1]

float float_lerp(float a, float b, float t);

/* mat3 related functions */
mat3_t mat3_from_mat4(mat4_t m);

mat3_t mat3_inverse_transpose(mat3_t m);

mat3_t mat3_adjoint(mat3_t m);

/* mat4 related functions */
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v);

mat4_t mat4_from_trs(vec3_t t, quat_t r, vec3_t s);

mat4_t mat4_identity(void);

mat4_t mat4_from_quat(quat_t q);

mat4_t mat4_mul_mat4(mat4_t a, mat4_t b);

/* quat related functions */
quat_t quat_new(float x, float y, float z, float w);

float quat_dot(quat_t a, quat_t b);

quat_t quat_slerp(quat_t a, quat_t b, float t);

/* transform matrics */
mat4_t mat4_translate(float tx, float ty, float tz);   // 平移矩阵

mat4_t mat4_scale(float sx, float sy, float sz);

mat4_t mat4_rotate_x(float angle);

mat4_t mat4_rotate_y(float angle);

mat4_t mat4_rotate_z(float angle);


