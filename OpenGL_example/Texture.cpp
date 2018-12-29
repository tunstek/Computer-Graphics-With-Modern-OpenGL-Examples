//
//  Texture.cpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 29/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture() {
    textureID = 0;
    width = 0;
    height = 0;
    bitdepth = 0;
    filePath = "";
}

Texture::Texture(char* path) {
    textureID = 0;
    width = 0;
    height = 0;
    bitdepth = 0;
    filePath = path;
}

void Texture::loadTexture() {
    unsigned char* texData = stbi_load(filePath, &width, &height, &bitdepth, 0); // byte array
    if(!texData) {
        printf("ERR: [Texture::loadTexture] Failed to find file: %s", filePath);
    }
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(texData);
}


void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitdepth = 0;
    filePath = "";
}


Texture::~Texture() {
    clearTexture();
}

