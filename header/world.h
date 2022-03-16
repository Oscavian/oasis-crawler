//
// Created by oskar on 03.03.22.
//

#ifndef CRAWLERKLASSEN_WORLD_H
#define CRAWLERKLASSEN_WORLD_H

#include "gameUtils.h"
#include "player.h"
#include "iostream"

class World {

public:
    World(unsigned int sideLength, unsigned int level);
    virtual ~World();
    static char getInput(enum inputType inputType);
    Player *player;
    void drawWorld();
    void movePlayer(Coords validCoords) const;
    bool positionIsValid(Coords coords) const;
    bool movePlayerIfPossible(char direction) const;
    int getRelicCount() const;
    void doCellAction();
    void encounterDanger();
    void encounterRock();
    void encounterRavine();
    void encounterLake();
    void encounterFairyFountain();
    void findRelic();
    void giveRndItem();
    static int rollDice(int maxEyes);
    void redrawWorld(); // draw + clear
    static void clearScreen();

private:
    unsigned int m_worldSize;
    int m_relicCount;
    enum cellType m_cells[50][50];
    std::string statusMessage;
    unsigned int m_currentLevel;
};

#endif //CRAWLERKLASSEN_WORLD_H
