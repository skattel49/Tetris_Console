#ifndef BOARD_H
#define BOARD_H
#include "Board.h"
#endif
#include <iostream>


Board::Board(int height, int width){
    //initialize height and width of the board
    this->height = height;
    this->width = width;
    //has count of all hashes in a row excluding the boundaries
    this->count_hashes.reserve(height);
    //initialize score
    this->score = 0;
    //dynamically allocate 2d array of characters for the board
    this->board = new char*[height];
    for(int i = 0; i<height; i++){
        this->board[i] = new char[width];
    }
}

//draw the board and the tiles
void Board::testDraw(Tiles* player){
    int x = player->getPosX();
    int y = player->getPosY();
    int s = player->getSize();

    std::cout<<"Controls of the game: "<<std::endl;
    std::cout<<"a + Enter : Rotate Left, d + Enter: Rotate Right"<<std::endl;
    std::cout<<"j + Enter : Move Left, k + Enter : Move Right"<<std::endl;

    for(int i = 0; i<height; i++){
        std::cout<<"@";
        for(int j = 0; j<width; j++){
            //if the board already has a tile then display it
            if(board[i][j] == '#'){
                std::cout<<'#';
                continue;
            }

            //if the board coincides with our tile matrix then and only then
            //print the matrices
            if(i>=y && i<y+s && j>=x && j<x+s){
                if(player->getChar(i, j) == '#'){
                    std::cout<<'#';
                }
                else{
                    std::cout<<" ";
                }
            }
            else{
                std::cout<<" ";    
            }
        }
        std::cout<<"@"<<"\n";
    }
    //prints the base
    for(int j = 0; j<width+2; j++){
        std::cout<<"@";
    }
    std::cout<<std::endl;
    std::cout<<"Your Score: "<<score*100<<std::endl;
}

//preserve the state of our tile in the board
void Board::preserveState(Tiles* player){
    int x = player->getPosX();
    int y = player->getPosY();
    int s = player->getSize();
    //copy the hashes of the matrix if it reaches the desired destination
    for(int i = y; i<y+s; i++){
        for(int j = x; j<x+s; j++){
            if(player->getChar(i, j)=='#'){
                board[i][j] = '#';
            }
        }
    }
}

