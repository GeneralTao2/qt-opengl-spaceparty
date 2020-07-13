#ifndef MAIN_TOOL_H
#define MAIN_TOOL_H

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

static const unsigned int SCR_WIDTH = 1000;
static const unsigned int SCR_HEIGHT = 600;

std::ostream &operator<< (std::ostream &out, const glm::vec2 &vec);
std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec);
std::ostream &operator<< (std::ostream &out, const glm::vec4 &vec);

void vecInArray(std::vector<float> &array, glm::vec2 value);
void vecInArray(std::vector<float> &array, glm::vec3 value);
void vecInArray(std::vector<float> &array, glm::vec4 value);

struct MoveTimeLine {
    GLfloat dx;
    GLfloat end;
};

struct BoneTimeChain {
    std::vector< MoveTimeLine > chain;
    bool enable = true;
    GLfloat time;
    size_t index;
    BoneTimeChain(std::vector< MoveTimeLine > Chain, GLfloat Time)
        : chain(Chain), time(Time) {
        index = 0;
    }
    BoneTimeChain() {

    }
    MoveTimeLine& front() {
        return chain[index];
    }
    MoveTimeLine& pop() {
        return chain[index++];
    }
    bool isEmpty() {
        return index >= chain.size();
    }
    void reset() {
        index = 0;
    }
};

struct MoveAction {
    std::vector<BoneTimeChain> *head;
    std::vector<BoneTimeChain> *leftHand;
    std::vector<BoneTimeChain> *rightHand;
    std::vector<BoneTimeChain> *leftLeg;
    std::vector<BoneTimeChain> *rightLeg;
    BoneTimeChain& getHead(size_t i) {
        return (*head)[i];
    }
    BoneTimeChain& getLeftHand(size_t i) {
        return (*leftHand)[i];
    }
    BoneTimeChain& getRightHand(size_t i) {
        return (*rightHand)[i];
    }
    BoneTimeChain& getLeftLeg(size_t i) {
        return (*leftLeg)[i];
    }
    BoneTimeChain& getRightLeg(size_t i) {
        return (*rightLeg)[i];
    }
    MoveAction(size_t headSize, size_t leftHandSize, size_t rightHandSize,
               size_t leftLegSize, size_t rightLegSize) {
        head = new std::vector<BoneTimeChain>(headSize);
        leftHand = new std::vector<BoneTimeChain>(leftHandSize);
        rightHand = new std::vector<BoneTimeChain>(rightHandSize);
        leftLeg = new std::vector<BoneTimeChain>(leftLegSize);
        rightLeg = new std::vector<BoneTimeChain>(rightLegSize);
    }
    ~MoveAction() {
        delete head;
        delete leftHand;
        delete rightHand;
        delete leftLeg;
        delete rightLeg;
    }
};

struct MovePoint {
    glm::vec2 position;
    GLfloat angle;
};

struct MoveTimer {
    GLfloat dx;
    GLint cadre;
    bool enable;
};

struct Bone {
    glm::vec2 scale;
    glm::vec4 textureCoords;
    glm::mat4 model;
    MoveTimer timer;
    GLfloat Zindex;
    std::vector<MovePoint> points;
    void MoveTo(BoneTimeChain &chain) {
        MoveTimeLine &action = chain.front();
        float da = action.end - points[0].angle;
        timer.cadre = action.dx;
        timer.enable = true;
        timer.dx = da/action.dx;
    }
};

#endif // MAIN_TOOL_H
