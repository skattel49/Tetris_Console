#define BOARD_H

#include "all_headers.h"

#include <vector>

class Board{
    public:
        Board(int height, int width);
        void testDraw(Tiles* player);
        void preserveState(Tiles* player);
        bool positionValidLeftX(Tiles* player);
        bool positionValidRightX(Tiles* player);
        bool positionValidY(Tiles* player);
        void validateAndRotate(Tiles* player, char user_in);
        void hashesCount();
        void reconfigureBoard(int row);
        void showCompletedRow(int row);
        ~Board();
    private:
        std::vector<int> count_hashes;
        char** board;
        int height, width;
        int score;
};