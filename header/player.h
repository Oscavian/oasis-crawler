//
// Created by oskar on 03.03.22.
//

#ifndef CRAWLERKLASSEN_PLAYER_H
#define CRAWLERKLASSEN_PLAYER_H
#include "gameUtils.h"
#include <iostream>
class World;

class Player {
public:
    explicit Player(int startHealth);
    int getCurrentHealth() const;
    void takeDamage(int dmgAmount);
    void restoreHP(int hp);
    void setCurrentHealth(int health);
    Coords getPosition() const;
    int getX() const;
    int getY() const;
    int getFoundRelics() const;
    void findRelic();
    void setPosition(Coords coords);
    bool hasItem(enum itemType item) const;
    void giveItem(enum itemType item);
    void useItem(enum itemType item);
    std::string getItemList() const;

private:
    int m_currentHealth;
    int m_relicsFound;
    Coords m_coords;
    bool m_hasBombs;
    bool m_hasHookshot;
    bool m_hasRaft;
};

#endif //CRAWLERKLASSEN_PLAYER_H
