#pragma once

#include "api.h"
#include "maths.h"

typedef struct {
    vec3_t position;         // 顶点位置
    vec2_t texture_cood;     // texture_map 上对应的纹理坐标
    vec3_t normal;           // 顶点法向
    
    vec4_t tangent;          // 
    vec4_t joint;
    vec4_t weight;
} vertex_t;

typedef struct mesh {
    int num_faces;            // 面片的数量
    vertex_t* vertices;       // 顶点
    vec3_t center;
} mesh_t;

/* mesh loading and releasing */
mesh_t* mesh_load(const char* filename);
void mesh_release(mesh_t* mesh);

/* mesh retrieving */ 
int mesh_get_num_faces(mesh_t* mesh);
vertex_t* mesh_get_vertecs(mesh_t* mesh);
vec3_t mesh_get_center(mesh_t* mesh);