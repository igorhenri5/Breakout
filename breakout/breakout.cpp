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

void Breakout::init(){
    this->qntLevels = 4;
    this->levelNumber = 1;
    this->ballCount = 3;
    this->state = 0;
    this->score = 0; 
    this->gamePaused = true;
    this->changingLevels = false;
    this->gameEnd = false;
    initPaddle();
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
        case 0: //inicializar
            init();
            break;

        case 1: //executando
            draw();
            if (!this->gamePaused) {
                update();
            }
            break;
        case 2: //game over
            draw();
            if (!this->gamePaused) {
                update();
            }
            break;
        case 3: //debug
            draw();
            update();
            gameInfo();
            this->state = 1;
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

//Movimento & Colisões
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
                   switch ((*it)->type) {
                   case 1:
                        this->currentLevel->liveBricks--;
                        break;
                    
                   case 2:
                       (*it)->type = 1;
                       break;

                   case 3:
                       this->currentLevel->liveBricks--;
                       break;

                   case 4: //Se for do Tipo 4, Amarelo
                       this->currentLevel->liveBricks--;
                       ballCount++; //Ganha uma vida Extra
                       messages.push_back(new Message("+1 Vida!!", 180, height));

                   case 5:
                       break;
                   }

                   if (this->currentLevel->liveBricks == 0) {
                       this->gamePaused = true;
                       this->changingLevels = true;
                   }
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
            resetBall();
        }

}

void Breakout::initPaddle(){
    paddle = new Paddle(((float)width-200)/2,(float)height*0.9, 200.0f,10.0f);
}

void Breakout::initBall(){
    ball = new Ball(((float)width-10)/2, (float)height*0.9-15.0f, 6, 0, -10);
}

void Breakout::initLevel() { //Inicia o Level 

    std::string layout1 = "00000000111100000000|11111000444400011111";
    std::string layout2 = "00000221555112200000|10033224444442233000";
    std::string layout3 = "03300333033303300333|10000101010101010101|10110101011001010101|10010101010101010101|01100111010101100111";
    std::string layout4 = "03300022011022000330|10023320011002332001|00000000000000000000|30012000555500021003";
    
    std::cout << "Loading Level: " << this->levelNumber << std::endl;
    
    switch(this->levelNumber){
        case 1:
            currentLevel = new Level(layout1);
            break;
        case 2:
            currentLevel = new Level(layout2);
            break;
        case 3:
            currentLevel = new Level(layout3);
            break;
        case 4:
            currentLevel = new Level(layout4);
            break;
    }
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

void Breakout::drawMessages() {
    if (!messages.empty()) {
        for (std::vector<Message*>::iterator it = messages.begin(); it != messages.end();) {
            drawText(10.0f, (*it)->posY, (*it)->message);
            (*it)->posY -= 1;
            (*it)->timer -= 1;

            if ((*it)->timer <= 0) {
                if (it != messages.end()) {
                    it = messages.erase(it);
                }
            } else {
                it++;
            }
        }
    }
}

void Breakout::draw(){
    drawPaddle();
    drawBricks();
    drawBall();
    drawText(10.0f, 25.0f, "Score: " + std::to_string(this->score)); //Desenha o Score
    drawText(120.0f, 25.0f, "Vidas: " + std::to_string(this->ballCount)); //Desenha a quantidade de Bolotas
    drawText(220.0f, 25.0f, "Tijolos Restantes: " + std::to_string(this->currentLevel->liveBricks)); //Desenha a quantidade de Bolotas
    drawMessages();
    
    if(this->gamePaused){ //Se o jogo estiver pausado, informa o jogador
        if (this->gameEnd) {
            drawText(450.0f, 400.0f, "VC ganhou!!!!");
        } else if (this->changingLevels) {
            drawText(450.0f, 400.0f, "LEVEL COMPLETO");
            drawText(275.0f, 425.0f, "Presisone o Botao Esquerdo do Mouse para ir para outro nivel!");
        } else {
            if (state == 2) {
                drawText(450.0f, 400.0f, "PERDEU TUDO");
                drawText(275.0f, 425.0f, "Presisone o Botao Esquerdo do Mouse para comecar um novo jogo!");
            }
            else {
                drawText(450.0f, 400.0f, "Jogo Pausado!");
                drawText(275.0f, 425.0f, "Presisone o Botao Esquerdo do Mouse para Despausar!");
            }
        }
    }
}

void Breakout::resetBall(){
    ballCount--;
    if(ballCount == 0){
        this->state = 2;
        this->gamePaused = true;
    }else{
        initBall();
    }
}

void Breakout::gameInfo() {
    std::cout << "########## GAME INFO ##########" << std::endl;
    std::cout << "----- PADDLE -----"<< std::endl;
    std::cout << "PosX: " << paddle->x << std::endl;
    std::cout << "VelX: " << paddleVelocity(paddle->x, this->mouseX, paddle->width, (GLfloat)width) << std::endl;
    std::cout << "------ BALL ------" << std::endl;
    std::cout << "PosX: " << ball->x << std::endl;
    std::cout << "PosY: " << ball->y << std::endl;
    std::cout << "VelX: " << ball->velX << std::endl;
    std::cout << "VelY: " << ball->velY << std::endl;
    std::cout << "------ BRICKS ------" << std::endl;
    int k = 0;
    for(std::vector<Brick*>::iterator it = currentLevel->bricks.begin(); it != currentLevel->bricks.end(); ++it ,k++){
        (*it)->drawBrick();
        if((*it)->type != 0){
            std::cout << "ACTIVE BRICK [" << k << "] PosX:" << (*it)->x << " PosY:" << (*it)->y << " Type:" << (*it)->type << " HP:" << (*it)->hp << std::endl;
        }
    }
}


//Handle de eventos de Mouse & Teclado

void Breakout::activeMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        switch (this->gamePaused) {
        case true:
            if (this->state == 2) {
                init();
            }
            else if (this->changingLevels) { //Se estiver realizando uma transição de Fase
                if (this->levelNumber == this->qntLevels) { //Se essa for a fase Final, acaba o Jogo
                    this->gameEnd = true;
                    this->changingLevels = false;
                } else {  //Se não
                    this->levelNumber++; //Aumenta o numero do Level Atual
                    initLevel(); //Carrega o Level Novamente
                    this->changingLevels = false; //Encerra a transição de Fase
                }
            } else { //Se não estiver realizando transição de Fase
                if(!this->gameEnd) this->gamePaused = false; //Despauza o jogo se ele ainda não tiver acabado
                std::cout << "RESUME GAME" << std::endl;
            }
            break;

        case false:
            this->gamePaused = true;
            std::cout << "PAUSE GAME" << std::endl;
            break;
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if(this->state != 2){ //desabilita debug em caso de game over
            this->gamePaused = true;
            this->state = 3;
        }
    }
}

void Breakout::passiveMouse(int x, int y) {
    this->mouseX = (GLfloat)x;
}

void Breakout::activeKeyboard(int key, int x, int  y) {
    std::cout << "Key pressed:: " << key << std::endl;
    switch (key) {
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

void Breakout::specialActiveKeyboard(int key, int x, int y) {
    std::cout << "Key pressed:: " << key << std::endl;
}
