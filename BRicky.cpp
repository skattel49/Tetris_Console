#include "BRicky.h"
BRicky::BRicky(int height, int width): Tiles(){
    //size of matrix that contains our tile
    
    this->size = 3;
    this->posX = width/2;
    this->posY = 0;
    this->endX = this->posX + size;
    this->endY = this->posY + size;

    this->state = 0;
    this->ricky = new char*[3];
    for(int i = 0; i<3; i++){
        this->ricky[i] = new char[3];
    }
    //initialize tile's form
    ricky[1][0] = '#';
    for(int i = 0; i<3; i++){
        ricky[2][i] = '#';
    }
}

void BRicky::changeState(char key){
    //left rotate
    if(key == 'a'){
        this->state--;
    }
    //right rotate
    else if(key == 'd'){
        this->state++;
    }
    //circular loop to make state change
    //easier
    if(this->state%4==0){
        this->state = 0;
    }
    else if(this->state<0){
        this->state = 3;
    }
    for(int i = 0; i<this->size; i++){
        for(int j = 0; j<this->size; j++){
            ricky[i][j] = '\0';
        }
    }
    //find which state the tile is in
    switch(this->state){
        case 0:
            ricky[1][0] = '#';
            for(int i = 0; i<3; i++){
                ricky[2][i] = '#';
            }
            break;
        case 1:
            ricky[0][0] = '#';
            for(int i = 0; i<3; i++){
                ricky[i][1] = '#';
            }
            break;
        case 2:
            ricky[2][2] = '#';
            for(int i = 0; i<3; i++){
                ricky[1][i] = '#';
            }
            break;
        case 3:
            ricky[2][0] = '#';
            for(int i = 0; i<3; i++){
                ricky[i][1] = '#';
            }
            break;
    }
}

int BRicky::getSize(void){
    return this->size;
}

char BRicky::getChar(int y, int x){
    //a and b are relative coordinates with the position of our tile in the board
    int rel_x = x-this->posX;
    int rel_y = y-this->posY;
    //std::cout<<rel_y<<" "<<rel_x<<std::endl;
    return this->ricky[rel_y][rel_x];
}

void BRicky::updateY(){
    this->posY++;
    this->endY++;
}

void BRicky::updateX(char key){
    if(key == 'j'){
        this->posX--;
        this->endX--;
    }
    else{
        this->posX++;
        this->endX++;
    }
}

int BRicky::getPosX(){
    return this->posX;
}

int BRicky::getPosY(){
    return this->posY;
}

int BRicky::getEndX(){
    return this->endX;
}

int BRicky::getEndY(){
    return this->endY;
}

BRicky::~BRicky(){
    for(int i = 0; i<3; i++){
        delete[] this->ricky[i];
    }
    delete this->ricky;
}