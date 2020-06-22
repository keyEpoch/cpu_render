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

vec3_t vec3_lerp(vec3_t a, vec3_t b, float t) {   // 根据t来进行vector插值
    float x = float_lerp(a.x, b.x, t);
    float y = float_lerp(a.y, b.y, t);
    float z = float_lerp(a.z, b.z, t);
    return vec3_new(x, y, z);
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

float float_lerp(float a, float b, float t) {
    return a + (b - a) * t;      // 根据比例t，来进行float 插值操作
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

// 根据 平移向量，四元数，scale来得到一个总的transform矩阵
mat4_t mat4_from_trs(vec3_t t, quat_t r, vec3_t s) {
    mat4_t translation = mat4_translate(t.x, t.y, t.z);
    mat4_t rotation = mat4_from_quat(r);
    mat4_t scale = mat4_scale(s.x, s.y, s.z);
    return mat4_mul_mat4(translation, mat4_mul_mat4(rotation, scale));
}

mat4_t mat4_identity(void) {
    mat4_t m = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    }};
    return m;
}

mat4_t mat4_from_quat(quat_t q) {
    mat4_t m = mat4_identity();
    float xx = q.x * q.x; float xy = q.x * q.y; float xz = q.x * q.z;
    float xw = q.x * q.w; float yy = q.y * q.y; float yz = q.y * q.z;
    float yw = q.y * q.w; float zz = q.z * q.z; float zw = q.z * q.w;

    m.m[0][0] = 1 - 2 * (yy + zz);
    m.m[0][1] = 2 * (xy - zw);
    m.m[0][2] = 2 * (xz + yw);

    m.m[1][0] = 2 * (xy + zw);
    m.m[1][1] = 1 - 2 * (xx + zz);
    m.m[1][2] = 2 * (yz - xw);

    m.m[2][0] = 2 * (xz - yw);
    m.m[2][1] = 2 * (yz + xw);
    m.m[2][2] = 1 - 2 * (xx + yy);

    return m;
}

mat4_t mat4_mul_mat4(mat4_t a, mat4_t b) {
    mat4_t m = {{{0}}};
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                m.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return m;
}

/* quat related functions */
quat_t quat_new(float x, float y, float z, float w) {
    quat_t q;
    q.x = x; q.y = y; q.z = z; q.w = w;
    return q;
}

float quat_dot(quat_t a, quat_t b) {     // quat 点乘
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

quat_t quat_slerp(quat_t a, quat_t b, float t) {     // quat 插值
    float cos_angle = quat_dot(a, b);
    if (cos_angle < 0) {
        b = quat_new(-b.x, -b.y, -b.z, -b.w);
        cos_angle = -cos_angle;
    }
    if (cos_angle > 1 - EPSILON) {
        float x = float_lerp(a.x, b.x, t);
        float y = float_lerp(a.y, b.y, t);
        float z = float_lerp(a.z, b.z, t);
        float w = float_lerp(a.w, b.w, t);
        return quat_new(x, y, z, w);
    } else {
        float angle = (float)acos(cos_angle);
        float sin_angle = (float)sin(angle);
        float angle_a = (1 - t) * angle;
        float angle_b = t * angle;
        float factor_a = (float)sin(angle_a) / sin_angle;
        float factor_b = (float)sin(angle_b) / sin_angle;
        float x = factor_a * a.x + factor_b * b.x;
        float y = factor_a * a.y + factor_b * b.y;
        float z = factor_a * a.z + factor_b * b.z;
        float w = factor_a * a.w + factor_b * b.w;
        return quat_new(x, y, z, w);
    }
}

/* transform matrics */

/*
 * 平移矩阵
 * tx, ty, tz: the x, y, and z coordinates of a translation vector
 *
 *  1  0  0 tx
 *  0  1  0 ty
 *  0  0  1 tz
 *  0  0  0  1
 *
 * see http://docs.gl/gl2/glTranslate
 */
mat4_t mat4_translate(float tx, float ty, float tz) {
    mat4_t m = mat4_identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;
    return m;
}


/*
 * sx, sy, sz: scale factors along the x, y, and z axes, respectively
 *
 * sx  0  0  0
 *  0 sy  0  0
 *  0  0 sz  0
 *  0  0  0  1
 *
 * see http://docs.gl/gl2/glScale
 */
mat4_t mat4_scale(float sx, float sy, float sz) {
    mat4_t m = mat4_identity();
    assert(sx != 0 && sy != 0 && sz != 0);
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}