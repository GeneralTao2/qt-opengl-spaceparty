#ifndef BODY_PART_H
#define BODY_PART_H

#include <settings/classes/objects/plain_map.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/tools/main_tool.h>

class BodyPart
{
public:
    BodyPart();
    ~BodyPart();
    PlainMap *plainMap;
    //TextureColorMapArgs *textureColorMapArgs;
    void Init();
    void Draw();
};

#endif // BODY_PART_H
