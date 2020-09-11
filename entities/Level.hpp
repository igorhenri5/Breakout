#ifndef __LEVEL__
#define __LEVEL__

#include <GL/freeglut.h>
#include "brick.hpp"
#include <vector>
#include <string>

class Level {
public:
    std::string layout;
    std::vector<Brick*> bricks;
    Level();
    Level(std::string);
};

#endif