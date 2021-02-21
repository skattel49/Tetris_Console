#ifndef TILES_H
#define TILES_H
#include "Tiles.h"
#endif

/*
 ##
##
*/

class RZ:public Tiles{
    public:
        RZ(int height, int width);
        ~RZ();
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
        char** rz;
        int posX, posY;
        int endX, endY;
};