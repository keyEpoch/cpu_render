#include "skeleton.h"
#include <math.h>
#include "macro.h"
#include "maths.h"

/* joint updating&retrieving static functions */
static vec3_t get_translation(joint_t* joint, float frame_time) {
    int num_translations = joint->num_translations;
    float* translation_times = joint->translation_times;
    vec3_t* translation_values = joint->translation_values;

    if (num_translations == 0) 
        return vec3_new(0, 0, 0);
    else if (frame_time <= translation_times[0]) 
        return translation_values[0];
    else if (frame_time >= translation_times[num_translations - 1]) 
        return translation_values[num_translations - 1];
    else {
        for (int i = 0; i < num_translations - 1; ++i) {
            float curr_time = translation_times[i];
            float next_time = translation_times[i + 1];
            if (frame_time >= curr_time && frame_time < next_time) {
                float t = (frame_time - curr_time) / (next_time - curr_time);
                vec3_t curr_translation = translation_values[i];
                vec3_t next_translation = translation_values[i + 1];
                // 根据t来得到vector插值
                return vec3_lerp(curr_translation, next_translation, t);
            }
        }
        assert(0);
        return vec3_new(0, 0, 0);
    }
}

static quat_t get_rotation(joint_t* joint, float frame_time) {
    int num_rotations = joint->num_rotations;
    float *rotation_times = joint->rotation_times;
    quat_t *rotation_values = joint->rotation_values;

    if (num_rotations == 0) {
        return quat_new(0, 0, 0, 1);
    } else if (frame_time <= rotation_times[0]) {
        return rotation_values[0];
    } else if (frame_time >= rotation_times[num_rotations - 1]) {
        return rotation_values[num_rotations - 1];
    } else {
        int i;
        for (i = 0; i < num_rotations - 1; i++) {
            float curr_time = rotation_times[i];
            float next_time = rotation_times[i + 1];
            if (frame_time >= curr_time && frame_time < next_time) {
                float t = (frame_time - curr_time) / (next_time - curr_time);
                quat_t curr_rotation = rotation_values[i];
                quat_t next_rotation = rotation_values[i + 1];
                return quat_slerp(curr_rotation, next_rotation, t);
            }
        }
        assert(0);
        return quat_new(0, 0, 0, 1);
    }
}

static vec3_t get_scale(joint_t *joint, float frame_time) {
    int num_scales = joint->num_scales;
    float *scale_times = joint->scale_times;
    vec3_t *scale_values = joint->scale_values;

    if (num_scales == 0) {
        return vec3_new(1, 1, 1);
    } else if (frame_time <= scale_times[0]) {
        return scale_values[0];
    } else if (frame_time >= scale_times[num_scales - 1]) {
        return scale_values[num_scales - 1];
    } else {
        int i;
        for (i = 0; i < num_scales - 1; i++) {
            float curr_time = scale_times[i];
            float next_time = scale_times[i + 1];
            if (frame_time >= curr_time && frame_time < next_time) {
                float t = (frame_time - curr_time) / (next_time - curr_time);
                vec3_t curr_scale = scale_values[i];
                vec3_t next_scale = scale_values[i + 1];
                return vec3_lerp(curr_scale, next_scale, t);
            }
        }
        assert(0);
        return vec3_new(1, 1, 1);
    }
}

void skeleton_update_joints(skeleton_t* skeleton, float frame_time) {
    // fmod 相当于是对 float 的 mod，也就是取余
    frame_time = (float)fmod(frame_time, skeleton->max_time);   
    if (frame_time != skeleton->last_time) {
        for (int i = 0; i < skeleton->num_joints; ++i) {
            joint_t* joint = &skeleton->joints[i];
            vec3_t translation = get_translation(joint, frame_time);
            quat_t rotation = get_rotation(joint, frame_time);
            vec3_t scale = get_scale(joint, frame_time);

            mat4_t joint_matrix;
            mat3_t normal_matrix;

            joint->transform = mat4_from_trs(translation, rotation, scale);

            if (joint->parent_index >= 0) {
                joint_t *parent = &skeleton->joints[joint->parent_index];
                joint->transform = mat4_mul_mat4(parent->transform,
                                                 joint->transform);
            }

            joint_matrix = mat4_mul_mat4(joint->transform, joint->inverse_bind);
            normal_matrix = mat3_inverse_transpose(mat3_from_mat4(joint_matrix));
            skeleton->joint_matrices[i] = joint_matrix;
            skeleton->normal_matrices[i] = normal_matrix;
        }
        skeleton->last_time = frame_time;
    }
}