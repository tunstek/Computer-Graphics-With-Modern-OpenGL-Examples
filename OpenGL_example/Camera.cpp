//
//  Camera.cpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 28/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera() {
    worldUp = consts::DEFAULT_WORLD_UP;
    position = consts::DEFAULT_CAMERA_POSITION;
    yaw = consts::DEFAULT_CAMERA_YAW;
    pitch = consts::DEFAULT_CAMERA_PITCH;
    front = consts::DEFAULT_CAMERA_FRONT;
    
    movementSpeed = consts::DEFAULT_MOVEMENT_SPEED;
    turnSpeed = consts::DEFAULT_TURNING_SPEED;
    
    update();
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
    worldUp = consts::DEFAULT_WORLD_UP;
    position = startPosition;
    yaw = startYaw;
    pitch = startPitch;
    front = consts::DEFAULT_CAMERA_FRONT;
    
    movementSpeed = startMoveSpeed;
    turnSpeed = startTurnSpeed;
    
    update();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(position, position+front, up);
}

void Camera::update() {
    // updates mouse movements
    
    front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
    front = glm::normalize(front);
    
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    
}


void Camera::keyControl(bool *keys, GLfloat deltaTime) {
    GLfloat velocity = movementSpeed * deltaTime;
    if(keys[consts::DEFAULT_FORWARDS_KEY]) {
        // move forwards
        // adds an upwards angle to the position so that we move in the direction we are looking, not relative to the ground
        position += front * velocity;
    }
    if(keys[consts::DEFAULT_BACKWARDS_KEY]) {
        // move backwards
        position -= front * velocity;
    }
    if(keys[consts::DEFAULT_LEFT_KEY]) {
        // move left
        position -= right * velocity;
    }
    if(keys[consts::DEFAULT_RIGHT_KEY]) {
        // move right
        position += right * velocity;
    }
    
    if(keys[consts::DEFAULT_UP_KEY]) {
        // move up
        position += up * velocity;
    }
    if(keys[consts::DEFAULT_DOWN_KEY]) {
        // move down
        position -= up * velocity;
    }
}


void Camera::mouseControl(GLfloat deltaX, GLfloat deltaY) {
    deltaX *= turnSpeed;
    deltaY *= turnSpeed;
    
    yaw += deltaX;
    pitch += deltaY;
    
    // limit the pitch so you can't look beyond directly up
    if(pitch > 89.0f) {
        // things get strange @ >= 90
        pitch = 89.0f;
    }
    if(pitch < -89.0f) {
        // things get strange @ >= 90
        pitch = -89.0f;
    }
    
    
    // pitch and yaw have change therefore we need to update
    update();
}


Camera::~Camera() {
    
}
