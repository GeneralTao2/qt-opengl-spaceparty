#include "shader_arg_structs.h"

void ColorArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetVector3f("color", color);
    shader.SetMatrix4("model", model);
}

void TextureColorArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, Zindex) );
    model = glm::rotate(model, angle, glm::vec3(axes , 1));
    model = glm::scale(model, glm::vec3(scale, 1));
    shader.Use();
    shader.SetInteger("plain", 0);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader.SetVector3f("color", color);
    shader.SetMatrix4("model", model);
}

void TextureColorMapBoneArgs::Calc() {
    for(auto &bone: bones) {
        for(auto &point: bone.points) {
            model = glm::translate(model, glm::vec3(point.position, 0) );
            model = glm::rotate(model, point.angle, glm::vec3(0, 0, 1));
        }
        bone.model = glm::translate(model, glm::vec3(0,0, bone.Zindex) );
        bone.model = glm::scale(bone.model, glm::vec3(bone.scale, 1));
    }
}

void TextureColorMapBoneArgs::Bind(Bone &bone) {
    shader.Use();
    shader.SetInteger("plain", 0);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader.SetVector4f("textureCoords", bone.textureCoords);
    shader.SetVector3f("color", color);
    shader.SetMatrix4("model", bone.model);
}


void TextureColorMapBodyArgs::Bind() {
    model = glm::translate(model, glm::vec3(position, 1) );
    model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
    glm::mat4 localModel = glm::translate(model, glm::vec3(0,0, Zindex) );
    localModel = glm::scale(localModel, glm::vec3(scale, 1));
    shader.Use();
    shader.SetInteger("plain", 0);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader.SetVector4f("textureCoords", textureCoords);
    shader.SetVector3f("color", color);
    shader.SetMatrix4("model", localModel);
}


void PostProcessingArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetInteger("mode", postProc.mode);
    shader.SetFloat("exposure", postProc.exposure);
    shader.SetFloat("offset", postProc.offset);
    shader.SetFloat("gamma", postProc.gamma);
    shader.SetVector1fArray("kernelMat",
           postProc.kernelMats[postProc.currentMat]);
}










