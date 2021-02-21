#ifndef TILES_H
#define TILES_H
#include "Tiles.h"
#endif

/*
  #
###
*/

class Hero:public Tiles{
    public:
        Hero(int height, int width);
        ~Hero();
        void changeState(char key);
        int getSize(void);
        char getChar(int x, int y);
        void updateY();
        void updateX(char key);
        int getPosX();
        int getPosY();
        int getEndX();
        int getEndY();
    private:
        int size;
        int state;
        char** hero;
        int posX, posY;
        int endX, endY;
};