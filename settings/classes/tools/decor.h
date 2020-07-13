#ifndef DECOR_H
#define DECOR_H

#include "shader.h"
#include "texture.h"

struct PostProcessing {
    float exposure = 0.5;
    int mode = 0;
    float gamma = 1.53;
    float offset = 0.03;
    std::vector<float> kernelMat = {
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
    };
    int currentMat = 0;
    std::vector<const char*> kernelNames = {
        "sharpen",
        "blur",
        "endgeDetection"
    };
    std::vector<std::vector<float>> kernelMats = {
        {
            -1, -1, -1,
            -1, 9, -1,
            -1, -1, -1
        },{
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16
        },{
            1, 1, 1,
            1, -8, 1,
            1, 1, 1
        }
    };
};



#endif // DECOR_H
