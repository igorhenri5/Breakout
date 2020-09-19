#ifndef __BRICK__
#define __BRICK__

#include <GL/freeglut.h>

class Brick{
    public:
        GLfloat x, y;
        GLfloat width, height;
        bool tangivel;
        int type;
        int hp;
        Brick();
        Brick(GLfloat,GLfloat,GLfloat,GLfloat);
        Brick(GLfloat,GLfloat,GLfloat,GLfloat, int);
        void drawBrick();
        int takeHit();
};

#endif