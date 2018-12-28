//
//  Utils.hpp
//  OpenGL GLFW
//
//  Created by Keith Tunstead on 26/12/2018.
//  Copyright © 2018 Keith Tunstead. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

class Utils {
public:
    static float degreesToRadians(int deg){return deg*(3.14159265358f / 180.0f);}
    static std::string ReadFile(const char *path);
};

#endif /* Utils_hpp */
