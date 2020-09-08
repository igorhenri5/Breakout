#include "Ball.hpp"

Ball::Ball(){    
}

Ball::Ball(GLfloat x, GLfloat y, GLfloat radius, GLfloat velX, GLfloat velY){
    this->x = x;
    this->y = y;
    // this->width = width;
    // this->height = height;
    this->radius = radius;
    this->velX = velX;
    this->velY = velY;
}

