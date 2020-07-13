#include "rig.h"

Rig::Rig(PlainMap *PLAINMAP) : plainMap(PLAINMAP)
{
    Init();
}

Rig::~Rig() {
    delete leftHand;
    delete rightHand;
    delete leftLeg;
    delete rightLeg;
    delete head;
    delete torso;
    delete runing;
}

void Rig::Init() {
    torso = new TextureColorMapBodyArgs({
        .position = {200, 180},
        .scale = {80, 120},
        .angle = 0,
        .Zindex = 0.5,
        .model = glm::mat4(1),
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .textureCoords = {0.1,0,0.08,0.12},
        .shader = RM::GetShader("texture_color_plain_map")
                                                          });
    leftHand = new TextureColorMapBoneArgs({
        .bones = {
        {
            {32, 80},
            {0.18, 0,  0.032, 0.08},
            glm::mat4(1),
            {0, 0, false},
            0.8,
            {
                { {-30, -60}, 0 },
                { {0, 40}, 0 }

            }
        }, {
            {32, 90},
            {0.18, 0.08,  0.032, 0.09},
            glm::mat4(1),
            {0, 0, false},
            0.81,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        }
        },
        .timeLine = nullptr,
        .model = glm::mat4(1),
        .layer = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .shader = RM::GetShader("texture_color_plain_map")
      });
    rightHand = new TextureColorMapBoneArgs({
        .bones = {
        {
            {32, 80},
            {0.212, 0,  0.032, 0.08},
            glm::mat4(1),
            {0, 0, false},
            0.3,
            {
                { {30, -60}, 0 },
                { {0, 40}, 0 }

            }
        }, {
            {32, 90},
            {0.212, 0.08,  0.032, 0.09},
            glm::mat4(1),
            {0, 0, false},
            0.31,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        }
        },
        .timeLine = nullptr,
        .model = glm::mat4(1),
        .layer = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .shader = RM::GetShader("texture_color_plain_map")
      });
    leftLeg = new TextureColorMapBoneArgs({
        .bones = {
        {
            {32, 80},
            {0.244, 0,  0.032, 0.08},
            glm::mat4(1),
            {0, 0, false},
            0.6,
            {
                { {-24, 50}, 0 },
                { {0, 40}, 0 }

            }
        }, {
            {32, 90},
            {0.244, 0.08,  0.032, 0.09},
            glm::mat4(1),
            {0, 0, false},
            0.61,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        }
        },
        .timeLine = nullptr,
        .model = glm::mat4(1),
        .layer = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .shader = RM::GetShader("texture_color_plain_map")
      });
    rightLeg = new TextureColorMapBoneArgs({
        .bones = {
        {
            {32, 80},
            {0.276, 0,  0.032, 0.08},
            glm::mat4(1),
            {0, 0, false},
            0.4,
            {
                { {24, 50}, 0 },
                { {0, 40}, 0 }

            }
        }, {
            {32, 90},
            {0.276, 0.08,  0.032, 0.09},
            glm::mat4(1),
            {0, 0, false},
            0.41,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        }
        },
        .timeLine = nullptr,
        .model = glm::mat4(1),
        .layer = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .shader = RM::GetShader("texture_color_plain_map")
      });
    head = new TextureColorMapBoneArgs({
        .bones = {
        {
            {100, 100},
            {0, 0,  0.1, 0.1},
            glm::mat4(1),
            {0, 0, false},
            0.9,
            {
                { {0, -60}, 0 },
                { {0, -50}, 0 }

            }
        }
        },
        .timeLine = nullptr,
        .model = glm::mat4(1),
        .layer = 0,
        .color = {1, 1, 0.5},
        .texture = RM::GetTexture("player_map"),
        .shader = RM::GetShader("texture_color_plain_map")
      });
    runing = new MoveAction({
        head->bones.size(),
        leftHand->bones.size(),
        rightHand->bones.size(),
        leftLeg->bones.size(),
        rightLeg->bones.size(),
      });

    head->bones[0].points[0].angle = PI/9;
    leftHand->bones[0].points[0].angle = PI/5;
    leftHand->bones[1].points[0].angle = -PI/3;
    rightHand->bones[0].points[0].angle = -PI/6;
    rightHand->bones[1].points[0].angle = -PI/8;
    leftLeg->bones[0].points[0].angle = PI/6;
    leftLeg->bones[1].points[0].angle = 0;
    rightLeg->bones[0].points[0].angle = -PI/6;
    rightLeg->bones[1].points[0].angle = 0;

    runing->getHead(0) =        BoneTimeChain({ {30, PI/11}, {30, PI/9},   {30, PI/11},   {30, PI/9},  {30, PI/11},   {30, PI/9},   {30, PI/11},      }, 3);
    runing->getLeftHand(0) =    BoneTimeChain({ {30, PI/12},{30, PI/9},   {30, PI/7.5f},{30, PI/6}, {30, PI/9},    {30, -PI/12}, {30, -PI/10},    }, 3);
    runing->getLeftHand(1) =    BoneTimeChain({ {30, -PI/4},{30, -PI/3},  {30, -PI/3},  {30, -PI/8}, {30, -PI/9},{30, -PI/9},  {30, -PI/9},      }, 3);
    runing->getRightHand(0) =   BoneTimeChain({ {30, 0},    {30, -PI/12}, {30, -PI/10}, {30, PI/5},  {30, PI/12},{30, PI/9},   {30, PI/7.5f},         }, 3);
    runing->getRightHand(1) =   BoneTimeChain({ {30, -PI/9},{30, -PI/9},  {30, -PI/9},  {30, -PI/3}, {30, -PI/4},{30, -PI/3},  {30, -PI/3},       }, 3);
    runing->getLeftLeg(0) =     BoneTimeChain({ {30, 0},    {30, -PI/6},  {30, -PI/5},  {30, -PI/6}, {30, -PI/6},{30, 0},      {30, PI/13},           }, 3);
    runing->getLeftLeg(1) =     BoneTimeChain({ {30, PI/4}, {30, PI/3},   {30, PI/5},   {30, 0},     {30, PI/6}, {30, 0},      {30, 0},      }, 3);
    runing->getRightLeg(0) =    BoneTimeChain({ {30, -PI/6},{30, 0},      {30, PI/13},  {30, PI/6},  {30, 0},    {30, -PI/6},  {30, -PI/5},      }, 3);
    runing->getRightLeg(1) =    BoneTimeChain({ {30, PI/6}, {30, 0},      {30, 0},      {30, 0},     {30, PI/4}, {30, PI/3},   {30, PI/5},    }, 3);

    head->timeLine =        runing->head;
    leftHand->timeLine =    runing->leftHand;
    rightHand->timeLine =   runing->rightHand;
    leftLeg->timeLine =     runing->leftLeg;
    rightLeg->timeLine =    runing->rightLeg;

}

