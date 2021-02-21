#include "Teewee.h"

Teewee::Teewee(int height, int width): Tiles(){
    //size of matrix that contains our tile
    
    this->size = 4;
    this->posX = width/2;
    this->posY = 0;
    this->endX = this->posX + size;
    this->endY = this->posY + size;

    this->state = 0;
    this->teew = new char*[size];
    for(int i = 0; i<size; i++){
        this->teew[i] = new char[size];
    }
    //initialize tile's form
    for(int i = 0; i<size; i++){
        teew[i][1] = '#';
    }
}

void Teewee::changeState(char key){
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
            teew[i][j] = '\0';
        }
    }
    //find which state the tile is in
    switch(this->state){
        case 0:
            for(int i = 0; i<size; i++){
                teew[i][1] = '#';
            }
            break;
        case 1:
            for(int i = 0; i<size; i++){
                teew[1][i] = '#';
            }
            break;
    }
}

int Teewee::getSize(void){
    return this->size;
}

char Teewee::getChar(int y, int x){
    //a and b are relative coordinates with the position of our tile in the board
    int rel_x = x-this->posX;
    int rel_y = y-this->posY;

    return this->teew[rel_y][rel_x];
}

void Teewee::updateY(){
    this->posY++;
    this->endY++;
}

void Teewee::updateX(char key){
    if(key == 'j'){
        this->posX--;
        this->endX--;
    }
    else{
        this->posX++;
        this->endX++;
    }
}

int Teewee::getPosX(){
    return this->posX;
}

int Teewee::getPosY(){
    return this->posY;
}

int Teewee::getEndX(){
    return this->endX;
}

int Teewee::getEndY(){
    return this->endY;
}

Teewee::~Teewee(){
    for(int i = 0; i<3; i++){
        delete[] this->teew[i];
    }
    delete this->teew;
}