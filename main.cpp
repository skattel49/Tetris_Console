#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <time.h>
#include <random>
#include <termios.h>
#include "all_headers.h"

using namespace std;

char user_in='\0';

void Input(){
    // while(true){
    //     cin>>user_in;
    //     if(user_in == 'q'){
    //         break;
    //     }
    // }
    
    struct termios old_state, new_state;
    //get the current state of stdin
    tcgetattr(STDIN_FILENO, &old_state);
    //copy the state to modify it
    new_state = old_state;
    //turn off canonical mode and turn echo for stdin off
    new_state.c_lflag &= (~ICANON & ~ECHO);
    //set the new attribute this instant
    tcsetattr(STDIN_FILENO, TCSANOW, &new_state);

    while(user_in!='q'){
        cin>>user_in;
    }

    //reset all the settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_state);
}

int random_tiles(){
    srand(time(0));
    int x = rand() % 7;
    return x;
}

void Logic(){
    //set the height and width of the game
    int height = 30, width = 30;
    //initialize board with height and width
    Board x(height, width);
    //create an abstract pointer for 7 different tiles
    Tiles* tile;
    //flag that produces random tiles after a certain condition
    bool flag = true;
    int random_num = 0;
    while(true){
        //clear the screen
        system("clear");
        //exit the game if user inputs q
        if(user_in == 'q'){
            break;
        }
        //randomly generate tiles after it is placed or is at the bottom
        if(flag){
            flag = false;
            random_num = random_tiles();
            if(random_num == 0){
                BRicky* brick = new BRicky(height, width);
                tile = brick;
            }
            else if(random_num == 1){
                ORicky* rick = new ORicky(height, width);
                tile = rick;
            }
            else if(random_num == 2){
                CZ* cz = new CZ(height, width);
                tile = cz;
            }
            else if(random_num == 3){
                RZ* rz = new RZ(height, width);
                tile = rz;
            }
            else if(random_num == 4){
                Hero* hero = new Hero(height, width);
                tile = hero;
            }
            else if(random_num == 5){
                Teewee* tew = new Teewee(height, width);
                tile = tew;
            }
            else if(random_num == 6){
                Smash* smash = new Smash(height, width);
                tile = smash;
            }
        }
        //draw tiles on the board
        x.testDraw(tile);
        //count the number of hashes in all row and reconfigure the board
        //if the hashes are equal to the width
        x.hashesCount();

        if(user_in == 'a' || user_in == 'd'){
            //if the rotation is valid then rotate
            x.validateAndRotate(tile, user_in);
        }
        else if(user_in == 'j' || user_in == 'k'){
            //check if the next position of tile is valid and update it's position
            if(user_in == 'j' && x.positionValidLeftX(tile)){
                tile->updateX(user_in);
            }
            else if(user_in == 'k' && x.positionValidRightX(tile)){
                tile->updateX(user_in);
            }
        }
        //check if the tile reached the end or it's position is not valid
        if(!x.positionValidY(tile)){
            //preserve the state of the board with the current tile
            x.preserveState(tile);   
            delete tile;
            flag = true;
        }
        else{
            tile->updateY();
        }
        //reset user input so it does not go to if clause on the next round
        user_in = '\0';
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int main(){
    //thread for input
    thread t2(Input);
    //thread for gameplay
    thread t1(Logic);
    t1.join();
    t2.join();
    system("clear");
    cout<<"The game has ended"<<endl;
}