#include "scene.h"
#include "maths.h"
#include "texture.h"
#include "darray.h"

scene_t *scene_create(vec3_t background, model_t *skybox, \
  model_t **models, float ambient_intensity, \ 
  float punctual_intensity, int shadow_width, int shadow_height) {

    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->background = vec4_from_vec3(background, 1);
    scene->skybox = skybox;
    scene->models = models;
    scene->ambient_intensity = ambient_intensity;
    scene->punctual_intensity = punctual_intensity;

    if (shadow_width > 0 && shadow_height > 0) {
        scene->shadow_buffer = framebuffer_create(shadow_width, shadow_height);
        scene->shadow_map = texture_create(shadow_width, shadow_height);
    } else {
        scene->shadow_map = NULL;
        scene->shadow_map = NULL;
    }
    return scene;
}


void scene_release (scene_t* scene) {
    int num_models = darray(scene->models);
}