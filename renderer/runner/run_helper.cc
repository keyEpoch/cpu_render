#include "run_helper.h"
#include "../core/api.h"
#include "../core/darray.h"
#include "../core/mesh.h"
#include "../core/maths.h"
#include "../core/skeleton.h"

/* static funcitons, only used in this file */
static int count_num_faces(scene_t* scene) {
    int num_models = darray_size(scene->models);
    int num_faces = 0;
    
    for (int i = 0; i < num_models; ++i) {
        model_t* model = scene->models[i];
        num_faces += mesh_get_num_faces(model->mesh);
    }

    return num_faces;
}

static bbox_t get_model_bbox(model_t* model) {
    mesh_t* mesh = model->mesh;
    int num_faces = mesh_get_num_faces(mesh);
    vertex_t* vertices = mesh_get_vertecs(mesh);
    // Model 坐标，将model从模型坐标系转换到世界坐标系
    mat4_t model_matrix = model->transform;
    bbox_t bbox;

    // 因为动画和skeleton会动，所以要计算一下运动周期中的bbox
    if (model->skeleton && model->attached >= 0) {
        mat4_t* joint_matrics;
        mat4_t node_matrix;
        skeleton_update_joints(model->skeleton, 0); 
        joint_matrics = skeleton_get_joint_matrices(model->skeleton);

        // 选取 attached 的那个关节
        node_matrix = joint_matrics[model->attached];
        model_matrix = mat4_mul_mat4(model_matrix, node_matrix);
    }

    bbox.bbox_min = vec3_new(+1e6, +1e6, +1e6);
    bbox.bbox_max = vec3_new(-1e6, -1e6, -1e6);
    for (int i = 0; i < num_faces; ++i) {
        for (int j = 0; j < 3; ++j) {
            vertex_t vertex = vertices[i * 3 + j];
            // 转化成齐次坐标
            vec4_t local_pos = vec4_from_vec3(vertex.position, 1);   
            vec4_t world_pos = mat4_mul_vec4(model_matrix, local_pos);
            bbox.bbox_min = vec3_min(bbox.bbox_min, vec3_from_vec4(world_pos));
            bbox.bbox_max = vec3_max(bbox.bbox_max, vec3_from_vec4(world_pos));
        }
    }
    return bbox;
}

static bbox_t get_scene_bbox(scene_t* scene) {
    int num_models = darray_size(scene->models);
    bbox_t bbox;
    bbox.bbox_min = vec3_new(+1e6, +1e6, +1e6);
    bbox.bbox_max = vec3_new(-1e6, -1e6, -1e6);
    for (int i = 0; i < num_models; ++i) {
        model_t* model = scene->models[i];
        bbox_t bbox_model = get_model_bbox(model);
        bbox.bbox_min = vec3_min(bbox_model.bbox_min, bbox.bbox_min);
        bbox.bbox_max = vec3_max(bbox_model.bbox_max, bbox.bbox_max);
    }
    return bbox;
}

scene_t* run_create_scene(creator_t creators[], const char* scene_name) {
    scene_t* scene = NULL;
    assert(scene_name != NULL);
    for (int i = 0; creators[i].scene_name != NULL; ++i) {
        if (strcmp(creators[i].scene_name, scene_name) == 0) {
            cout << "scene name: " << scene_name << endl;
            scene = creators[i].create_scene();  // 创建场景
            break;
        }
    } 
    
    assert(scene != NULL);

    int num_faces = count_num_faces(scene);
    // 得到场景的 bbox
    bbox_t bbox = get_scene_bbox(scene);
    // 得到bbox的center
    vec3_t center = vec3_div(vec3_add(bbox.bbox_min, bbox.bbox_max), 2);
    // bbox的对角向量
    vec3_t extent = vec3_sub(bbox.bbox_max, bbox.bbox_min);

    bool with_skybox = scene->skybox != NULL;
    bool with_shadow = scene->skybox != NULL;
    bool with_ambient = scene->ambient_intensity > 0;
    bool with_punctual = scene->punctual_intensity > 0;    

    cout << "faces: " << num_faces << endl;
    cout << "center: [" << center.x << ", " << center.y << ", " << \
      center.z << "]" << endl;
    cout << "extent: [" << center.x << ", " << center.y << ", " << \
      center.z << "]" << endl;
    cout << "skybox: " << (with_skybox ? "on" : "off") << endl;
    cout << "shadow: " << (with_shadow ? "on" : "off") << endl;
    cout << "ambient: " << (with_shadow ? "on" : "off") << endl;
    cout << "punctual: " << (with_shadow ? "on" : "off") << endl;

    return scene;
}


 