void Rig::Draw() {
    torso->model = glm::mat4(1);
    plainMap->Drow(torso);
    leftHand->model = torso->model;
    rightHand->model = torso->model;
    leftLeg->model = torso->model;
    rightLeg->model = torso->model;
    head->model = torso->model;

    ProcessAnimation();
    ProcessMove();

    Run();

    plainMap->Drow(leftHand);
    plainMap->Drow(rightHand);
    plainMap->Drow(leftLeg);
    plainMap->Drow(rightLeg);
    plainMap->Drow(head);
}

void Rig::Moving(TextureColorMapBoneArgs *part) {
    for(size_t i=0; i< part->bones.size(); i++) {
        if(part->bones[i].timer.enable) {

            if(part->bones[i].timer.cadre == 0 ) {
                part->bones[i].timer.enable = false;
                if(part->getTimeLine(i).isEmpty()) {
                    part->getTimeLine(i).reset();
                    part->bones[i].MoveTo(part->getTimeLine(i));
                    part->getTimeLine(i).pop();
                } else {
                    part->bones[i].MoveTo(part->getTimeLine(i));
                    part->getTimeLine(i).pop();
                }
            }

            part->bones[i].points[0].angle += part->bones[i].timer.dx;
            part->bones[i].timer.cadre--;
        }
    }
}

void Rig::ProcessAnimation() {
    GLfloat time = glfwGetTime();
    for(size_t i=0; i<runing->head->size(); i++) {
        if(runing->getHead(i).enable && (time > runing->getHead(i).time)) {
            if(runing->getHead(i).isEmpty()) {

            } else {
                head->bones[i].MoveTo(runing->getHead(i));
                runing->getHead(i).pop();
                runing->getHead(i).enable = false;
            }
        }
    }

    for(size_t i=0; i<runing->leftHand->size(); i++) {
        if(runing->getLeftHand(i).enable && (time > runing->getLeftHand(i).time)) {
            if(runing->getLeftHand(i).isEmpty()) {

            } else {
                leftHand->bones[i].MoveTo(runing->getLeftHand(i));
                runing->getLeftHand(i).pop();
                runing->getLeftHand(i).enable = false;
            }
        }
    }

    for(size_t i=0; i<runing->rightHand->size(); i++) {
        if(runing->getRightHand(i).enable && (time > runing->getRightHand(i).time)) {
            if(runing->getRightHand(i).isEmpty()) {

            } else {
                rightHand->bones[i].MoveTo(runing->getRightHand(i));
                runing->getRightHand(i).pop();
                runing->getRightHand(i).enable = false;
            }
        }
    }

    for(size_t i=0; i<runing->leftLeg->size(); i++) {
        if(runing->getLeftLeg(i).enable && (time > runing->getLeftLeg(i).time)) {
            if(runing->getLeftLeg(i).isEmpty()) {

            } else {
                leftLeg->bones[i].MoveTo(runing->getLeftLeg(i));
                runing->getLeftLeg(i).pop();
                runing->getLeftLeg(i).enable = false;
            }
        }
    }

    for(size_t i=0; i<runing->rightLeg->size(); i++) {
        if(runing->getRightLeg(i).enable && (time > runing->getRightLeg(i).time)) {
            if(runing->getRightLeg(i).isEmpty()) {

            } else {
                rightLeg->bones[i].MoveTo(runing->getRightLeg(i));
                runing->getRightLeg(i).pop();
                runing->getRightLeg(i).enable = false;
            }
        }
    }

}

void Rig::ProcessMove() {
    Moving(leftHand);
    Moving(rightHand);
    Moving(leftLeg);
    Moving(rightLeg);
    Moving(head);
}
void Rig::Run() {


}
