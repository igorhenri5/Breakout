#include "Message.hpp"
#include <iostream>

Message::Message(){
}

Message::Message(std::string message, int timer, float posY){
    this->message = message;
    this->timer = timer;
    this->posY = posY;
}
