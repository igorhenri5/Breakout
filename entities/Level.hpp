#ifndef __LEVEL__
#define __LEVEL__

#include <GL/freeglut.h>
#include "brick.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>

class Level {
public:
    std::string layout;
    std::vector<Brick*> bricks;
    Level();
    Level(std::string);
};

#endif