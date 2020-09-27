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
    actionChangeOnceEx = false;
    dx = glm::vec2(1, 0);
    scale = 0.5;
    state = STAND;
    position = {200, 180};
    texture = RM::GetTexture("player_map");
    shader = RM::GetShader("texture_color_plain_map");
    torso = new TextureColorMapBodyArgs(
       Bone(
            {80, 120},
            {0.1,0,0.08,0.12},
            0.5,
            {
                { position, 0 }
            }
        ),
        scale,
        {1, 1, 0.5},
        texture,
        shader
    );
    leftHand = new TextureColorMapBoneArgs(
        {
        Bone(
            {32, 80},
            {0.18, 0,  0.032, 0.08},
            0.8,
            {
                { {-30, -60}, 0 },
                { {0, 40}, 0 }
            }
        ), Bone(
            {32, 90},
            {0.18, 0.08,  0.032, 0.09},
            0.81,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        )
        },
        scale,
        {1, 1, 0.5},
        texture,
        shader
      );
    rightHand = new TextureColorMapBoneArgs(
        {
        Bone(
            {32, 80},
            {0.212, 0,  0.032, 0.08},
            0.3,
            {
                { {30, -60}, 0 },
                { {0, 40}, 0 }

            }
        ), Bone(
            {32, 90},
            {0.212, 0.08,  0.032, 0.09},
            0.31,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        )
        },
        scale,
        {1, 1, 0.5},
        texture,
        shader
      );
    leftLeg = new TextureColorMapBoneArgs(
        {
        Bone(
            {32, 80},
            {0.244, 0,  0.032, 0.08},
            0.6,
            {
                { {-24, 50}, 0 },
                { {0, 40}, 0 }

            }
        ), Bone(
            {32, 90},
            {0.244, 0.08,  0.032, 0.09},
            0.61,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        )
        },
        scale,
        {1, 1, 0.5},
        texture,
        shader
      );
    rightLeg = new TextureColorMapBoneArgs(
        {
        Bone(
            {32, 80},
            {0.276, 0,  0.032, 0.08},
            0.4,
            {
                { {24, 50}, 0 },
                { {0, 40}, 0 }

            }
        ), Bone(
            {32, 90},
            {0.276, 0.08,  0.032, 0.09},
            0.41,
            {
                { {0, 45}, 0 },
                { {0, 25}, 0 }
            }
        )
        },
        scale,
        {1, 1, 0.5},
        texture,
        shader
      );
    head = new TextureColorMapBoneArgs(
        {
        Bone(
            {100, 100},
            {0, 0,  0.1, 0.1},
            0.9,
            {
                { {0, -60}, 0 },
                { {0, -50}, 0 }

            }
        )
        },
        scale,
        {1, 1, 0.5},
        texture,
        shader
      );

    runing = new MoveAction(
        head->bones.size(),
        leftHand->bones.size(),
        rightHand->bones.size(),
        leftLeg->bones.size(),
        rightLeg->bones.size(),
        {15, 15, 15, 15, 15, 15, 15, 15},
        true, true
      );

    runing->getTorso() =        BoneTimeChain({ 0,      0,      0,      0,      0,      0,     0,       0,     }, 0, runing->clipKeys, runing->clipable);
    runing->getHead(0) =        BoneTimeChain({PI/11,   PI/9,   PI/11, PI/9,   PI/11,   PI/9,  PI/11,  PI/9,   }, 0, runing->clipKeys, runing->clipable);
    runing->getLeftHand(0) =    BoneTimeChain({PI/7.5f, PI/6,   PI/9,  -PI/12, -PI/10,  -PI/6,  PI/12, PI/9,   }, 0, runing->clipKeys, runing->clipable);
    runing->getLeftHand(1) =    BoneTimeChain({-PI/3,   -PI/8,  -PI/9, -PI/9,  -PI/9,   -PI/8, -PI/4,  -PI/3,  }, 0, runing->clipKeys, runing->clipable);
    runing->getRightHand(0) =   BoneTimeChain({-PI/10,  -PI/8,  PI/12, PI/9,   PI/7.5f, PI/5, 0,       -PI/12, }, 0, runing->clipKeys, runing->clipable);
    runing->getRightHand(1) =   BoneTimeChain({-PI/9,   -PI/8,  -PI/4, -PI/3,  -PI/3,   -PI/3, -PI/9,  -PI/9,  }, 0, runing->clipKeys, runing->clipable);
    runing->getLeftLeg(0) =     BoneTimeChain({-PI/5,   -PI/6,  -PI/6, 0,      PI/13,   PI/6,  0,      -PI/6,  }, 0, runing->clipKeys, runing->clipable);
    runing->getLeftLeg(1) =     BoneTimeChain({PI/5,    0,      PI/6,  0,      0,       0,     PI/4,   PI/3,   }, 0, runing->clipKeys, runing->clipable);
    runing->getRightLeg(0) =    BoneTimeChain({PI/13,   PI/6,   0,     -PI/6,  -PI/5,   -PI/6, -PI/6,  0,      }, 0, runing->clipKeys, runing->clipable);
    runing->getRightLeg(1) =    BoneTimeChain({0,       0,      PI/4,  PI/3,   PI/5,    0,     PI/6,   0,      }, 0, runing->clipKeys, runing->clipable);

    standRack = {
        .torso      = 0,
        .head       = PI/15,
        .leftHand1  = PI/15,
        .leftHand2  = -PI/15,
        .rightHand1 = PI/15,
        .rightHand2 = -PI/15,
        .leftLeg1   = 0,
        .leftLeg2   = 0,
        .rightLeg1  = 0,
        .rightLeg2  = 0,
    };

    runToStand = new MoveAction(head->bones.size(),
                              leftHand->bones.size(),
                              rightHand->bones.size(),
                              leftLeg->bones.size(),
                              rightLeg->bones.size(),{15}, false, false);
    runToStand->addRock(standRack);

    SetInitialRack(standRack);

    SetMoveAction(runing);
}

