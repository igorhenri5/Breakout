#ifndef __BKOUT__
#define __BKOUT__

#include "../entities/ball.hpp"
#include "../entities/brick.hpp"
#include "../entities/paddle.hpp"
#include "../entities/level.hpp"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#define FRAMETIME 1000/60

class Breakout{
    public:
        int state, score;
        bool gamePaused;
        int width, height;
        GLfloat mouseX;
        //std::vector<Brick*> bricks;
        Paddle* paddle;
        Ball* ball;
        Level* currentLevel;

        Breakout();
        Breakout(int, int);

        void init();
        void display();
        void update();
        // void pause();

        void initPaddle();
        void initBall();
        //void initBricks();
        void initLevel();

        void draw();
        void drawPaddle();
        void drawBall();
        void drawBricks();
        void drawText(float, float, std::string);

        void activeMouse(int, int, int, int);
        void passiveMouse(int, int);
        void activeKeyboard(int, int, int);
        void specialActiveKeyboard(int, int, int);
};


#endif