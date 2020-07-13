#include "resource_manager.h"


std::map<std::string, Texture2D>           RM::Textures;
std::map<std::string, Shader>              RM::Shaders;
std::map<std::string, std::vector<float>>  RM::Vertices;
std::string                                RM::path;
std::string                                RM::toShaders;
std::string                                RM::toVertices;
std::string                                RM::toTextures;

void RM::RM_Init() {
    RM::path = "C://Users//ar725//Documents//qt//spacepaty//";
    RM::toShaders = "settings//shaders//";
    RM::toTextures = "settings//textures//";
    RM::toVertices = "settings//vertices//";

    RM::LoadShader("plain//plain.vert", "plain//plain.frag", "", "plain");
    RM::LoadShader("texture_color_plain//texture_color_plain.vert",
                   "texture_color_plain//texture_color_plain.frag", "", "texture_color_plain");
    RM::LoadShader("texture_color_plain_map//texture_color_plain_map.vert",
                   "texture_color_plain_map//texture_color_plain_map.frag", "",
                   "texture_color_plain_map");

    RM::LoadTexture("box.png", true, "box");
    RM::LoadTexture("map.png", true, "player_map");
    RM::LoadTexture("bg.png", true, "bg");
    RM::LoadTexture("ground.png", true, "ground");

}

Shader RM::LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}


Shader &RM::GetShader(std::string name)
{
    if(!Shaders.count(name))
        std::cout << "Error! Shaders doesn't has " << name << std::endl;
    return Shaders[name];
}

Texture2D RM::LoadTexture(std::string file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}
Texture2D &RM::GetTexture(std::string name)
{
    if(!Textures.count(name))
        std::cout << "Error! Textures doesn't has " << name << std::endl;
    return Textures[name];
}


std::vector<float> RM::LoadVertices(std::string file, std::string name) {
    Vertices[name] = loadVerticesFromFile(file);
    return Vertices[name];
}
std::vector<float>  &RM::GetVertices(std::string name) {
    if(!Vertices.count(name))
        std::cout << "Error! Vertices doesn't has " << name << std::endl;
    return Vertices[name];
}
void RM::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader RM::loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open files
        std::ifstream vertexShaderFile(path + toShaders + vShaderFile);
        std::ifstream fragmentShaderFile(path + toShaders + fShaderFile);
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != "")
        {
            std::ifstream geometryShaderFile(path + toShaders + gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}

Texture2D RM::loadTextureFromFile(std::string file, GLboolean alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    file = path + toTextures + file;
    int width, height;
    unsigned char* image = stbi_load(file.c_str(), &width, &height, 0, texture.Image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);
    if(!image) {
        std::cout << "Error! Failed to load texture from " << file << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
    texture.Generate(width, height, image);
    stbi_image_free(image);
    return texture;
}

Texture2D RM::loadTextureFromFileMat(std::string file, GLboolean alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    file = path + toTextures + file;
    int width, height;
    unsigned char* image = stbi_load(file.c_str(), &width, &height, 0, texture.Image_Format == GL_RGBA ? GL_RGBA : GL_RGB);
    texture.Generate(width, height, image);
    stbi_image_free(image);
    return texture;
}
std::vector<float>  RM::loadVerticesFromFile(std::string file) {
    std::vector<float> vertices;
    try {
        std::ifstream in(path + toVertices + file);
        if(!in.is_open())
            throw std::exception();
        float v;
        while(in >> v) {
            vertices.push_back(v);
        }
    } catch (std::exception e) {
        std::cout << "ERROR::VERTICES: Failed to read shader files" << std::endl;
    }
    return vertices;
}
unsigned int RM::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

