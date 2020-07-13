#ifndef RIG_H
#define RIG_H

#include <settings/classes/objects/plain_map.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/tools/main_tool.h>

class Rig
{
public:
    std::vector< std::vector<MovePoint> > points;
    PlainMap *plainMap;
    TextureColorMapBoneArgs *leftHand;
    TextureColorMapBoneArgs *rightHand;
    TextureColorMapBoneArgs *leftLeg;
    TextureColorMapBoneArgs *rightLeg;
    TextureColorMapBoneArgs *head;
    TextureColorMapBodyArgs *torso;
    MoveAction *runing;
    float PI = 3.14159265359;
    void Init();
    void Draw();
    void ProcessMove();
    void ProcessAnimation();
    void Moving(TextureColorMapBoneArgs *part);
    void Run();
    Rig(PlainMap *PLAINMAP);
    ~Rig();
};

#endif // RIG_H
