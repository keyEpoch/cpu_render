#pragma once

#include "../core/api.h"
#include "../core/scene.h"

typedef struct {
    vec3_t bbox_min;
    vec3_t bbox_max;
} bbox_t;

typedef struct {
    const char* scene_name;
    scene_t* (*create_scene)(void);
} creator_t;


scene_t* run_create_scene(creator_t creators[], const char* scene_name);