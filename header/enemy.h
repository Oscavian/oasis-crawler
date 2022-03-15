//
// Created by oskar on 04.03.22.
//

#ifndef CRAWLERKLASSEN_ENEMY_H
#define CRAWLERKLASSEN_ENEMY_H

enum enemyTypes {
    Ganon, Zanto, Bokblin
};

class Enemy {
public:
    Enemy(enum enemyTypes enemyType);
private:
    enum enemyTypes m_enemyType;
};


#endif //CRAWLERKLASSEN_ENEMY_H
