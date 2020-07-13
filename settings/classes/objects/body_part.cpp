#include "body_part.h"

BodyPart::BodyPart() {
    Init();
}

BodyPart::~BodyPart() {
    //delete textureColorMapArgs;
}

void BodyPart::Init() {
   /* textureColorMapArgs = new TextureColorMapArgs({
        .position = {200, 200},
        .scale = {100, 100},
        .angle = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .textureCoords = {0,0,0.2,0.2},
        .shader = RM::GetShader("texture_color_plain_map")
       });*/
}

void BodyPart::Draw() {
    //plainMap->Drow(textureColorMapArgs);
}
