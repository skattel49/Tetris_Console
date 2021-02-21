#include "Hero.h"
Hero::Hero(int height, int width): Tiles(){
    //size of matrix that contains our tile
    
    this->size = 3;
    this->posX = width/2;
    this->posY = 0;
    this->endX = this->posX + size;
    this->endY = this->posY + size;

    this->state = 0;
    this->hero = new char*[3];
    for(int i = 0; i<3; i++){
        this->hero[i] = new char[3];
    }
    //initialize tile's form
    hero[1][1] = '#';
    for(int i = 0; i<3; i++){
        hero[2][i] = '#';
    }
}

void Hero::changeState(char key){
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
            hero[i][j] = '\0';
        }
    }
    //find which state the tile is in
    switch(this->state){
        case 0:
            hero[1][1] = '#';
            for(int i = 0; i<3; i++){
                hero[2][i] = '#';
            }
            break;
        case 1:
            hero[1][2] = '#';
            for(int i = 0; i<3; i++){
                hero[i][1] = '#';
            }
            break;
        case 3:
            hero[1][0] = '#';
            for(int i = 0; i<3; i++){
                hero[i][1] = '#';
            }
            break;
        case 2:
            hero[2][1] = '#';
            for(int i = 0; i<3; i++){
                hero[1][i] = '#';
            }
            break;
    }
}

int Hero::getSize(void){
    return this->size;
}

char Hero::getChar(int y, int x){
    //a and b are relative coordinates with the position of our tile in the board
    int rel_x = x-this->posX;
    int rel_y = y-this->posY;
    //std::cout<<rel_y<<" "<<rel_x<<std::endl;
    return this->hero[rel_y][rel_x];
}

void Hero::updateY(){
    this->posY++;
    this->endY++;
}

void Hero::updateX(char key){
    if(key == 'j'){
        this->posX--;
        this->endX--;
    }
    else{
        this->posX++;
        this->endX++;
    }
}

int Hero::getPosX(){
    return this->posX;
}

int Hero::getPosY(){
    return this->posY;
}

int Hero::getEndX(){
    return this->endX;
}

int Hero::getEndY(){
    return this->endY;
}

Hero::~Hero(){
    for(int i = 0; i<3; i++){
        delete[] this->hero[i];
    }
    delete this->hero;
}