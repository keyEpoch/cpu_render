#include <iostream>
#include "core/api.h"
#include "runner/run_blinn.h"
#include "runner/run_pbr.h"

// define function prototype
typedef void (*runfunc_t)(int argc, char* argv[]);

typedef struct {
    const char* runname;
    runfunc_t runfunc;
}runcase_t;

static runcase_t eg_runcases[] = {
    {"blinn", run_blinn},
    {"pbr",   run_pbr}
};

int main(int argc, char* argv[]) {
    int num_runcases = ARRAY_SIZE(eg_runcases);
    if (argc != 3) {
        cout << "argc should be 3! " << endl;
        exit(EXIT_FAILURE);
    }

    bool runfunc_match = false;
    const char* arg_runname = argv[1];
    runfunc_t arg_runfunc = NULL;

    for (auto& run_case : eg_runcases) {
        if (strcmp(run_case.runname, arg_runname) == 0) {
            runfunc_match = true;
            arg_runfunc = run_case.runfunc;
            break;
        }
    }

    if (!runfunc_match) {
        cout << "no matching runfunctions! " << endl;
        exit(EXIT_FAILURE);
    }

    if (arg_runfunc) {
        cout << "runname: " << arg_runname << endl;
        arg_runfunc(argc, argv);
    }   

    return 0;
}








