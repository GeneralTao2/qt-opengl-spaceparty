#include "process_input.h"

float PI::lastX = SCR_WIDTH / 2.0f;
float PI::lastY = SCR_HEIGHT / 2.0f;
bool PI::firstMouse = true;

// timing
float PI::deltaTime = 0.0f;
float PI::lastFrame = 0.0f;

bool PI::cursorFlag = false;
float PI::lastCursorReaction = 0;

PI::PI()
{

}
void PI::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(cursorFlag)
        return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

void PI::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(cursorFlag)
        return;
    camera.ProcessMouseScroll(yoffset);
}

void PI::processInput(GLFWwindow *window)
{
    bool cursorEnabling = (glfwGetTime() - lastCursorReaction) > 0.3;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if ( ( glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ) && cursorEnabling) {
        if(cursorFlag) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorFlag = !cursorFlag;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursorFlag = !cursorFlag;
        }
        lastCursorReaction = glfwGetTime();
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void PI::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
