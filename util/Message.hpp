#ifndef __MESSAGE__
#define __MESSAGE__

#include <GL/freeglut.h>
#include <iostream>

class Message {
    public:
        std::string message;
        int timer;
        float posY;
        Message();
        Message(std::string, int ,float);
};

#endif