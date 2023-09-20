#include "headers/game.hpp"

void Game::HandleEvents()
{
    // If user presses escape, exit
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_TRUE)
    {
        glfwSetWindowShouldClose(m_window, 1);
    }

    // Process the inputs for the camera
    if(m_cam)
        m_cam->ProcessInput(m_window);
}

void Game::Update(const float& delta_ms)
{
    // Check to see if the window should be closing
    m_run = !glfwWindowShouldClose(m_window);
    
    // Update the camera based on movement state
    if(m_cam)
        m_cam->Update(delta_ms);

    // Calculate fps and display it in the window title
    int fps = (int)(1000.0f / (float)delta_ms);

    std::string new_title = m_title;

    new_title += " [FPS] ";

    new_title += std::to_string(fps);

    glfwSetWindowTitle(m_window, new_title.c_str());
}

void Game::Draw()
{
    // Clear the screen to the blue colour
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // Bind the shader and set the texture unit to 0
    m_shader->Bind();
    m_shader->SetIntUniform("tex", 0);

    // Get the width and the height of the window
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    // Set the projection matrix in the shader
    m_shader->SetMatrixUniform("mProj", glm::perspective(90.0f, (float)width / (float)height, 0.1f, 100.0f));
    
    // If a camera exists set the view matrix to the camera's view matrix, else leave it
    if(m_cam)
        m_shader->SetMatrixUniform("mView", m_cam->GetMatrix());
    else
        m_shader->SetMatrixUniform("mView", glm::mat4(1.0f));

    // For each model set the model matrix in the shader to the model's matrix
    for(Model* m : m_models)
    {
        m_shader->SetMatrixUniform("mModel", m->GetModelMat());
        m->Draw();
    }

    // Swap buffers (display screen) and poll events
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Game::MakeCam()
{
    if(m_cam)
        delete m_cam;

    m_cam = new Camera();
}

void Game::InitModels()
{
    // Pyramid vertices
    Vertex vertices[] = {
        // position             // colour           // tex coord
        {-0.5f,  0.0f,  0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f},
        {-0.5f,  0.0f, -0.5f,    0.0f, 0.0f, 0.0f,   5.0f, 0.0f},
        { 0.5f,  0.0f, -0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f},
        { 0.5f,  0.0f,  0.5f,    0.0f, 0.0f, 0.0f,   5.0f, 0.0f},
        { 0.0f,  0.8f,  0.0f,    0.0f, 0.0f, 0.0f,   2.5f, 5.0f}
    };

    // Pyramid indices
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    // Push back three models of the same shape but with different textures
    m_models.push_back(new Model(vertices, sizeof(vertices), true, indices, sizeof(indices), "../res/textures/wall.jpg"));
    m_models[0]->SetPos(glm::vec3(3.0f, 0.0f, 0.0f));

    m_models.push_back(new Model(vertices, sizeof(vertices), true, indices, sizeof(indices), "../res/textures/default.jpg"));
    m_models[1]->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));

    m_models.push_back(new Model(vertices, sizeof(vertices), true, indices, sizeof(indices), "../res/textures/container.jpg"));
    m_models[2]->SetPos(glm::vec3(-3.0f, 0.0f, 0.0f));
}
