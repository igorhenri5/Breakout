#ifndef __BRICK__
#define __BRICK__

#include <GL/freeglut.h>

class Brick{
    public:
        GLfloat x, y;
        GLfloat width, height;
        Brick();
        Brick(GLfloat,GLfloat,GLfloat,GLfloat);
};

#endif