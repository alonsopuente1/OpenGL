/*

camera.hpp

Defines a camera class which means you can move around  in the OpenGL scene given you set
add the view

*/

// header guard
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GLFW/glfw3.h"

class Camera
{

public:
    /// @brief Makes the view matrix for the camera
    Camera()
    : m_pos(0.0f, 0.0f, 0.0f), m_lookdir(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f)
    {
        m_mat_view = glm::lookAt(m_pos, m_pos + m_lookdir, m_up);
    }

    /// @brief Processes inputs for the camera to set the move and rotate states, BUT DOESNT APPLY THEM. That happens in the Update() function
    /// @param window The window to process the inputs from
    void ProcessInput(GLFWwindow* window);

    /// @brief Updates the camera's position and direction based on states
    /// @param delta_ms The delta time of the game to make sure the game runs at the same speed no matter the framerate
    void Update(const float& delta_ms);

    /// @brief Returns the view matrix belonging to the camera
    /// @return View matrix
    inline glm::mat4 GetMatrix() const { return m_mat_view; }

private:
    // Stores the position of the cameraa
    glm::vec3 m_pos;
 
    // Stores the look direction of the camera
    glm::vec3 m_lookdir;
    
    // Stores up direction (will always be (0.0f, 1.0f, 0.0f))
    const glm::vec3 m_up;

    // Stores states of which keys are pressed, which is then applied accordingly in Update() function
    bool m_wPressed = false;
    bool m_sPressed = false;
    bool m_aPressed = false;
    bool m_dPressed = false;

    bool m_leftPressed  = false;
    bool m_rightPressed = false;
    bool m_upPressed    = false;
    bool m_downPressed  = false;

    bool m_spacePressed = false;
    bool m_shiftPressed = false;

    // The camera's view matrix
    glm::mat4 m_mat_view;

    /// @brief Rotates the look direction of the camera along the y axis (left and right)
    /// @param angle Angle to rotate by in radians
    void RotateYaw(float angle);

    /// @brief Rotates the look direction of the camera along the left and right axis (up and down)
    /// @param angle Angle to rotate by in radians
    void RotatePitch(float angle);

    /// @brief Updates the view matrix based on the camera's position, look direction and up vector
    inline void UpdateMat() { m_mat_view = glm::lookAt(m_pos, m_pos + m_lookdir, m_up); }
};

#endif