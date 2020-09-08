#ifndef __PADDLE__
#define __PADDLE__

#include <GL/freeglut.h>

class Paddle{
    public:
        GLfloat x, y;
        GLfloat width, height;
        Paddle();
        Paddle(GLfloat,GLfloat,GLfloat,GLfloat);
};

#endif