#include <iostream>
#include "header/gameHandler.h"
#define RED "\033[31m"

int main() {
    using namespace std;
    cout << "Welcome to the Game!\n Goal: Help Link find all the relics and don't die.\n You (H) start with 5 HP.\n Don't get caught by Ganon or Zanto, they're after you!\n"
         << "Move the character with w,a,s,d\n";
    gameHandler game = gameHandler();
#if defined(_WIN32)
    system("pause");
    system("cls");
#elif defined(__linux__)
    system("read");
    system("clear");
#endif
    game.startGame();
    return 0;
}
