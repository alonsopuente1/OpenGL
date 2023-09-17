#include <iostream>
#include <time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/settings.hpp" 
#include "headers/util.hpp"
#include "headers/logger.hpp"
#include "headers/shader.hpp"
#include "headers/VBO.hpp"
#include "headers/VAO.hpp"
#include "headers/IBO.hpp"
#include "headers/Vertex.hpp"
#include "headers/error.hpp"
#include "headers/texture.hpp"
#include "headers/camera.hpp"

#include "headers/model.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

int main(int argc, char** argv)
{
    srand(time(nullptr));

    glfwInitHint(GLFW_VERSION_MAJOR, 4);
    glfwInitHint(GLFW_VERSION_MINOR, 6);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(glfwInit() == GLFW_FALSE)
    { 
        const char* x;
        glfwGetError(&x);
        Logger::Error("Failed to initialise GLFW.\nGLFW Error: %s", x);
        return -1;
    }


    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello OpenGL", NULL, NULL);

    if(!window)
    {
        const char* x;
        glfwGetError(&x);
        Logger::Error("Failed to create window.\nGLFW Error: %s", x);
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::Error("Failed to initialize GLAD.");
        return -1;
    }    

    Logger::Info("Open GL Version: %s", glGetString(GL_VERSION));

    GLCall(glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    Vertex vertices[] = {
        // position             // colour           // tex coord
        {-0.5f,  0.0f,  0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f},
        {-0.5f,  0.0f, -0.5f,    0.0f, 0.0f, 0.0f,   5.0f, 0.0f},
        { 0.5f,  0.0f, -0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f},
        { 0.5f,  0.0f,  0.5f,    0.0f, 0.0f, 0.0f,   5.0f, 0.0f},
        { 0.0f,  0.8f,  0.0f,    0.0f, 0.0f, 0.0f,   2.5f, 5.0f}
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    {

    Model model(vertices, sizeof(vertices), true, indices, sizeof(indices), "");
    Shader shader_program("../res/shaders/Basic.vert", "../res/shaders/Basic.frag");
    Camera cam(90.0f, (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH, 0.1, 100.0f);
    
    model.SetPos(glm::vec3(0.0f, 0.0f, -2.0f));

    shader_program.Bind();
    shader_program.SetIntUniform("tex", 0);

    float old_time_ms = (float)glfwGetTime() / 1000.0f;

    float theta = 0.0f;

    GLCall(glEnable(GL_DEPTH_TEST));

    while(!glfwWindowShouldClose(window)) 
    {  
        processInput(window);
        cam.ProcessInput(window);

        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


        float new_time_ms = (float)glfwGetTime() / 1000.0f;
        float delta_ms = new_time_ms - old_time_ms;
        old_time_ms = new_time_ms;

        cam.Update(delta_ms);

        // theta += delta_ms * 200.0f;

        shader_program.Bind();
        shader_program.SetMatrixUniform("mMVP", cam.GetMatrix() * model.GetModelMat());

        model.Draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    
    return 0;
}