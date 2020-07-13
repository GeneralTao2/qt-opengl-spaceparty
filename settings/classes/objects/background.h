#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <settings/classes/objects/plain.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/tools/main_tool.h>

class Background
{
public:
    Background(Plain *PLAIN);
    ~Background();
    Plain *plain;
    TextureColorArgs *textureColorArgs;
    void Init();
    void Draw();
};

#endif // BACKGROUND_H
