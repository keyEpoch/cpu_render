#pragma once
#include "maths.h"

/*
 * for skeletal animation, see
 * https://people.rennes.inria.fr/Ludovic.Hoyet/teaching/IMO/05_IMO2016_Skinning.pdf
 */

typedef struct {
    int joint_index;
    int parent_index;
    mat4_t inverse_bind;

    /* translations 平移 */ 
    int num_translations;         // 平移次数
    float* translation_times;     // 平移的时间
    vec3_t* translation_values;   // 平移的值

    /* rotations 旋转 */
    int num_rotations;
    float* rotation_times;
    quat_t* rotation_values;      // quaternion值 四元数 用四元数来表示旋转
 
    /* scales 缩放*/
    int num_scales;
    float* scale_times;
    vec3_t* scale_values;

    /* interpolated */ 
    mat4_t transform;

} joint_t;

typedef struct skeleton {
    float min_time;
    float max_time;
    int num_joints;
    joint_t* joints;
    
    /* cached results */
    mat4_t* joint_matrics;     // 关节矩阵
    mat3_t* normal_matrics;    // normal矩阵
    float last_time;
} skeleton_t;

/* joint updating&retrieving */
void skeleton_update_joints(skeleton_t* skeleton, float frame_time);