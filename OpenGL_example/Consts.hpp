//
//  Consts.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 28/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef Consts_hpp
#define Consts_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace consts {
    // camera
    const glm::vec3 DEFAULT_CAMERA_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
    const GLfloat DEFAULT_CAMERA_YAW = -90.0f;
    const GLfloat DEFAULT_CAMERA_PITCH = 0.0f;
    const glm::vec3 DEFAULT_CAMERA_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
    
    
    // movement
    const GLint DEFAULT_FORWARDS_KEY = GLFW_KEY_W;
    const GLint DEFAULT_BACKWARDS_KEY = GLFW_KEY_S;
    const GLint DEFAULT_LEFT_KEY = GLFW_KEY_A;
    const GLint DEFAULT_RIGHT_KEY = GLFW_KEY_D;
    const GLint DEFAULT_UP_KEY = GLFW_KEY_SPACE;
    const GLint DEFAULT_DOWN_KEY = GLFW_KEY_LEFT_SHIFT;
    const GLfloat DEFAULT_MOVEMENT_SPEED = 1.0f;
    const GLfloat DEFAULT_TURNING_SPEED = 0.5f;
};


#endif /* Consts_hpp */
