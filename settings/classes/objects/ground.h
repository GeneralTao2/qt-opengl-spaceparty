#ifndef GROUND_H
#define GROUND_H

#include <settings/classes/objects/plain.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/tools/main_tool.h>

class Ground
{
public:
    GLuint width, height;
    GLuint x, y;
    Plain *plain;
    TextureColorArgs *textureColorArgs;
    Ground(Plain *PLAIN);
    void Init();
    void Draw();
};

#endif // GROUND_H