void Rig::ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        state = RUN;
    } else {
        //state = STAND;
        if(state == RUN){
            state = RUNtoSTAND;
        }
    }
}

void Rig::ProcessMove() {
    if(currentAction->enabled) {
        std::cout << state;
        //std::cout << currentAction->getHead(0).clipKeys->size();
        Moving(torso);
        Moving(leftHand);
        Moving(rightHand);
        Moving(leftLeg);
        Moving(rightLeg);
        Moving(head);
    }
}
void Rig::Move() {

    if(lastState != state) {
        actionChangeOnceEx = true;
    }

    if(state == RUN) {
        if(actionChangeOnceEx) {
            SetMoveAction(runing);
            runing->reset();
            runing->enable();
            actionChangeOnceEx = false;
        }
        if(torso->bone.points[0].position.x > 1000 || torso->bone.points[0].position.x < 0) {
            dx.x *= -1;
        }
        torso->bone.points[0].position += dx;
    }

    if(state == RUNtoSTAND) {
        if(actionChangeOnceEx) {
            runing->disable();
            runing->reset();
            runToStand->enable();
            SetMoveAction(runToStand);
            actionChangeOnceEx = false;
        }
        //std::cout << head->bones[0].timer.cadre;
        if(currentAction->getHead(0).isEmpty() &&
                !head->bones[0].timer.enable) {
            //std::cout << state;
            //currentAction->disable();
            currentAction->reset();
            state = STAND;
        }
    }

    lastState = state;
}

void Rig::SetInitialRack(RigRack rack) {
    torso       ->bone.points[0].angle     = rack.torso;
    head        ->bones[0].points[0].angle = rack.head;
    leftHand    ->bones[0].points[0].angle = rack.leftHand1;
    leftHand    ->bones[1].points[0].angle = rack.leftHand2;
    rightHand   ->bones[0].points[0].angle = rack.rightHand1;
    rightHand   ->bones[1].points[0].angle = rack.rightHand2;
    leftLeg     ->bones[0].points[0].angle = rack.leftLeg1;
    leftLeg     ->bones[1].points[0].angle = rack.leftLeg2;
    rightLeg    ->bones[0].points[0].angle = rack.rightLeg1;
    rightLeg    ->bones[1].points[0].angle = rack.rightLeg2;
}

