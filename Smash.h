#ifndef TILES_H
#define TILES_H
#include "Tiles.h"
#endif

/*
#
###
*/

class Smash:public Tiles{
    public:
        Smash(int height, int width);
        ~Smash();
        void changeState(char key){}
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
        char** smash;
        int posX, posY;
        int endX, endY;
};