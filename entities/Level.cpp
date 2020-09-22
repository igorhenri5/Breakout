#include "Level.hpp"

Level::Level() {
}

Level::Level(std::string layout) {
    this->liveBricks = 0;
    this->layout = layout;
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
                if (c != 53 && c != 48) this->liveBricks++; //Se n�o for do tipo 0 ou 5 (Caracter 53 - N�mero 5) incrementa a quantidade de tijolos "vivos"
        }
    }
}
