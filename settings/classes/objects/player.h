#ifndef PLAYER_H
#define PLAYER_H

#include <settings/classes/objects/plain_map.h>
#include <settings/classes/objects/rig.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/tools/main_tool.h>

class Player
{
public:
    void Init();
    void Draw();
    PlainMap *plainMap;
    Rig *rig;
    Player(PlainMap *PLAINMAP);
    ~Player();
};

#endif // PLAYER_H
