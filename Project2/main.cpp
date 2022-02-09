
#include "Game.h"

int main(){
    Game g;
    while(!g.checkIfGameOver()){
        g.printGame();
        g.choose();
    }
}
