#include "Ball.hpp"

Ball::Ball(){   
    this->velX = 0;
    this->velY = 0;
}

Ball::Ball(GLfloat x, GLfloat y, GLfloat radius, GLfloat velX, GLfloat velY){
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->velX = velX;
    this->velY = velY;
}
