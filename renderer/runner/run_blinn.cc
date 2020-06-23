#include "../core/api.h"
#include "../scenes/blinn_scenes.h"
#include "run_helper.h"

static creator_t g_creators[] = {
    {"azura", blinn_azura_scene},
    {"centaur", blinn_centaur_scene},
    {"craftsman", blinn_craftsman_scene},
    {"elfgirl", blinn_elfgirl_scene},
    {"kgirl", blinn_kgirl_scene},
    {"lighthouse", blinn_lighthouse_scene},
    {"mccree", blinn_mccree_scene},
    {"nier2b", blinn_nier2b_scene},
    {"phoenix", blinn_phoenix_scene},
    {"whip", blinn_whip_scene},
    {"witch", blinn_witch_scene},
    {NULL, NULL},
};

static void tick_function(context_t* context, void* userdata) {

}

void run_blinn(int argc, char* argv[]) {
    // cout << "run blinn function! " << endl;
    // cout << argc << endl;
    // cout << endl;

    assert(argc == 3);
    const char* scene_name = argv[2];
    scene_t* scene = run_create_scene(g_creators, scene_name);

    if (scene) {
        run_enter_mainloop(tick_function, scene);
        
    }
}