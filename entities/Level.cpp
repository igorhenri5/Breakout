#include "Level.hpp"

Level::Level() {
}

Level::Level(std::string layout) {
    this->layout = layout;
    // int brickWidth = 90;
    // int brickHeight = 45;
    // int spacing = 5;
    int brickWidth = 45;
    int brickHeight = 23;
    float spacing = 2.5f;
    int col = 1;
    int row = 0;
    for(char& c : layout){
        if(c == '|'){
            col++;
            row = 0;
        }else if(c>= 48 && c<= 53){
            bricks.push_back(new Brick(row * (brickWidth+2*spacing) + spacing, col * (brickHeight+2*spacing), brickWidth, brickHeight, c-48));
                row++;
        }
    }
}
