#pragma once

#include "maths.h"
#include "texture.h"
#include "mesh.h"

typedef struct {
    
    float frame_time;           // 每一帧的时间
    float delta_time;
    
    vec3_t light_dir;           // 光线方向
    vec3_t camera_pos;          // 相机姿态

    mat4_t light_view_matrix;   // 光线的 view 矩阵
    mat4_t light_proj_matrix;   // 光线的 proj 矩阵
    mat4_t camera_view_matrix;  // 相机的 view 矩阵 
    mat4_t camera_proj_matrix;  // 相机的 proj 矩阵

    float ambient_intensity;    // 环境光的光强
    float punctual_intensity;   // 实时光强

    texture_t* shadow_map;

    int layer_view;
} perframe_t;

typedef struct model {
    mesh_t* mesh;             // 网格
    program_t* program;
    mat4_t transform;

    /* for animation */ 
    skeleton_t* skeleton;     // 骨骼
    int attached;

    /* for sorting */ 
    int opaque;               // 不透明度
    float distance;

    // TODO: add polymorphism 

} model_t;

typedef struct {
    vec4_t background;        // 背景
    model_t* sky_box;         // 天空盒子
    model_t** models;         // 场景中会有很多model，所以就声明二级指针

    /* light intensity */ 
    float ambient_intensity;
    float punctual_intensity;

    /* shadow mapping */
    framebuffer_t* shadow_buffer;
    texture_t* shadow_map;
} scene_t;


/* claim functions */
scene_t* scene_create (
    vec3_t background,
    model_t* skybox,
    model_t** models,
    float ambient_intensity,
    float punctual_intensity,
    int shadow_width,
    int shadow_height
);

void scene_release (scene_t* scene);











