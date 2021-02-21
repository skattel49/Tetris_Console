#ifndef TILES_H
#define TILES_H
#include "Tiles.h"
#endif

/*
#
###
*/

class BRicky: public Tiles{
    public:
        BRicky(int height, int width);
        ~BRicky();
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
        char** ricky;
        int posX, posY;
        int endX, endY;
};