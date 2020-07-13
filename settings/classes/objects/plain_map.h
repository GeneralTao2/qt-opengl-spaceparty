#ifndef PLAIN_MAP_H
#define PLAIN_MAP_H

#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../tools/shader.h"
#include "../tools/resource_manager.h"
#include "../tools/shader_arg_structs.h"

class PlainMap
{
public:
    unsigned int VAO;
    unsigned int VBO;
    void Init();
    void Drow(TextureColorMapBoneArgs *args);
    void Drow(TextureColorMapBodyArgs *args);
    PlainMap();
};

#endif // PLAIN_MAP_H
