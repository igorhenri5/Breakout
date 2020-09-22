#ifndef __BALL__
#define __BALL__

#include <GL/freeglut.h>

class Ball{
    public:
        GLfloat x, y;
        GLfloat radius;
        GLfloat velX, velY;
        Ball();
        Ball(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
};


#endif