#include "ground.h"

Ground::Ground(Plain *PLAIN) : plain(PLAIN) {
    Init();
}

void Ground::Init() {
    GLuint height = RM::GetTexture("ground").Height;
    textureColorArgs = new TextureColorArgs({
        .position = {500, SCR_HEIGHT-(height*0.5)},
        .scale = {1000, height},
        .axes = {1, 1},
        .angle = 0,
        .Zindex = 5,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("ground"),
        .shader = RM::GetShader("texture_color_plain")
       });
}

void Ground::Draw() {
    plain->Drow(textureColorArgs);
}
