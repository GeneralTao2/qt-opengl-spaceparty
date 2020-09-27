#ifndef RIG_H
#define RIG_H
#include <glfw3.h>
#include <settings/classes/objects/plain_map.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/tools/main_tool.h>

enum RigState {
    STAND,
    RUN,
    RUNtoSTAND,
    WALK
};

class Rig
{
public:
    std::vector< std::vector<MovePoint> > points;
    PlainMap *plainMap;
    TextureColorMapBoneArgs *leftHand;
    TextureColorMapBoneArgs *rightHand;
    TextureColorMapBoneArgs *leftLeg;
    TextureColorMapBoneArgs *rightLeg;
    TextureColorMapBoneArgs *head;
    TextureColorMapBodyArgs *torso;
    MoveAction *currentAction;
    MoveAction *runing;
    MoveAction *runToStand;
    GLfloat scale;
    glm::vec2 position;
    glm::vec2 dx;
    RigState state;
    RigState lastState;
    RigRack standRack;
    Texture2D texture;
    Shader shader;
    bool actionChangeOnceEx;
    float PI = 3.14159265359;
    void Init();
    void Draw();
    void ProcessMove();
    void ProcessAnimation();
    void ProcessInput(GLFWwindow *window);
    void Moving(TextureColorMapBoneArgs *part);
    void Moving(TextureColorMapBodyArgs *body);
    void SetInitialRack(RigRack rack);
    void SetMoveAction(MoveAction *moveAction);
    void Move();
    Rig(PlainMap *PLAINMAP);
    ~Rig();
};

#endif // RIG_H
