#include "headers/camera.hpp"

#include "headers/settings.hpp"

void Camera::ProcessInput(GLFWwindow* window)
{   
    // Update the key states whether the associated key is pressed or not
    m_wPressed = glfwGetKey(window, GLFW_KEY_W);
    m_sPressed = glfwGetKey(window, GLFW_KEY_S);
    m_aPressed = glfwGetKey(window, GLFW_KEY_A);
    m_dPressed = glfwGetKey(window, GLFW_KEY_D);

    m_leftPressed = glfwGetKey(window, GLFW_KEY_LEFT);
    m_rightPressed = glfwGetKey(window, GLFW_KEY_RIGHT);
    m_upPressed = glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE;
    m_downPressed = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE;

    m_spacePressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_TRUE;
    m_shiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_TRUE;
}

void Camera::Update(const float& delta_ms)
{
    // The MOVE_SPEED and ROTATE_SPEED has been pre-calculated to save time (and instructions i guess)
    // Both have been multiplied by the delta time of game to ensure that the games runs the same on every machine regardless of framerate
    const float moveMag = MOVE_SPEED * delta_ms;
    const float rotateMag = ROTATE_SPEED * delta_ms;

    // Based on key states, update the camera position and/or rotation
    
    // Move forward
    if(m_wPressed)
        m_pos += m_lookdir * moveMag;
    // Move backward
    if(m_sPressed)
        m_pos -= m_lookdir * moveMag;
    // Move left
    if(m_aPressed)
        m_pos -= glm::normalize(glm::cross(m_lookdir, m_up)) * moveMag;
    // Move right
    if(m_dPressed)
        m_pos += glm::normalize(glm::cross(m_lookdir, m_up)) * moveMag;
        
    // Move up
    if(m_spacePressed)
        m_pos.y += moveMag;
    // Move down
    if(m_shiftPressed)
        m_pos.y -= moveMag;

    // Look left
    if(m_leftPressed)
        RotateYaw(rotateMag);
    // Look right
    if(m_rightPressed)
        RotateYaw(-rotateMag);
    // Look up
    if(m_upPressed)
        RotatePitch(rotateMag);
    // Look down
    if(m_downPressed)
        RotatePitch(-rotateMag);

    // Finally, recalculate the view matrix after the camera data has been updated
    m_mat_view = glm::lookAt(m_pos, m_pos + m_lookdir, m_up);
}

void Camera::RotateYaw(float angle)
{
    m_lookdir = glm::rotate(glm::mat4(1.0f), angle, m_up) * glm::vec4(m_lookdir, 0.0f);
}

void Camera::RotatePitch(float angle)
{
    m_lookdir = glm::rotate(glm::mat4(1.0f), angle, glm::cross(m_lookdir, m_up)) * glm::vec4(m_lookdir, 0.0f);
}