void Rig::SetMoveAction(MoveAction *moveAction) {
    currentAction = moveAction;
    torso->timeLine =       currentAction->torso;
    head->timeLine =        currentAction->head;
    leftHand->timeLine =    currentAction->leftHand;
    rightHand->timeLine =   currentAction->rightHand;
    leftLeg->timeLine =     currentAction->leftLeg;
    rightLeg->timeLine =    currentAction->rightLeg;
}

void Rig::Draw() {
    torso->model = glm::mat4(1);
    plainMap->Drow(torso);
    leftHand->model = torso->model;
    rightHand->model = torso->model;
    leftLeg->model = torso->model;
    rightLeg->model = torso->model;
    head->model = torso->model;

    Move();

    ProcessAnimation();
    ProcessMove();

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
                    if(currentAction->reversibil) {
                        part->getTimeLine(i).reset();
                        part->bones[i].MoveTo(part->getTimeLine(i));
                        part->getTimeLine(i).pop();
                    } else {
                        //currentAction->disable();
                    }
                } else {
                    part->bones[i].MoveTo(part->getTimeLine(i));
                    part->getTimeLine(i).pop();
                }
            }
            if(state == RUNtoSTAND) {
                int a = 1;
            }
            part->bones[i].points[0].angle += part->bones[i].timer.dx;
            part->bones[i].timer.cadre--;
        }
    }
}

void Rig::Moving(TextureColorMapBodyArgs *body) {
    if(body->bone.timer.enable) {

        if(body->bone.timer.cadre == 0 ) {
            body->bone.timer.enable = false;
            if(body->getTimeLine().isEmpty()) {
                if(currentAction->reversibil) {
                    body->getTimeLine().reset();
                    body->bone.MoveTo(body->getTimeLine());
                    body->getTimeLine().pop();
                } else {
                    //currentAction->disable();
                }
            } else {
                body->bone.MoveTo(body->getTimeLine());
                body->getTimeLine().pop();
            }
        }
        body->bone.points[0].angle += body->bone.timer.dx;
        body->bone.timer.cadre--;
    }
}

void Rig::ProcessAnimation() {
    GLfloat time = glfwGetTime();
    if(currentAction->started) {

        if(currentAction->getTorso().isEmpty()) {

        } else {
            torso->bone.MoveTo(currentAction->getTorso());
            currentAction->getTorso().pop();
        }

        for(size_t i=0; i<currentAction->head->size(); i++) {
            if(currentAction->getHead(i).isEmpty()) {

            } else {
                head->bones[i].MoveTo(currentAction->getHead(i));
                currentAction->getHead(i).pop();
            }
        }

        for(size_t i=0; i<currentAction->leftHand->size(); i++) {
            if(currentAction->getLeftHand(i).isEmpty()) {

            } else {
                leftHand->bones[i].MoveTo(currentAction->getLeftHand(i));
                currentAction->getLeftHand(i).pop();
            }
        }

        for(size_t i=0; i<currentAction->rightHand->size(); i++) {
            if(currentAction->getRightHand(i).isEmpty()) {

            } else {
                rightHand->bones[i].MoveTo(currentAction->getRightHand(i));
                currentAction->getRightHand(i).pop();
            }
        }

        for(size_t i=0; i<currentAction->leftLeg->size(); i++) {
            if(currentAction->getLeftLeg(i).isEmpty()) {

            } else {
                leftLeg->bones[i].MoveTo(currentAction->getLeftLeg(i));
                currentAction->getLeftLeg(i).pop();
            }
        }

        for(size_t i=0; i<currentAction->rightLeg->size(); i++) {
            if(currentAction->getRightLeg(i).isEmpty()) {

            } else {
                rightLeg->bones[i].MoveTo(currentAction->getRightLeg(i));
                currentAction->getRightLeg(i).pop();
            }
        }
    currentAction->started = false;
    }

}

