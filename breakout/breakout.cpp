#include "breakout.hpp"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <GL/freeglut.h>

#define PI 3.14159265
#define MAXXVEL 10

Breakout::Breakout(){
    this->state = 0;
}

Breakout::Breakout(int width, int height){
    this->state = 0;
    this->width = width;
    this->height = height;
}

void Breakout::activeMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        std::cout << "Pause/Resume" << std::endl;
        //pause
    }
}

void Breakout::passiveMouse(int x, int y){
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%d", x);
    glutSetWindowTitle(buffer);

    this->mouseX = (GLfloat)x;
}

void Breakout::activeKeyboard(int key, int x, int  y){
    std::cout << "Key pressed:: " << key << std::endl;
    switch(key){
        case 'q':
        case 'Q':
            //quit
            exit(1);
        case 'r':
        case 'R':
            //reset
            break;
        default:
            break;
    }
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

GLfloat paddleVelocity(GLfloat pX, GLfloat wX, GLfloat pWidth, GLfloat wWidth){
    //Velocidade dada em pixels por 16.6 ms 
    GLfloat maxVel = 40;
    GLfloat vel;

    GLfloat paddleCenterX = pX+(pWidth/2);
    GLfloat maxDistance = wWidth-pWidth/2;
    //retorna algo no intervalo [-maxVel,maxVel]
    vel = ((wX-paddleCenterX)/maxDistance)*maxVel;

    if(vel>0 && vel<0.334)
        return 0.334;

    if(vel<0 && vel>-0.334)
        return -0.334;

    return vel;
}

GLfloat calcBallXVel(){

}

void Breakout::update(){
//Movimento
    //mover bola
        this->ball->x += this->ball->velX;
        this->ball->y += this->ball->velY;    

    //mover paddle
    GLfloat vel = paddleVelocity(paddle->x, this->mouseX, paddle->width, (GLfloat)width);
    this->paddle->x += vel;

//Colisões
    //colisão com as bordas da tela
        //esquerda-direita
        if((this->ball->x <= (2*this->ball->radius)) || (this->ball->x >= (this->width - 2*this->ball->radius))){
            this->ball->velX *= -1;
        }
        //cima
        if((this->ball->y <= (2 * this->ball->radius))){
            this->ball->velY *= -1;
        }
        //baixo
        if(this->ball->y >= (this->height - 2*this->ball->radius)){
            //matar a bola
            this->ball->velY *= -1;
        }

    //colisão da bola com os tijolos            

    //colisão da bola com o paddle
        // if(this->ball->x >= this->paddle->x && this->ball->x <= this->paddle->x + paddle->width){
        if( this->ball->x >= this->paddle->x && 
            this->ball->x <= this->paddle->x + paddle->width){
            if( (this->paddle->y -this->ball->y -this->ball->radius) < (this->paddle->height) &&
                (this->paddle->y -this->ball->y -this->ball->radius) > 0){
                this->ball->velY *= -1;
                //mudar a velX da bola de acordo com a area do paddle onde ocorreu colisão
                    //calcula a nova velocidade em x com uma função não linear
                GLfloat paddleCenterX = this->paddle->x+(this->paddle->width/2);
                GLfloat velX = (this->ball->x - paddleCenterX)/(this->paddle->width/2);
                if(velX>0)
                    velX = MAXXVEL*sqrt(velX);
                else
                    velX = -MAXXVEL*sqrt(-velX);                
                this->ball->velX = velX;
            }
        }
}
        

void Breakout::initPaddle(){
    paddle = new Paddle(((float)width-200)/2,(float)height*0.9, 200.0f,10.0f);
}

void Breakout::initBricks(){
    int brickWidth  = 90;
    int brickHeight = 45;
    //matriz de tijolos 3x10 p/ tela 1000x1000
    for(int k=1; k<=3; k++){
        for(int i=0; i<10; i++){
            bricks.push_back(new Brick(i*100+5,k*50,brickWidth,brickHeight));
        }
    }
}

void Breakout::initBall(){
    ball = new Ball(((float)width-10)/2,(float)height*0.9-15.0f,10,10,10);
}

void Breakout::drawPaddle(){
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(paddle->x , paddle->y, paddle->x + paddle->width , paddle->y + paddle->height);
}

void Breakout::drawBricks(){
    for(std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it){
        // glColor3f(0.91f, 0.008f, 0.475f);
        glColor3f(0.0f, 1.0f, 0.6f);
        glRectf((*it)->x, (*it)->y, (*it)->x + (*it)->width, (*it)->y + (*it)->height);
        
        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f-0.2f, 0.2f);
        glVertex2f((*it)->x, (*it)->y);
        glColor3f(0.0f, 1.0f-0.05f, 0.25f);
        glVertex2f((*it)->x + (*it)->width, (*it)->y);
        glColor3f(0.0f, 1.0f-0.15f, 0.45f);
        glVertex2f((*it)->x + (*it)->width, (*it)->y + (*it)->height);
        glVertex2f((*it)->x, (*it)->y);
        glEnd();
    }
}

void Breakout::drawBall(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glBegin(GL_POLYGON);
    glColor3f(0.91f, 0.008f, 0.475f);
    for(int j = 0; j < 50; j++) {
        float const theta = 2.0f * PI * (float)j/50.0f;
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

