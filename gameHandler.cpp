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
#include <cassert>

gameHandler::gameHandler() {
    hyrule = nullptr;
    m_currentLevel = 1;
}

gameHandler::~gameHandler(){
    if (hyrule->getRelicCount() == hyrule->player->getFoundRelics()){
        std::cout << "You won! The game is over.";
    } else if (hyrule->player->getCurrentHealth() == 0){
        std::cout << "You died! Game over.";
    }
   delete hyrule;
}

void gameHandler::startGame() {
    char input = '\0';
    for (int i = 10; i <= 50; i += 5){
        hyrule = new World(i, m_currentLevel);
        hyrule->drawWorld();
        do {
            input = World::getInput(movement);
            hyrule->movePlayerIfPossible(input);
            World::clearScreen();
            hyrule->doCellAction();
            hyrule->drawWorld();
        } while (hyrule->player->getCurrentHealth() > 0 && hyrule->player->getFoundRelics() < hyrule->getRelicCount());
        m_currentLevel++;
        if (m_currentLevel != 10){
            std::cout << "\nLevel cleared!\nContinue playing? (y/n)\n";
            if (World::getInput(yesorno) == 'n'){
                std::cout << "Game aborted. Thank you for playing!\n";
                delete hyrule;
                break;
            }
        } else {
            std::cout << "Thank you so much for playing my game <3\n";
        }
        World::clearScreen();
        assert("Player not deleted: " && hyrule->player != nullptr);
        delete hyrule;
    }
    assert("World not deleted:" && hyrule != nullptr);
}