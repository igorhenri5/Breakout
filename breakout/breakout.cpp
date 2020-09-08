#include "breakout.hpp"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <GL/freeglut.h>

Breakout::Breakout(){
    this->state = 0;
}

Breakout::Breakout(int width, int height){
    this->state = 0;
    this->width = width;
    this->height = height;
}

GLfloat paddleVelocity(GLfloat pX, GLfloat wX, GLfloat pWidth, GLfloat wWidth){
    //Velocidade dada em pixels por 16.6 ms 
    GLfloat maxVel = 40;
    GLfloat vel;

    int paddleCenterX = pX+(pWidth/2);
    float maxDistance = wWidth-pWidth/2;
    //retorna algo no intervalo [-maxVel,maxVel]
    vel = ((wX-paddleCenterX)/maxDistance)*maxVel;

    if(vel>0 && vel<0.334)
        return 0.334;

    if(vel<0 && vel>-0.334)
        return -0.334;

    return vel;
}

void Breakout::passiveMouse(int x, int y){
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%d", x);
    glutSetWindowTitle(buffer);

    this->mouseX = (GLfloat)x;
}

void Breakout::activeKeyboard(int key, int x, int  y){
    std::cout << "Key pressed:: " << key << std::endl;
}

void Breakout::specialActiveKeyboard(int key, int x, int y){
    std::cout << "Key pressed:: " << key << std::endl;    
}

void Breakout::init(){
    initPaddle();
    initBricks();
    initBall();
    mouseX = 0.0f;
    this->state = 1;
}

void reDisplay(int value){
    glutPostRedisplay();
}

void Breakout::display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch(this->state){
        case 0:
            init();
            break;

        case 1:
            draw();
            update();
            break;        
        default:
            break;
    }
    
    glutTimerFunc(FRAMETIME, reDisplay, 0);
    glutSwapBuffers();
}

void Breakout::update(){
    //mover tudo e checar colisões      

    //movendo paddle
    GLfloat vel = paddleVelocity(paddle->x, this->mouseX, paddle->width, (GLfloat)width);
    // if(paddle->x >= 0 && (paddle->x + paddle->width < this->width)){
        paddle->x += vel;
    // /} 
}

void Breakout::initPaddle(){
    paddle = new Paddle(((float)width-200)/2,(float)height*0.9, 200.0f,10.0f);
}

void Breakout::initBricks(){
    int brickWidth  = 90;
    int brickHeight = 45;
    bricks.push_back(new Brick(300,100,brickWidth,brickHeight));
    bricks.push_back(new Brick(400,100,brickWidth,brickHeight));
    bricks.push_back(new Brick(500,100,brickWidth,brickHeight));
    bricks.push_back(new Brick(600,100,brickWidth,brickHeight));
    bricks.push_back(new Brick(700,100,brickWidth,brickHeight));
}

void Breakout::initBall(){
    ball = new Ball(((float)width-10)/2,(float)height*0.9-15.0f,10,1,1);
}

void Breakout::drawPaddle(){
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(paddle->x , paddle->y, paddle->x + paddle->width , paddle->y + paddle->height);
}

void Breakout::drawBricks(){
    for(std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it){
        glColor3f(0.0f, 1.0f, 0.0f);
        glRectf((*it)->x, (*it)->y, (*it)->x + (*it)->width, (*it)->y + (*it)->height);
        
        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f-0.2f, 0.2f);
        glVertex2f((*it)->x, (*it)->y);
        glColor3f(0.0f, 1.0f-0.05f, 0.05f);
        glVertex2f((*it)->x + (*it)->width, (*it)->y);
        glColor3f(0.0f, 1.0f-0.15f, 0.15f);
        glVertex2f((*it)->x + (*it)->width, (*it)->y + (*it)->height);
        glVertex2f((*it)->x, (*it)->y);
        glEnd();
    }
}

void Breakout::drawBall(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    for(int j = 0; j < 50; j++) {
        float const theta = 2.0f * 3.14f * (float)j / 50.0f;
        float const x = ball->radius * cosf(theta);
        float const y = ball->radius * sinf(theta);
        glVertex2f(x + ball->x, y + ball->y);
    }
    glEnd();   
}

void Breakout::draw(){
    drawPaddle();
    drawBricks();
    drawBall();
}

