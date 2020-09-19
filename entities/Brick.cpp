#include "Brick.hpp"

Brick::Brick(){
}

Brick::Brick(GLfloat x, GLfloat y, GLfloat width, GLfloat height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Brick::Brick(GLfloat x, GLfloat y, GLfloat width, GLfloat height, int type){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->type = type;
    this->tangivel = true;

    switch(type){
        case 0: //vazio            
            this->tangivel = false;
            break;
        case 1: //verde
            this->hp = 1;
            break;
        case 2: //vermelho
            this->hp = 1;
            break;
        case 3: //azul
            this->hp = 2;
            break;
        case 4: //amarelo
            this->hp = 3;
            break;
    }
}

void Brick::drawBrick() { //Desenha cada um dos Tijolos

    if (this->tangivel && this->type != 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    switch (this->type) { //Escolhe a cor base do Tijolo com base no Tipo
        default:
            glColor3f(0.0f, 1.0f - 0.2f, 0.2f);
            break;

        case 2:
            glColor3f(1.0f, 0.0f, 0.2f);
            break;

        case 3:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;

        case 4:
            glColor3f(0.8f, 0.9f, 0.2f);
            break;

        case 5:
            glColor3f(0.35f, 0.35f, 0.35f);
            break;
    }

    glRectf(this->x, this->y, this->x + this->width, this->y + this->height);

    glBegin(GL_QUADS);
    switch (this->type) { //Estiliza o Tijolo com base no Tipo
        default: //Default -> Tipo 1 ou 0, Bloco Verde
            glColor3f(0.0f, 1.0f - 0.2f, 0.2f);
            glVertex2f(this->x, this->y);
            glColor3f(0.0f, 1.0f - 0.05f, 0.25f);
            glVertex2f(this->x + this->width, this->y);
            glColor3f(0.0f, 1.0f - 0.15f, 0.45f);
            glVertex2f(this->x + this->width, this->y + this->height);
            glVertex2f(this->x, this->y);
            break;

        case 2: //Tipo 2 -> Bloco Vermelho
            glColor3f(1.0f - 0.2f, 0.2f, 0.2f);
            glVertex2f(this->x, this->y);
            glColor3f(1.0f - 0.05f, 0.2f, 0.25f);
            glVertex2f(this->x + this->width, this->y);
            glColor3f(1.0f - 0.15f, 0.2f, 0.45f);
            glVertex2f(this->x + this->width, this->y + this->height);
            glVertex2f(this->x, this->y);
            break;

        case 3: //Tipo 3 -> Bloco Azul
            //MUDAR PRA COR CERTA
            glColor3f(0.2f, 0.2f, 1.0f - 0.2f);
            glVertex2f(this->x, this->y);
            glColor3f(0.25f, 0.2f, 1.0f - 0.05f);
            glVertex2f(this->x + this->width, this->y);
            glColor3f(0.45f, 0.2f , 1.0f - 0.15f);
            glVertex2f(this->x + this->width, this->y + this->height);
            glVertex2f(this->x, this->y);
            break;

        case 4: //Tipo 4 -> Bloco Amarelo
            //MUDAR PRA COR CERTA
            glColor3f(0.8f - 0.1f, 0.9f, 0.2f);
            glVertex2f(this->x, this->y);
            glColor3f(0.8f - 0.1f, 0.9f, 0.25f);
            glVertex2f(this->x + this->width, this->y);
            glColor3f(0.8f - 0.15f, 0.9f, 0.3f);
            glVertex2f(this->x + this->width, this->y + this->height);
            glVertex2f(this->x, this->y);
            break;

        case 5: //Tipo 5 -> Bloco Cinza
            //MUDAR PRA COR CERTA
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex2f(this->x, this->y);
            glColor3f(0.3f, 0.3f, 0.3f);
            glVertex2f(this->x + this->width, this->y);
            glColor3f(0.4f, 0.4f, 0.4f);
            glVertex2f(this->x + this->width, this->y + this->height);
            glVertex2f(this->x, this->y);
            break;

    }
    glEnd();
}

int Brick::takeHit(){
    
    switch(type){
        case 1: //verde
            this->hp = 0;
            this->tangivel = false;
            return 50;
            break;
        case 2: //vermelho
            this->hp = 0;
            this->tangivel = false;
            return 100;
            break;
        case 3: //azul decai pra verde
            this->hp -= 1;
            this->type = 1;
            return 100;
            break;
        case 4: //amarelo decai pra azul
            this->hp -= 1;
            this->type = 3;
            return 250;
            break;
        case 5: //cinza
            return -5;
            break;
    }
    return 0;
}