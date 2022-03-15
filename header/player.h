//
// Created by oskar on 03.03.22.
//

#ifndef CRAWLERKLASSEN_PLAYER_H
#define CRAWLERKLASSEN_PLAYER_H
#include "gameUtils.h"

class World;

class Player {
public:
    Player(int startHealth);
    int getCurrentHealth() const;
    void takeDamage(int dmgAmount, bool isEnemy);
    void restoreHP(int hp);
    void setCurrentHealth(int health);
    Coords getPosition() const;
    int getX() const;
    int getY() const;
    int getFoundRelics() const;
    void findRelic();
    void setPosition(Coords coords);

private:
    int m_currentHealth;
    int m_takenDmg;
    int m_relicsFound;
    int m_enemiesMet;
    Coords m_coords;
};


#endif //CRAWLERKLASSEN_PLAYER_H
