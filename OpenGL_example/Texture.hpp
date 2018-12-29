//
//  Texture.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 29/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include "stb_image.h"

class Texture {
public:
    Texture();
    Texture(char* filePath);
    
    void loadTexture();
    void useTexture();
    void clearTexture();
    
    ~Texture();
private:
    GLuint textureID;
    int width, height, bitdepth;
    char* filePath;
};

#endif /* Texture_hpp */
