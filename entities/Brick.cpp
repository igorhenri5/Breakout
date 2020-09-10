#include "Brick.hpp"

Brick::Brick(){
}

Brick::Brick(GLfloat x, GLfloat y, GLfloat width, GLfloat height, int type){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->type = type;

    if(type == 0) this->tangivel = false;
    else this->tangivel = true;
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
    }

    glEnd();
}