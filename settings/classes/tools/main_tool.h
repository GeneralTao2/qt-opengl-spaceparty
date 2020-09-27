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

std::ostream &operator<< (std::ostream &out, const glm::mat4 &mat);

void vecInArray(std::vector<float> &array, glm::vec2 value);
void vecInArray(std::vector<float> &array, glm::vec3 value);
void vecInArray(std::vector<float> &array, glm::vec4 value);

struct BoneTimeChain {
    std::vector<GLfloat> chain;
    std::vector<GLfloat> *clipKeys;
    GLfloat time;
    size_t index;
    bool clipable;
    BoneTimeChain(std::vector<GLfloat> Chain, GLfloat Time, std::vector<GLfloat> *ClipKeys,
                  bool Clipable)
        : chain(Chain), clipKeys(ClipKeys), time(Time), clipable(Clipable) {
        index = 0;
    }
    BoneTimeChain() {

    }
    GLfloat& getClipKey() {
        return (*clipKeys)[index];
    }
    GLfloat& front() {
        return chain[index];
    }
    GLfloat& pop() {
        return chain[index++];
    }
    bool isEmpty() {
        return index >= chain.size();
    }
    void reset() {
        index = 0;
    }
};

struct RigRack {
    GLfloat torso;
    GLfloat head;
    GLfloat leftHand1;
    GLfloat leftHand2;
    GLfloat rightHand1;
    GLfloat rightHand2;
    GLfloat leftLeg1;
    GLfloat leftLeg2;
    GLfloat rightLeg1;
    GLfloat rightLeg2;
};

struct MoveAction {
    std::vector<GLfloat> *clipKeys;
    std::vector<BoneTimeChain> *head;
    std::vector<BoneTimeChain> *leftHand;
    std::vector<BoneTimeChain> *rightHand;
    std::vector<BoneTimeChain> *leftLeg;
    std::vector<BoneTimeChain> *rightLeg;
    BoneTimeChain *torso;
    bool started = true;
    bool enabled = false;
    bool reversibil = false;
    bool clipable = false;
    void enable() {
        enabled = true;
    }
    void disable() {
        enabled = false;
    }
    BoneTimeChain& getTorso() {
        return *torso;
    }
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
               size_t leftLegSize, size_t rightLegSize, std::initializer_list<GLfloat> ClipKeys,
               bool Reversibil, bool Clipable) : reversibil(Reversibil), clipable(Clipable) {
        torso = new BoneTimeChain;
        head = new std::vector<BoneTimeChain>(headSize);
        leftHand = new std::vector<BoneTimeChain>(leftHandSize);
        rightHand = new std::vector<BoneTimeChain>(rightHandSize);
        leftLeg = new std::vector<BoneTimeChain>(leftLegSize);
        rightLeg = new std::vector<BoneTimeChain>(rightLegSize);
        clipKeys = new std::vector<GLfloat>(ClipKeys);
    }
    void reset() {
        getTorso()      .reset();
        getHead(0)      .reset();
        getLeftHand(0)  .reset();
        getLeftHand(1)  .reset();
        getRightHand(0) .reset();
        getRightHand(1) .reset();
        getLeftLeg(0)   .reset();
        getLeftLeg(1)   .reset();
        getRightLeg(0)  .reset();
        getRightLeg(1)  .reset();
    }
    void addRock(RigRack rack) {
        getTorso()      = BoneTimeChain({rack.torso     }, 0, clipKeys, clipable);
        getHead(0)      = BoneTimeChain({rack.head      }, 0, clipKeys, clipable);
        getLeftHand(0)  = BoneTimeChain({rack.leftHand1 }, 0, clipKeys, clipable);
        getLeftHand(1)  = BoneTimeChain({rack.leftHand2 }, 0, clipKeys, clipable);
        getRightHand(0) = BoneTimeChain({rack.rightHand1}, 0, clipKeys, clipable);
        getRightHand(1) = BoneTimeChain({rack.rightHand2}, 0, clipKeys, clipable);
        getLeftLeg(0)   = BoneTimeChain({rack.leftLeg1  }, 0, clipKeys, clipable);
        getLeftLeg(1)   = BoneTimeChain({rack.leftLeg2  }, 0, clipKeys, clipable);
        getRightLeg(0)  = BoneTimeChain({rack.rightLeg1 }, 0, clipKeys, clipable);
        getRightLeg(1)  = BoneTimeChain({rack.rightLeg2 }, 0, clipKeys, clipable);
    }
    ~MoveAction() {
        delete head;
        delete leftHand;
        delete rightHand;
        delete leftLeg;
        delete rightLeg;
        delete clipKeys;
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
    GLfloat Zindex;
    std::vector<MovePoint> points;
    glm::mat4 model;
    MoveTimer timer;
    Bone(glm::vec2 Scale, glm::vec4 TextureCoords, GLfloat Zindex_, std::vector<MovePoint> Points)
        : scale(Scale), textureCoords(TextureCoords), Zindex(Zindex_), points(Points),
          model(glm::mat4(1)), timer({0, 0, false}){}
    void MoveTo(BoneTimeChain &chain) {
        GLfloat angel = chain.front();
        float da = angel - points[0].angle;
        timer.enable = true;
        if(chain.clipable) {
            timer.cadre = chain.getClipKey();
            timer.dx = da/chain.getClipKey();
        } else {
            /*timer.cadre = chain.getClipKey();
            timer.dx = da/chain.getClipKey();*/
            timer.cadre = fabs(da)/0.0697;
            if(timer.cadre == 0) {
                timer.cadre = 1;
                timer.dx = 0;
            }
            timer.dx = da > 0 ? 0.03 : -0.03;
        }
    }
};

#endif // MAIN_TOOL_H
