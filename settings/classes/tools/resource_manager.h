#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "stb_image.h"
#include <settings/libs/glad/glad.h>
#include "texture.h"
#include "shader.h"
#include "decor.h"

class RM
{
public:
    //configs
    static std::string path;
    static std::string toShaders;
    static std::string toVertices;
    static std::string toTextures;
    //shader
    static std::map<std::string, Shader>    Shaders;
    static Shader   LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name);
    static Shader   &GetShader(std::string name);
    //texture
    static std::map<std::string, Texture2D> Textures;
    static Texture2D LoadTexture(std::string file, GLboolean alpha, std::string name);
    static Texture2D &GetTexture(std::string name);
    //vertices
    static std::map<std::string, std::vector<float>> Vertices;
    static std::vector<float> LoadVertices(std::string file, std::string name);
    static std::vector<float> &GetVertices(std::string name);
    //private
    static void      Clear();
    static Shader    loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile = nullptr);
    static std::vector<float> loadVerticesFromFile(std::string file);
    static Texture2D loadTextureFromFile(std::string file, GLboolean alpha);
    static Texture2D loadTextureFromFileMat(std::string file, GLboolean alpha);
    static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = 0);

    static void RM_Init();
private:
    RM() { }
};

#endif // RESOURCE_MANAGER_H
