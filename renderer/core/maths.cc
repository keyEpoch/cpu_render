#include "maths.h"

/* vec3 related apis */
vec3_t vec3_new(float x, float y, float z) {
    vec3_t vec3;
    vec3.x = x; vec3.y = y; vec3.z = z;
    return vec3;
}

vec3_t vec3_min(vec3_t a, vec3_t b) {
    float x = a.x < b.x ? a.x : b.x;
    float y = a.y < b.y ? a.y : b.y;
    float z = a.z < b.z ? a.z : b.z;
    return vec3_new(x, y, z);
}

vec3_t vec3_max(vec3_t a, vec3_t b) {
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    float z = a.z > b.z ? a.z : b.z;
    return vec3_new(x, y, z);
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
    return vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
    return vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3_t vec3_mul(vec3_t a, float factor) {
    return vec3_new(a.x * factor, a.x * factor, a.x * factor);
}

vec3_t vec3_div(vec3_t a, float divisor) {
    assert(divisor != 0);
    divisor = 1 / divisor; 
    return vec3_mul(a, divisor);
}

/* vec4 related apis */
vec4_t vec4_new(float x, float y, float z, float w) {
    vec4_t vec4;
    vec4.x = x; vec4.y = y; vec4.z = z; vec4.w = w;
    return vec4;
}

vec4_t vec4_from_vec3(vec3_t v, float w) {
    return vec4_new(v.x, v.y, v.z, w);
}

vec3_t vec3_from_vec4(vec4_t v) {
    return vec3_new(v.x, v.y, v.z);
}


/* float related functions */
unsigned char float_to_uchar(float f) {     
    return (unsigned char)(f * 255);
}



/* mat4 related functions */
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v) {
    float res[4];
    for (int i = 0; i < 4; ++i) {
        float a = m.m[i][0] * v.x;
        float b = m.m[i][1] * v.y;
        float c = m.m[i][2] * v.z;
        float d = m.m[i][3] * v.w;
        res[i] = a + b + c + d;
    }
    return vec4_new(res[0], res[1], res[2], res[3]);
}