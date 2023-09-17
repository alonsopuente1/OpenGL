#include "headers/camera.hpp"

#include "headers/settings.hpp"

glm::mat4 Camera::GetMatrix()
{
    return m_mat_proj * m_mat_lookat;
}


void Camera::ProcessInput(GLFWwindow* window)
{   
    m_wPressed = glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE;
    m_sPressed = glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE;
    m_aPressed = glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE;
    m_dPressed = glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE;

    m_leftPressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_TRUE;
    m_rightPressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_TRUE;
    m_upPressed = glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE;
    m_downPressed = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE;

    m_spacePressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_TRUE;
    m_shiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_TRUE;
}

void Camera::Update(float delta_ms)
{
    const float moveMag = MOVE_SPEED * delta_ms;
    const float rotateMag = ROTATE_SPEED * delta_ms;

    if(m_wPressed)
        m_pos += m_lookdir * moveMag;
    if(m_sPressed)
        m_pos -= m_lookdir * moveMag;
    if(m_aPressed)
        m_pos -= glm::normalize(glm::cross(m_lookdir, m_up)) * moveMag;
    if(m_dPressed)
        m_pos += glm::normalize(glm::cross(m_lookdir, m_up)) * moveMag;
        
    if(m_spacePressed)
        m_pos.y += moveMag;
    if(m_shiftPressed)
        m_pos.y -= moveMag;

    if(m_leftPressed)
        RotateYaw(rotateMag);
    if(m_rightPressed)
        RotateYaw(-rotateMag);
    if(m_upPressed)
        RotatePitch(rotateMag);
    if(m_downPressed)
        RotatePitch(-rotateMag);

    m_mat_lookat = glm::lookAt(m_pos, m_pos + m_lookdir, m_up);
}

void Camera::RotateYaw(float angle)
{
    m_lookdir = glm::rotate(glm::mat4(1.0f), angle, m_up) * glm::vec4(m_lookdir, 0.0f);
}

void Camera::RotatePitch(float angle)
{
    m_lookdir = glm::rotate(glm::mat4(1.0f), angle, glm::cross(m_lookdir, m_up)) * glm::vec4(m_lookdir, 0.0f);
}