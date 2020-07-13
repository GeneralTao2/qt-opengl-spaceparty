#ifndef SHADER_ARG_STRUCTS_H
#define SHADER_ARG_STRUCTS_H

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "resource_manager.h"
#include "main_tool.h"

struct ColorArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 color;
    Shader shader;
    void Bind();
};

struct TextureColorArgs {
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 axes;
    float angle;
    GLfloat Zindex;
    glm::vec3 color;
    Texture2D texture;
    Shader shader;
    void Bind();
};

struct TextureColorMapBoneArgs {
    std::vector<Bone> bones;
    std::vector<BoneTimeChain> *timeLine;
    BoneTimeChain& getTimeLine(size_t i) {
        return (*timeLine)[i];
    }
    glm::mat4 model;
    size_t layer;
    glm::vec3 color;
    Texture2D texture;
    Shader shader;
    void Calc();
    void Bind(Bone &bone);
};

struct TextureColorMapBodyArgs {
    glm::vec2 position;
    glm::vec2 scale;
    GLfloat angle;
    GLfloat Zindex;
    glm::mat4 model;
    glm::vec3 color;
    Texture2D texture;
    glm::vec4 textureCoords;
    Shader shader;
    void Bind();
};

struct PostProcessingArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    PostProcessing postProc;
    Shader shader;
    void Bind();
};


#endif // SHADER_ARG_STRUCTS_H
