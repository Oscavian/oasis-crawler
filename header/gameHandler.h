//
// Created by oskar on 07.03.22.
//

#ifndef CRAWLERKLASSEN_GAMEHANDLER_H
#define CRAWLERKLASSEN_GAMEHANDLER_H
#include "player.h"
#include "world.h"
#include "gameUtils.h"

class gameHandler {
public:
    gameHandler();
    ~gameHandler();
    void startGame();
private:
    World* hyrule;
    unsigned int m_currentLevel;
};

#endif //CRAWLERKLASSEN_GAMEHANDLER_H
