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



void skeleton_update_joints(skeleton_t* skeleton, float frame_time) {
    // fmod 相当于是对 float 的 mod，也就是取余
    frame_time = (float)fmod(frame_time, skeleton->max_time);   
    if (frame_time != skeleton->last_time) {
        for (int i = 0; i < skeleton->num_joints; ++i) {
            joint_t* joint = &skeleton->joints[i];
            vec3_t translation = get_translation(joint, frame_time);
            quat_t rotation = get_rotation(joint, frame_time);

        }
    }
}