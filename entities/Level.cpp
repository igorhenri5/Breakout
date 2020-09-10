#include "Level.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>

Level::Level() {
}

Level::Level(std::string layout) {
    this->layout = layout;
    int brickWidth = 90;
    int brickHeight = 45;
    int col = 1;
    int row = 0;
    for (char& c : layout) {
        switch (c) {
        case '0':
            bricks.push_back(new Brick(row * 100 + 5, col * 50, brickWidth, brickHeight, 0));
            row++;
            break;

        case '1':
            bricks.push_back(new Brick(row * 100 + 5, col * 50, brickWidth, brickHeight, 1));
            row++;
            break;

        case '2':
            bricks.push_back(new Brick(row * 100 + 5, col * 50, brickWidth, brickHeight, 2));
            row++;
            break;

        case '|':
            col++;
            row = 0;
            break;
        }
        
    }
}
