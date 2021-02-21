#include "Smash.h"

Smash::Smash(int height, int width): Tiles(){
    //size of matrix that contains our tile
    
    this->size = 2;
    this->posX = width/2;
    this->posY = 0;
    this->endX = this->posX + size;
    this->endY = this->posY + size;

    this->state = 0;
    this->smash = new char*[size];
    for(int i = 0; i<size; i++){
        this->smash[i] = new char[size];
    }
    
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            this->smash[i][j] = '#';
        }
    }
}

int Smash::getSize(void){
    return this->size;
}

char Smash::getChar(int y, int x){
    //a and b are relative coordinates with the position of our tile in the board
    int rel_x = x-this->posX;
    int rel_y = y-this->posY;
    return this->smash[rel_y][rel_x];
}

void Smash::updateY(){
    this->posY++;
    this->endY++;
}

void Smash::updateX(char key){
    if(key == 'j'){
        this->posX--;
        this->endX--;
    }
    else{
        this->posX++;
        this->endX++;
    }
}

int Smash::getPosX(){
    return this->posX;
}

int Smash::getPosY(){
    return this->posY;
}

int Smash::getEndX(){
    return this->endX;
}

int Smash::getEndY(){
    return this->endY;
}


Smash::~Smash(){
    for(int i = 0; i<2; i++){
        delete[] this->smash[i];
    }
    delete this->smash;
}