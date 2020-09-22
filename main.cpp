#include <iostream>
#include <vector>
#include <string>
#include <GL/freeglut.h>

#include "breakout/breakout.hpp"

#define WIDTHPX  1000
#define HEIGHTPX 600

Breakout breakout(WIDTHPX,HEIGHTPX);

void activeMouse(int button, int state, int x, int y){
	breakout.activeMouse(button, state, x, y);
}

void passiveMouse(int x, int y){
    breakout.passiveMouse(x, y);
}

void activeKeyboard(unsigned char key, int x, int y){
	breakout.activeKeyboard(key, x, y);
}

void specialActiveKeyboard(int key, int x, int y){
	breakout.specialActiveKeyboard(key, x, y);
}

void display(){
    breakout.display();
}

void initOpenGLEnvironment(int width, int height){
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.106f, 0.106f, 0.200f, 1.0f); // Set background frame color
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WIDTHPX,HEIGHTPX);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Breakout");

    initOpenGLEnvironment(WIDTHPX,HEIGHTPX);

    glutDisplayFunc(display);
    glutMouseFunc(activeMouse);
    glutPassiveMotionFunc(passiveMouse);
	glutKeyboardFunc(activeKeyboard);
	glutSpecialFunc(specialActiveKeyboard);

    glutMainLoop();

    return 0;
}
