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
    glm::mat4 model;
    GLfloat &scale;
    glm::vec3 color;
    Texture2D &texture;
    Shader &shader;
    TextureColorMapBoneArgs(TextureColorMapBoneArgs &a) = default;
    TextureColorMapBoneArgs(std::vector<Bone> Bones, GLfloat &Scale, glm::vec3 Color, Texture2D &Texture_, Shader &Shader_)
        : bones(Bones), scale(Scale), color(Color), texture(Texture_), shader(Shader_){}
    BoneTimeChain& getTimeLine(size_t i) {
        return (*timeLine)[i];
    }
    void Calc();
    void Bind(Bone &bone);
};

struct TextureColorMapBodyArgs {
    Bone bone;
    GLfloat scale;
    glm::vec3 color;
    Texture2D &texture;
    Shader &shader;
    glm::mat4 model;
    BoneTimeChain *timeLine;
    BoneTimeChain& getTimeLine() {
        return *timeLine;
    }
    TextureColorMapBodyArgs(TextureColorMapBodyArgs &a) = default;
    TextureColorMapBodyArgs(Bone Bone_, GLfloat Scale, glm::vec3 Color, Texture2D &Texture, Shader &Shader_)
     : bone(Bone_), scale(Scale), color(Color), texture(Texture),
       shader(Shader_), model(glm::mat4(1)), timeLine(nullptr)
    {

    }
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
