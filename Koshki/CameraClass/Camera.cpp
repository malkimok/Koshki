#include "Camera.hpp"

Camera::Camera(){
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraUp, GLfloat cameraYaw, GLfloat cameraPitch, GLfloat cameraMoveSpeed, GLfloat cameraTurnSpeed, string cameraName){
    
    position = cameraPosition;
    worldUp = cameraUp;
    yaw = cameraYaw;
    pitch = cameraPitch;
    movementSpeed = cameraMoveSpeed;
    turnSpeed = cameraTurnSpeed;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    name = cameraName;
    
    update();
}

void Camera::update(){
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::calculateViewMatrix(){
    return glm::lookAt(position, position + front, worldUp);
}
