//
// Created by oskar on 03.03.22.
//

#ifndef CRAWLERKLASSEN_WORLD_H
#define CRAWLERKLASSEN_WORLD_H

#include "gameUtils.h"
#include "player.h"

class World {
    //header player, enemies, etc. to call movement methods
public:
    World(); //TODO: add initial field size as argument
    //TODO: Gefahrenfeld als Elternklasse und versch. Arten als Children
    virtual ~World();
    Player *player;
    //revealCells() TODO: fog of war, reveal flag oder so
    void drawWorld();
    void movePlayer(Coords validCoords);
    static bool positionIsValid(Coords coords);
    bool movePlayerIfPossible(char direction);
    int getRelicCount() const;
    void doCellAction();
    void encounterDanger();
    void encounterFairy();
    void findRelic();

private:
    int m_relicCount;
    enum cellType m_cells[10][10];
};


#endif //CRAWLERKLASSEN_WORLD_H
