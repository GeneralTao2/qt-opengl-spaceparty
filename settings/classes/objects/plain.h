#ifndef PLAIN_H
#define PLAIN_H

#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../tools/shader.h"
#include "../tools/resource_manager.h"
#include "../tools/shader_arg_structs.h"

class Plain
{
public:
    unsigned int VAO;
    unsigned int VBO;
    void Init();
    void Drow(ColorArgs args);
    void Drow(TextureColorArgs *args);
    void Drow();
    Plain();
};

#endif // PLAIN_H
