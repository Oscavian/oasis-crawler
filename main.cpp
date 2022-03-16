#include <iostream>
#include "header/gameHandler.h"
#define RED "\033[31m"

int main() {
    using namespace std;
    cout << "Welcome to the oasis-crawler!\n Goal: Help Link find all the relics and don't die.\n You (H) start with 5 HP.\nEach level the field size increases! There are 10 levels.\n"
         << "Move the character with w,a,s,d\n"
         << " '~' are normal cells\n '!' are dangers\n '$' are fairy fountains\n '*' are relics\n";
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
