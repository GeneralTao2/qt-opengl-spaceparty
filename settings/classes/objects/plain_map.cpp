#include "plain_map.h"

PlainMap::PlainMap()
{
    Init();
}

void PlainMap::Init() {
    float vertices[] = {
           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(1);
}

void PlainMap::Drow(TextureColorMapBoneArgs *args) {
    args->Calc();
    for(auto &bone: args->bones) {
        args->Bind(bone);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}
void PlainMap::Drow(TextureColorMapBodyArgs *args) {
    args->Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

