#include "Game.h"

int main(int argc, char* argv[]){
    if (Game_Init()){
        Game_Run();
        Game_End();
    }
    return 0;
}