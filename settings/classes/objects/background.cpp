#include "background.h"

Background::Background(Plain *PLAIN) : plain(PLAIN)
{
    Init();
}

Background::~Background() {
    delete textureColorArgs;
}

void Background::Init() {
    GLuint textureWidth = RM::GetTexture("bg").Width;
    GLuint textureHeight = RM::GetTexture("bg").Height;
    textureColorArgs = new TextureColorArgs({
        .position = {textureWidth/2, textureHeight/2},
        .scale = {textureWidth, textureHeight},
        .axes = {1, 1},
        .angle = 0,
        .Zindex = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("bg"),
        .shader = RM::GetShader("texture_color_plain")
       });
}

void Background::Draw() {
    plain->Drow(textureColorArgs);
}
