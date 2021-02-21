#ifndef TILES_H
#define TILES_H
#include "Tiles.h"
#endif

/*
##
 ##
*/

class CZ: public Tiles{
    public:
        CZ(int height, int width);
        ~CZ();
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
        char** cz;
        int posX, posY;
        int endX, endY;
};