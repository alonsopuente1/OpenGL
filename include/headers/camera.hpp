#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GLFW/glfw3.h"

class Camera
{

public:
    Camera(float fov, float aspect_ratio, float n_plane, float f_plane)
    : m_pos(0.0f, 0.0f, 0.0f), m_lookdir(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f)
    {
        m_mat_lookat = glm::lookAt(m_pos, m_pos + m_lookdir, m_up);
        m_mat_proj = glm::perspective(fov, aspect_ratio, n_plane, f_plane);
    }

    ~Camera()
    {
    }

    void ProcessInput(GLFWwindow* window);

    void Update(float delta_ms);

    glm::mat4 GetMatrix();
private:
    glm::vec3 m_pos;
    glm::vec3 m_lookdir;
    const glm::vec3 m_up;

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

    glm::mat4 m_mat_proj;
    glm::mat4 m_mat_lookat;

    void RotateYaw(float angle);
    void RotatePitch(float angle);
};

#endif