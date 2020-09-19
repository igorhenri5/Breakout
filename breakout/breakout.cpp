#include "breakout.hpp"
#include <iostream>
#include <math.h>

#define PI 3.14159265
#define MAXXVEL 10

Breakout::Breakout(){
    init();
}

Breakout::Breakout(int width, int height){
    this->width = width;
    this->height = height;
    init();
}

void Breakout::activeMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        switch (this->gamePaused) {
        case true:
            this->gamePaused = false;
            std::cout << "RESUME GAME" << std::endl;
            break;

        case false:
            this->gamePaused = true;
            std::cout << "PAUSE GAME" << std::endl;
            break;
        }
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
            init();
            break;
        default:
            break;
    }
}

void Breakout::specialActiveKeyboard(int key, int x, int y){
    std::cout << "Key pressed:: " << key << std::endl;    
}

void Breakout::init(){
    this->state = 0;
    this->score = 0; 
    this->gamePaused = true;
    initPaddle();
    //initBricks();
    initBall();
    initLevel();
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
            if (!this->gamePaused) {
                update();
            }
            // draw();
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

    // retorna algo no intervalo [-maxVel,maxVel]
    vel = ((wX-paddleCenterX)/maxDistance)*maxVel;

    if(vel>0 && vel<0.333)
        return 0.333;
    if(vel<0 && vel>-0.333)
        return -0.333;

    return vel;
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

    //colisão da bola com o paddle
        if( this->ball->y + 2*this->ball->radius > this->paddle->y &&
            this->ball->y < this->paddle->y &&
            this->ball->x > (this->paddle->x - this->ball->radius) &&
            this->ball->x < (this->paddle->x + this->paddle->width + this->ball->radius)){
            
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

    //colisão da bola com os tijolos  

        for (std::vector<Brick*>::iterator it = currentLevel->bricks.begin(); it != currentLevel->bricks.end(); ++it){
            int hit = 0;
            if ((*it)->tangivel){
                if( this->ball->x > (*it)->x - this->ball->radius &&
                    this->ball->x < (*it)->x + (*it)->width + this->ball->radius &&
                    this->ball->y > (*it)->y - this->ball->radius &&
                    this->ball->y < (*it)->y + (*it)->height + this->ball->radius){
                    
                    if( this->ball->y + this->ball->radius > (*it)->y &&
                        this->ball->y < (*it)->y + (*it)->height - this->ball->radius){
                        //hit lateral
                        this->ball->velX *= -1;
                        hit = 1;
                    }else if(   this->ball->x + this->ball->radius > (*it)->x  &&
                                this->ball->x < (*it)->x + (*it)->width - this->ball->radius){
                        //hit vertical
                        this->ball->velY *= -1;
                        hit = 1;
                    }else{
                        //hit na quina
                        this->ball->velX *= -1;
                        this->ball->velY *= -1;
                        hit = 1;
                    }
                }

                if(hit){                   
                   this->score += (*it)->takeHit();
                }
            }   
        }

    //colisão com as bordas da tela
        //esquerda-direita
        if( (this->ball->x <= (2*this->ball->radius)) || 
            (this->ball->x >= (this->width - 2*this->ball->radius))){
            this->ball->velX *= -1;
        }
        //cima
        if((this->ball->y <= (2*this->ball->radius))){
            this->ball->velY *= -1;
        }
        //baixo
        if(this->ball->y >= (this->height - 2*this->ball->radius)){
            //matar a bola
            this->ball->velY *= -1;
        }

}

void Breakout::initPaddle(){
    paddle = new Paddle(((float)width-200)/2,(float)height*0.9, 200.0f,10.0f);
    // paddle = new Paddle(0,height, 200.0f,10.0f);
}

void Breakout::initBall(){
    ball = new Ball(((float)width-10)/2, (float)height*0.9-15.0f, 6, 0, -10);
}

void Breakout::initLevel() { //Inicia o Level 
    // std::string layout = "1110220111|1002222001|1011221101|1001221001"; //Especifica quais os tipos de Tijolo fazem parte do Level
    // std::string layout = "11102201111110220111|10022220011002222001|10112211011011221101|10012210011001221001"; //Especifica quais os tipos de Tijolo fazem parte do Level
    std::string layout = "11102201111110220111|10022220011002222001|10112211011011221101|10012210011001223451"; //Especifica quais os tipos de Tijolo fazem parte do Level
    currentLevel = new Level(layout);
}

void Breakout::drawPaddle(){
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(paddle->x , paddle->y, paddle->x + paddle->width , paddle->y + paddle->height);
}

void Breakout::drawBricks(){
    for(std::vector<Brick*>::iterator it = currentLevel->bricks.begin(); it != currentLevel->bricks.end(); ++it){
        (*it)->drawBrick();
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

void Breakout::drawText(float x, float y, std::string text) { //Imprime a string nas coordenadas X e Y especificadas
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

void Breakout::draw(){
    drawPaddle();
    drawBricks();
    drawBall();
    drawText(10.0f, 25.0f, std::to_string(this->score)); //Desenha o Score
    
    if(this->gamePaused) { //Se o jogo estiver pausado, informa o jogador
        drawText(450.0f, 400.0f, "Jogo Pausado!");
        drawText(275.0f, 425.0f, "Presisone o Botao Esquerdo do Mouse para Despausar!");
    }
}

