//
// Created by oskar on 03.03.22.
//

#ifndef CRAWLERKLASSEN_WORLD_H
#define CRAWLERKLASSEN_WORLD_H

#include "gameUtils.h"
#include "player.h"
#include "iostream"

class World {
    //header player, enemies, etc. to call movement methods
public:
    World(); //TODO: add initial field size as argument
    //TODO: Gefahrenfeld als Elternklasse und versch. Arten als Children
    virtual ~World();
    char getInput(enum inputType inputType);
    Player *player;
    //revealCells() TODO: fog of war, reveal flag oder so
    void drawWorld();
    void movePlayer(Coords validCoords);
    static bool positionIsValid(Coords coords);
    bool movePlayerIfPossible(char direction);
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
    void clearScreen();


private:
    int m_relicCount;
    enum cellType m_cells[10][10];
    std::string statusMessage;
};


#endif //CRAWLERKLASSEN_WORLD_H
