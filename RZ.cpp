#include "RZ.h"

RZ::RZ(int height, int width): Tiles(){
    //size of matrix that contains our tile
    
    this->size = 3;
    this->posX = width/2;
    this->posY = 0;
    this->endX = this->posX + size;
    this->endY = this->posY + size;

    this->state = 0;
    this->rz = new char*[3];
    for(int i = 0; i<3; i++){
        this->rz[i] = new char[3];
    }
    //initialize tile's form
    changeState('a');
}

void RZ::changeState(char key){
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
    if(this->state%2==0){
        this->state = 0;
    }
    else if(this->state<0){
        this->state = 1;
    }
    for(int i = 0; i<this->size; i++){
        for(int j = 0; j<this->size; j++){
            rz[i][j] = '\0';
        }
    }

    rz[1][1] = '#';
    rz[2][1] = '#';
    //find which state the tile is in
    switch(this->state){
        case 0:
            rz[1][0] = '#';
            rz[2][2] = '#';
            break;
        case 1:
            rz[0][2] = '#';
            rz[1][2] = '#';
            break;
    }
}

int RZ::getSize(void){
    return this->size;
}

char RZ::getChar(int y, int x){
    //a and b are relative coordinates with the position of our tile in the board
    int rel_x = x-this->posX;
    int rel_y = y-this->posY;

    return this->rz[rel_y][rel_x];
}

void RZ::updateY(){
    this->posY++;
    this->endY++;
}

void RZ::updateX(char key){
    if(key == 'j'){
        this->posX--;
        this->endX--;
    }
    else{
        this->posX++;
        this->endX++;
    }
}

int RZ::getPosX(){
    return this->posX;
}

int RZ::getPosY(){
    return this->posY;
}

int RZ::getEndX(){
    return this->endX;
}

int RZ::getEndY(){
    return this->endY;
}

RZ::~RZ(){
    for(int i = 0; i<3; i++){
        delete[] this->rz[i];
    }
    delete this->rz;
}