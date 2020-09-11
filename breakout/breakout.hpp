#ifndef __BKOUT__
#define __BKOUT__

#include "../entities/ball.hpp"
#include "../entities/paddle.hpp"
#include "../entities/level.hpp"

#define FRAMETIME 1000/60

class Breakout{
    public:
        int state, score;
        bool gamePaused;
        int width, height;
        GLfloat mouseX;
        Paddle* paddle;
        Ball* ball;
        Level* currentLevel;

        Breakout();
        Breakout(int, int);

        void init();
        void display();
        void update();

        void initPaddle();
        void initBall();
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