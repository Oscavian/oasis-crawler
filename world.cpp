//
// Created by oskar on 03.03.22.
//

#include "header/world.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "header/player.h"
#include "header/gameUtils.h"
#define RED "\033[31m"


World::World() {
    m_relicCount = 0;
    srand(time(nullptr));

    player = new Player(5);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int randNum = rand() % 10;

            if (randNum < 5) {
                m_cells[i][j] = normal;
            } else if (randNum < 8) {
                m_cells[i][j] = danger;
            } else if (randNum < 9) {
                m_cells[i][j] = heal;
            } else if (randNum < 10) {
                m_cells[i][j] = relic;
                m_relicCount++;
            }
        }
    }
    
    //print at least one relic
    if (m_relicCount == 0){
        m_cells[rand() % 10][rand() % 10] = relic;
    }

}

void World::drawWorld() {
    using namespace std;
    for (int i = 0; i < 10; ++i) {
        cout << "{{";
        for (int j = 0; j < 10; ++j) {
            if (player->getPosition().coordsMatch(Coords(i, j))){
                cout << 'H';
            }
            else if (this->m_cells[i][j] == normal){
                cout << '~';
            } else if (this->m_cells[i][j] == danger){
                cout << '!';
            } else if (this->m_cells[i][j] == heal) {
                cout << '$';
            } else if (this->m_cells[i][j] == relic) {
                cout << '*';
            }
        }
        cout << "}}";
        cout << endl;
    }
}

World::~World() {
    delete player;
}

int World::getRelicCount() const {
    return this->m_relicCount;
}

bool World::positionIsValid(Coords coords) {
    if (coords.x > 9 || coords.x < 0 || coords.y > 9 || coords.y < 0){
        return false;
    } else {
        return true;
    }
}

void World::movePlayer(Coords validCoords) {
    player->setPosition(validCoords);
}

bool World::movePlayerIfPossible(char direction) {
    if (!positionIsValid(player->getPosition())){
        return false;
    }
    Coords requestedCoords;
    switch (direction) {
        case 'w':
            requestedCoords = Coords(player->getX() - 1, player->getY());
            break;
        case 'a':
            requestedCoords = Coords(player->getX(), player->getY() - 1);
            break;
        case 's':
            requestedCoords = Coords(player->getX() + 1, player->getY());
            break;
        case 'd':
            requestedCoords = Coords(player->getX(), player->getY() + 1);
            break;
        default:
            return false;
    }

    if (positionIsValid(requestedCoords)){
        movePlayer(requestedCoords);
        return true;
    } else {
        return false;
    }
}

void World::doCellAction() {
    enum cellType currentCell = this->m_cells[player->getX()][player->getY()];

    switch (currentCell){
        case normal:
            break;
        case danger:
            encounterDanger();
            break;
        case relic:
            findRelic();
            break;
        case heal:
            encounterFairy();
            break;
        default:
            break;
    }

    //set encountered cell to normal
    this->m_cells[player->getX()][player->getY()] = normal;
}

void World::encounterFairy() {
    player->restoreHP(1);
    std::cout << "\nYou encountered a fairy!\n";
}

void World::findRelic() {
    player->findRelic();
    std::cout << "\nYou found a relic!\n" << this->getRelicCount() << " relics to go!\n";
}

void World::encounterDanger() {
    int damageChance = rand() % 60;
    std::cout << "\nYou encountered a danger zone.\n";
    if (damageChance < 10) {
        player->takeDamage(1, false);
    } else {
        std::cout << "But you were lucky\n";
    }
}
