#include <iostream>
#include "GameState.h"
#include "game.h"
#include "ai.h"

using namespace std;

int main(){
    int x;
    main_menu();
    while (x != 5 && cin >> x) {
        if (x == 1) {
            PlayAgainst(PlayerMove);
        }
        else if (x == 2) {
            PlayAgainst(validMove);
        }
        else if (x == 3) {
            PlayAgainst(findBestMove);
        }
        else if (x == 4) {
            settings();
        }

        main_menu();
    }
    system("clear");
}