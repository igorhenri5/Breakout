#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <chrono>
#include <sys/time.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <GL/freeglut.h>
#include <string> 
// #include <GL/glew.h>

// 1) O jogo deve sempre começar no modo pausa, com a “bola” parada em alguma posição
// inicial da tela, e o “paddle” no centro da tela. A tecla R é usada para voltar o jogo para
// essa configuração inicial a qualquer momento.

// 2) A tecla Q, em qualquer momento que for pressionada, termina o programa.

// 3) O botão da esquerda do mouse coloca o jogo num modo de pausa, quando todos os
// objetos são congelados. Quando pressionado no modo de pausa, retorna o jogo ao
// movimento.

// 4) O botão da direita imprime os atributos de todos os objetos, e coloca o jogo em modo
// pausa. Deve listar o “paddle” com sua posição e velocidade, a “bola”, e todos os
// “tijolos”. Pressionado novamente, executa um ciclo do jogo, e novamente imprime todos
// os atributos.

struct timeval tempoInicialAll, tempoFinalAll;
struct timeval tempoInicial, tempoFinal;
float elapsedTimeAll;

int mouse_x, mouse_y;
char buffer[64];

void mouse(int btn, int state, int x, int y){
    float mx = x;
    float my = y;
    float ox = (mx/500-1.0);
    float oy = -(my/500 -1.0);
    switch(btn){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                printf("%f\n",mx);
                printf("%f\n",my);
            }
            break;
    }
};

void passive(int x, int y){
    mouse_x = x; 
    mouse_y = y;
}

void update(){   
}

void draw(){
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
    //     (*drawable)->draw();
    // }
    // glutSwapBuffers();
}

void mainloop(){
    snprintf(buffer, sizeof(buffer), "%d", mouse_x);
    glutSetWindowTitle(buffer);
    // gettimeofday(&tempoInicialAll, NULL);
    // update();
    // gettimeofday(&tempoFinalAll, NULL);
    // draw();

    // elapsedTimeAll += getSeconds(&tempoInicialAll, &tempoFinalAll);
    // if(x<=0){
    //     std::cout << "All ";
    //     printElapsedTime(elapsedTimeAll / 10);
    //     std::cout << std::endl;
    //     elapsedTimeAll = 0;
    //     x=10;
    // }
    // x--;
}

void onClose(){
    // for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
    //     delete (*drawable);
    // }
    // delete game::screenRect;
    // delete game::screenBounds;
    // delete game::quadtree;
    // delete game::threadPool;
    // delete game::masterFlag;
    // std::cout << "onClose" << std::endl;
}

void initOpenGLEnvironment(int width, int height){
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background frame color
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv){
    
    // elapsedTimeAll = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //Sem Vsync
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Breakout");
    // glewInit();
    initOpenGLEnvironment(1000, 1000);
    // initDrawables();
    glutDisplayFunc(draw);
    glutIdleFunc(mainloop);
    glutPassiveMotionFunc(passive);
    glutCloseFunc(onClose);
    glutMainLoop();

    return 0;
}
