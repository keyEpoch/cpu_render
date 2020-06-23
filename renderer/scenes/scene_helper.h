#pragma once

#include "../core/api.h"

typedef struct {
    vec3_t background;
    char environment[LINE_SIZE];
    char skybox[LINE_SIZE];
    char shadow[LINE_SIZE];
    float ambient;
    float punctual;
} scene_light_t;

typedef struct {
    int index;
    mat4_t matrix;
} scene_transform_t;

typedef struct {
    int index;
    vec4_t basecolor;
    float shininess;
    char diffuse_map[LINE_SIZE];
    char specular_map[LINE_SIZE];
    char emission_map[LINE_SIZE];
    char double_sided[LINE_SIZE];
    char enable_blend[LINE_SIZE];
    float alpha_cutoff;
} scene_blinn_t;

typedef struct {
    int index;
    vec4_t basecolor_factor;
    float metalness_factor;
    float roughness_factor;
    char basecolor_map[LINE_SIZE];
    char metalness_map[LINE_SIZE];
    char roughness_map[LINE_SIZE];
    char normal_map[LINE_SIZE];
    char occlusion_map[LINE_SIZE];
    char emission_map[LINE_SIZE];
    char double_sided[LINE_SIZE];
    char enable_blend[LINE_SIZE];
    float alpha_cutoff;
} scene_pbrm_t;

typedef struct {
    int index;
    vec4_t diffuse_factor;
    vec3_t specular_factor;
    float glossiness_factor;
    char diffuse_map[LINE_SIZE];
    char specular_map[LINE_SIZE];
    char glossiness_map[LINE_SIZE];
    char normal_map[LINE_SIZE];
    char occlusion_map[LINE_SIZE];
    char emission_map[LINE_SIZE];
    char double_sided[LINE_SIZE];
    char enable_blend[LINE_SIZE];
    float alpha_cutoff;
} scene_pbrs_t;

scene_t* scene_from_file(const char* filename, mat4_t root);