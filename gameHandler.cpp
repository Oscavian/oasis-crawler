//
// Created by oskar on 07.03.22.
//

#include "header/gameHandler.h"
#include "iostream"
#if defined(_WIN32)
#include "conio.h"
#endif
#include "header/gameUtils.h"
#include "header/world.h"
#include "header/player.h"

gameHandler::gameHandler() {
    hyrule = new World();
}

gameHandler::~gameHandler(){
    if (hyrule->getRelicCount() == hyrule->player->getFoundRelics()){
        std::cout << "You won! The game is over.";
    } else if (hyrule->player->getCurrentHealth() == 0){
        std::cout << "You died! Game over.";
    }
   delete hyrule;
};

void gameHandler::startGame() {
    char input = '\0';
    hyrule->drawWorld();
    do {
        input = hyrule->getInput(movement);
        hyrule->movePlayerIfPossible(input);
#if defined(_WIN32)
        system("cls");
#elif defined(__linux__)
        //system("clear");
#endif
        hyrule->doCellAction();
        hyrule->drawWorld();
    } while (hyrule->player->getCurrentHealth() > 0 && hyrule->player->getFoundRelics() < hyrule->getRelicCount());
}