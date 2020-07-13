#ifndef GAME_H
#define GAME_H

#include <glfw3.h>

#include <iostream>
#include <settings/classes/objects/camera.h>
#include <settings/classes/tools/shader_global_buffer.h>
#include <settings/classes/objects/plain.h>
#include <settings/classes/objects/plain_map.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/objects/background.h>
#include <settings/classes/objects/ground.h>
#include <settings/classes/objects/player.h>

class Game
{
public:
    Game();
    ~Game();
    Background *background;
    Ground *ground;
    Plain *plain;
    PlainMap *plainMap;
    Player *player;
    void Init();
    void Draw();
};

#endif // GAME_H
