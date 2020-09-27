#ifndef PORCESS_INPUT_H
#define PORCESS_INPUT_H

#include <glfw3.h>

#include <iostream>
#include <settings/classes/objects/camera.h>
#include <settings/classes/tools/game.h>
#include <settings/classes/tools/main_tool.h>

extern Camera camera;

class PI
{
public:
    static float lastX;
    static float lastY;
    static bool firstMouse;

    // timing
    static float deltaTime;
    static float lastFrame;

    static bool cursorFlag;
    static float lastCursorReaction;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow *window);
private:
    PI();
};

#endif // PORCESS_INPUT_H
