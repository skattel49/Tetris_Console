#include "CZ.h"

CZ::CZ(int height, int width): Tiles(){
    //size of matrix that contains our tile
    
    this->size = 3;
    this->posX = width/2;
    this->posY = 0;
    this->endX = this->posX + size;
    this->endY = this->posY + size;

    this->state = 0;
    this->cz = new char*[3];
    for(int i = 0; i<3; i++){
        this->cz[i] = new char[3];
    }
    //initialize tile's form
    changeState('a');
}

void CZ::changeState(char key){
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
            cz[i][j] = '\0';
        }
    }

    cz[1][1] = '#';
    cz[2][1] = '#';
    //find which state the tile is in
    switch(this->state){
        case 0:
            cz[1][0] = '#';
            cz[2][2] = '#';
            break;
        case 1:
            cz[0][2] = '#';
            cz[1][2] = '#';
            break;
    }
}

int CZ::getSize(void){
    return this->size;
}

char CZ::getChar(int y, int x){
    //a and b are relative coordinates with the position of our tile in the board
    int rel_x = x-this->posX;
    int rel_y = y-this->posY;
    return this->cz[rel_y][rel_x];
}

void CZ::updateY(){
    this->posY++;
    this->endY++;
}

void CZ::updateX(char key){
    if(key == 'j'){
        this->posX--;
        this->endX--;
    }
    else{
        this->posX++;
        this->endX--;
    }
}

int CZ::getPosX(){
    return this->posX;
}

int CZ::getPosY(){
    return this->posY;
}

int CZ::getEndY(){
    return this->endY;
}

int CZ::getEndX(){
    return this->endX;
}

CZ::~CZ(){
    for(int i = 0; i<3; i++){
        delete[] this->cz[i];
    }
    delete this->cz;
}