//
//  Camera.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 28/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Consts.hpp"

class Camera {
    
public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
    
    void keyControl(bool* keys);
    
    glm::mat4 calculateViewMatrix();
    
    ~Camera();
    
private:
    glm::vec3 position, front, up, right, worldUp;
    
    GLfloat yaw, pitch;
    
    GLfloat movementSpeed, turnSpeed;
    
    void update();
};

#endif /* Camera_hpp */
