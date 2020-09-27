#ifdef _WIN32
    #define APIENTRY __stdcall
#endif
#include <settings/libs/src/glad.c>
#ifdef _WINDOWS_
#endif
#define GLEW_STATIC
#include <settings/libs/glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <settings/classes/objects/camera.h>
#include <settings/classes/tools/shader_global_buffer.h>
#include <settings/classes/tools/shader_arg_structs.h>
#include <settings/classes/objects/background.h>
#include <settings/classes/tools/process_input.h>

#include <settings/classes/tools/game.h>
using namespace std;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    cout << "Hello World!" << endl;
    camera.MovementSpeed = 20;
    // Setup window
    //glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER  , GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, PI::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, PI::mouse_callback);
    glfwSetScrollCallback(window, PI::scroll_callback);
    glfwSetWindowPos(window, 100, 300);
    glfwSwapInterval(1); // Enable vsync

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool err = gladLoadGL() == 0;

    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }
    RM::RM_Init();

    ShaderGlobalBuffer shProjView({ "plain", "texture_color_plain",
                                  "texture_color_plain_map"});
    try {
    Game *game = new Game();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        PI::deltaTime = currentFrame - PI::lastFrame;
        PI::lastFrame = currentFrame;
        glfwPollEvents();
        PI::processInput(window);

        glm::mat4 projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -10.0f, 10.0f);
        glm::mat4 view = camera.GetViewMatrix();

        shProjView.Bind(projection, view);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.1f, 1.0f, 1.0f);
        game->ProcessInput(window);
        game->Draw();

        glfwSwapBuffers(window);
    }
    } catch(const std::exception&) {

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}



