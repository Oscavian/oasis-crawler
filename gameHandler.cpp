//
// Created by oskar on 07.03.22.
//

#include "header/gameHandler.h"
#include "iostream"
//#if defined(_WIN32)
//#include "conio.h"
//#endif
#include "header/gameUtils.h"
#include "header/world.h"
#include "header/player.h"

gameHandler::gameHandler() {
    hyrule = new World();
}

gameHandler::~gameHandler(){
   delete hyrule;
};
void gameHandler::startGame() {
    char input = '\0';
    do {
        hyrule->drawWorld();
        std::cout << "walk to (w,a,s,d): \n";
        input = getInput(movement);
        hyrule->movePlayerIfPossible(input);
        hyrule->doCellAction();
#if defined(_WIN32)
        system("cls");
#elif defined(__linux__)
        system("clear");
#endif
    } while (hyrule->player->getCurrentHealth() > 0 && hyrule->player->getFoundRelics() < hyrule->getRelicCount() && input != 'x');

}

char gameHandler::getInput(enum inputType inputType) {
    std::string input;
    char action = '\0';
    bool inputOkay = false;
    do {
        //input = (char)getch();
        getline(std::cin, input);
        switch (inputType) { //TODO input method
            case movement:
                inputOkay = true;
                break;
            case dice:
                break;
            case yesorno:
                break;
            default:
                std::cout << "\nWrong input!\n";
        }
    } while (!inputOkay);


    action = input[0];

    return action;
}
