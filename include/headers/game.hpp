/*

game.hpp

Defines a Game class which stores models, camera and shaders which only need three functions to run


HandeEvents();
Update(delta_time);
Draw();

*/

#ifndef GAME_H
#define GAME_H

#include "headers/util.hpp"
#include "headers/logger.hpp"
#include "headers/error.hpp"
#include "headers/model.hpp"
#include "headers/shader.hpp"
#include "headers/camera.hpp"

class Game
{

public:
    /// @brief Constructs the game ready for updating and drawing. OPENGL NEEDS TO BE INITIALISED BEFORE MAKING A GAME OBJECT
    /// @param title Title of the window
    /// @param width Width of the window
    /// @param height Height of the window
    Game(const char* title, int width, int height)
    : m_run(true),
      m_cam(nullptr),
      m_shader(nullptr),
      m_title(title)
    {
        // Initialise GLFW and stop if it fails
        if(!InitGLFW())
        {
            m_run = false;
            return;
        }

        // Create GLFW window
        m_window = glfwCreateWindow(width, height, title, NULL, NULL);

        // If window doesn't exist, don't go any further and log the error
        if(m_window == NULL)
        {
            const char* x;
            glfwGetError(&x);

            m_run = false;
            Logger::Error("Failed to create GLFW window. GLFW Error: %s", x);
            return;
        }

        // Make the window the current context
        glfwMakeContextCurrent(m_window);

        // Try to initialise OpenGL and if it doesn't init, stop.
        if(!InitOpenGL())
        {
            m_run = false;
            return;
        }

        // Set the viewport to be the width and height of the window
        GLCall(glViewport(0, 0, width, height));

        // Set the frame buffer resize callback
        glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

        // Enable depth testing to stop the weird overlapping textures
        GLCall(glEnable(GL_DEPTH_TEST));

        // Create the shader
        m_shader = new Shader("../res/shaders/Basic.vert", "../res/shaders/Basic.frag");

        // Initialise the models and add them to the scene
        InitModels();
    }

    /// @brief Deallocates the camera, models, shader and terminates GLFW
    ~Game()
    {
        // The reason I manually free each resource is becauase if GLFW is terminted before these resources are freed, the prograam will keep running for some reason
        if(m_cam)
            delete m_cam;

        if(m_shader)
            delete m_shader;

        for(Model* m : m_models)
            delete m;

        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    /// @brief Check to see if the game is still running
    /// @return The run state of the game
    inline bool Run() { return m_run; }

    /// @brief Processes events like keyboard input 
    void HandleEvents();
    /// @brief Updates the gamestate using the delta time. Delta time keeps everything moving at same rate across every machine even with different framerates
    /// @param delta_ms Time since last frame was rendered
    void Update(const float& delta_ms);
    /// @brief Draws the scene
    void Draw();

    /// @brief Makes a camera to move around the scene. Not necessary but if you dont call this you will stay at one position and cant move at all (in game)
    void MakeCam();

private:
    // The window where the game will be rendered
    GLFWwindow* m_window;
    
    // The current state of the program
    bool m_run;

    // All the models in the scene. Heap allocated because of problems of destructors (complicated but hard to get into in one comment)
    std::vector<Model*> m_models;

    // Optional camera
    Camera* m_cam;

    // Shader for the game
    Shader* m_shader;

    // Title of the window
    std::string m_title;

    // All model initialisation should occur here. Push back 'new Model(...)' to m_models to add a model
    void InitModels();
};

#endif