//check to the left of the tile matrix
bool Board::positionValidLeftX(Tiles* player){
    int x = player->getPosX();
    int y = player->getPosY();
    int s = player->getSize();
    
    /*
        # @**
        # @@*
        # *@*
        if there is a hash at any of these positions then we cannot go left
    */
    int first_hash_of_row[s];
    for(int i = 0; i<s; i++){
        for(int j = 0; j<s; j++){
            if(player->getChar(y+i, x+j)=='#'){
                first_hash_of_row[i] = j;
                break;
            }
            else if(j == s-1){
                first_hash_of_row[i] = 20;
            }
        }
    }
    //if there is a # before the first hash of a row in our tile matrix
    //then we cannot move our tile left
    for(int i = 0; i<s; i++){
        //no need to check if there is no hash in our row in the tile matrix
        if(first_hash_of_row[i] == 20){
            continue;
        }
        if(x+first_hash_of_row[i]-1<0 || board[y+i][x+first_hash_of_row[i]-1] == '#'){
            return false;
        }
    }
    return true;
}
//check to the right of the tile
bool Board::positionValidRightX(Tiles* player){
    int end_x = player->getEndX();
    int y = player->getPosY();
    int s = player->getSize();

    /*
        $$$#
        $$$#
        $$$#
        if there is a hash at any of these positions then we cannot go right
    */
    int last_hash_of_row[s];
    for(int i = 0; i<s; i++){
        for(int j = 0; j<s; j++){
            if(player->getChar(y+i, end_x-j-1)=='#'){
                last_hash_of_row[i] = j;
                break;
            }
            else if(j == 0){
                last_hash_of_row[i] = -20;
            }
        }
    }
    //if there is a # after the last hash of a row in our tile matrix
    //then we cannot move our tile right
    for(int i = 0; i<s; i++){
        if(last_hash_of_row[i] == -20){
            continue;
        }
        if(end_x-last_hash_of_row[i]>=width || board[y+i][end_x-last_hash_of_row[i]] == '#'){
            return false;
        }
    }
    return true;
}
//check the y position of the tile
bool Board::positionValidY(Tiles* player){
    int x = player->getPosX();
    int y = player->getPosY();
    int end_y = player->getEndY();
    int s = player->getSize();
    /*
        $$$
        $$$
        $$$
        ###
    */
    int last_hash_of_columns[s];
    for(int i = 0; i<s; i++){
        for(int j = 0; j<s; j++){
            if(player->getChar(end_y-j-1, x+i)=='#'){
                last_hash_of_columns[i] = j;
                break;
            }
            else if(j == s-1){
                last_hash_of_columns[i] = -20;
            }
        }
    }

    for(int i = 0; i<s; i++){
        if(last_hash_of_columns[i] == -20){
            continue;
        }
        //if if any of the hashes reach height or they have a hash below them 
        //the position is not valid for the next round
        if(end_y-last_hash_of_columns[i]>=height ||\
                 board[end_y-last_hash_of_columns[i]][x+i] == '#' ){
            return false;
        }
    }

   return true;
}
//check if the tile can be rotated at current position
void Board::validateAndRotate(Tiles* player, char user_in){
    bool flag = true;
    int x = player->getPosX();
    int y = player->getPosY();
    int s = player->getSize();

    if(user_in == 'a'){
        flag = false;
    }
    player->changeState(user_in);

    //check if one of it's position is not valid
    if(!(positionValidY(player) && positionValidLeftX(player) && positionValidRightX(player))){
        //if it is not valid then flip back and return
        if(flag){
            player->changeState('a');
        }
        else{
            player->changeState('d');
        }
        return;
    }

    //if rotation is not valid then change state back to normal
    for(int i = y; i<y+s; i++){
        for(int j = x; j<x+s; j++){
            //check if the tile overlaps with the board's #
            if(board[i][j] == '#' && player->getChar(i,j) == '#'){
                if(flag){
                    player->changeState('a');
                }
                else{
                    player->changeState('d');
                }
            }
        }
    }
}

void Board::reconfigureBoard(int row){
    for(int i = row; i>0; i--){
        for(int j = 0; j<width; j++){
            //copy the row above this row
            board[i][j] = board[i-1][j];
        }
    }
    //first row of the board will always be cleared
    for(int j = 0; j<width; j++){
        board[0][j] = '\0';
    }
}

void Board::showCompletedRow(int row){
    system("clear");
    std::cout<<"Controls of the game: "<<std::endl;
    std::cout<<"a + Enter : Rotate Left, d + Enter: Rotate Right"<<std::endl;
    std::cout<<"j + Enter : Move Left, k + Enter : Move Right"<<std::endl;

    for(int i = 0; i<height; i++){
        std::cout<<"@";
        for(int j = 0; j<width; j++){
            if(i==row){
                std::cout<<"*";
                continue;
            }
            //if the board already has a tile then display it
            if(board[i][j] == '#'){
                std::cout<<'#';
                continue;
            }
        }
        std::cout<<"@"<<"\n";
    }
    //prints the base
    for(int j = 0; j<width+2; j++){
        std::cout<<"@";
    }
    std::cout<<std::endl;
    std::cout<<"Your Score: "<<score*100<<std::endl;
}

void Board::hashesCount(){
    int tmp;
    for(int i = 0; i<height; i++){
        tmp = 0;
        for(int j = 0; j<width; j++){
            if(board[i][j] == '#'){
                tmp++;
            }
        }
        count_hashes[i] = tmp;
        if(tmp == width){
            reconfigureBoard(i);
            showCompletedRow(i);
            score++;
        }
    }
}

Board::~Board(){
    for(int i = 0; i<this->height; i++){
        delete[] this->board[i];
    }
    delete[] this->board;
}