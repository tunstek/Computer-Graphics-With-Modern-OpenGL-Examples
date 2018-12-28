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


void Camera::keyControl(bool *keys) {
    if(keys[consts::DEFAULT_FORWARDS]) {
        // move forwards
        position += front * movementSpeed;
    }
    if(keys[consts::DEFAULT_BACKWARDS]) {
        // move backwards
        position -= front * movementSpeed;
    }
    if(keys[consts::DEFAULT_LEFT]) {
        // move left
        position -= right * movementSpeed;
    }
    if(keys[consts::DEFAULT_RIGHT]) {
        // move right
        position += right * movementSpeed;
    }
}


Camera::~Camera() {
    
}
