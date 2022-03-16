//
// Created by oskar on 03.03.22.
//

#include "header/world.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#if defined(_WIN32)
#include "conio.h"
#include "assert.h"
#endif
#include "header/player.h"
#include "header/gameUtils.h"
#include "header/gameHandler.h"
#include <cassert>
#define RED "\033[31m"


World::World(unsigned int sideLength,unsigned int level) {
    srand(time(nullptr));
    m_relicCount = 0;
    if (sideLength > 50){
        m_worldSize = 50;
    } else {
        m_worldSize = sideLength;
    }
    m_currentLevel = level;
    statusMessage = "";
    player = new Player(5);

    //init needed cells with values
    for (int i = 0; i < m_worldSize; ++i) {
        for (int j = 0; j < m_worldSize; ++j) {
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

    //init remaining array
    for (unsigned int i = m_worldSize; i < 50; ++i) {
        for (unsigned int j = m_worldSize; j < 50; ++j) {
            m_cells[i][j] = unused;
        }
    }

    //print at least one relic
    if (m_relicCount == 0){
        m_cells[rand() % m_worldSize][rand() % m_worldSize] = relic;
    }

}

World::~World() {
    delete player;
}

char World::getInput(enum inputType inputType) {
    std::string input;
    char action = '\0';
    bool inputOkay = false;
    do {
#if defined(_WIN32)
        input = (char)getch();
        //getline(std::cin, input);
#elif defined(__linux__)
        getline(std::cin, input);
#endif
        if (input.length() != 1){
            continue;
        } else {
            action = input[0];
        }
        switch (inputType) {
            case movement:
                if (action == 'w' || action == 'a' || action == 's' || action == 'd'){
                    inputOkay = true;
                } else {
                    inputOkay = false;
                }
                break;
            case dice:
                if (action == 'r'){
                    inputOkay = true;
                }
                break;
            case yesorno:
                if (action == 'y' || action == 'n' || action == 'Y' || action == 'N'){
                    inputOkay = true;
                } else {
                    inputOkay = false;
                }
                break;
            default:
                std::cout << "\nWrong input!\n";
        }
    } while (!inputOkay);

    return action;
}


void World::drawWorld() {
    using namespace std;
    for (int i = 0; i < m_worldSize; ++i) {
        cout << "{{";
        for (int j = 0; j < m_worldSize; ++j) {
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
            cout << " ";
        }
        cout << "}}";
        if (i == 0){
            cout << "           Level " << to_string(m_currentLevel);
        } else if (i == 1){
            cout << "           HP: " << player->getCurrentHealth();
        } else if (i == 2) {
            cout << "           Remaining Relics: " << this->getRelicCount() - player->getFoundRelics();
        } else if (i == 3) {
            cout << "           Items: " << player->getItemList();
        }
        cout << "\n";
    }
    cout << endl << this->statusMessage;
}

int World::getRelicCount() const {
    return this->m_relicCount;
}

bool World::positionIsValid(Coords coords) const {
    if (coords.x > m_worldSize - 1 || coords.x < 0 || coords.y > m_worldSize - 1 || coords.y < 0){
        return false;
    } else {
        return true;
    }
}

void World::movePlayer(Coords validCoords) const {
    player->setPosition(validCoords);
}

bool World::movePlayerIfPossible(char direction) const {
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
    this->statusMessage = "";
    std::string message;
    switch (currentCell){
        case normal:
            message = "";
            break;
        case danger:
            encounterDanger();
            break;
        case relic:
            findRelic();
            giveRndItem();
            break;
        case heal:
            encounterFairyFountain();
            giveRndItem();
            break;
        case unused:
            assert("Error: Player on unused cell" && currentCell == unused);
            break;
        default:
            break;
    }

    //set encountered cell to normal
    this->m_cells[player->getX()][player->getY()] = normal;
}

void World::encounterFairyFountain() {
    player->restoreHP(1);
    this->statusMessage.append("You encountered a fairy fountain!\n You restored 1 HP!\n");
}

void World::findRelic() {
    player->findRelic();
    this->statusMessage.append("You found a relic!\n");
}

int World::rollDice(int maxEyes){
    int num = rand() % maxEyes;
    return num + 1;
}

void World::giveRndItem() {
    int coinflip = rand() % 2;
    int itemChance = rand() % 3;
    if (coinflip){
        if (itemChance == 0){
            if (!player->hasItem(bombs)){
                player->giveItem(bombs);
                this->statusMessage.append("Item obtained: Bombs\n");
            }
        } else if (itemChance == 1){
            if (!player->hasItem(hookshot)){
                player->giveItem(hookshot);
                this->statusMessage.append("Item obtained: Hookshot\n");
            }
        } else if(itemChance == 2){
            if (!player->hasItem(raft)){
                player->giveItem(raft);
                this->statusMessage.append("Item obtained: Raft\n");
            }
        }
    }
}

void World::redrawWorld(){
    clearScreen();
    this->drawWorld();
}

void World::clearScreen() {
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#endif
}

void World::encounterDanger() {
    int dangerType = rand() % 2;
    switch (dangerType) {
        case rock:
            encounterRock();
            break;
        case ravine:
            encounterRavine();
            break;
        case lake:
            encounterLake();
            break;
        default:
            break;
    }
}

void World::encounterRock() {
    int damage = 0;
    this->statusMessage.append("A big rock stands in your way!\n");
    if (player->hasItem(bombs)){
        this->statusMessage.append("Use bombs to destroy it? (y/n)\n");
        this->drawWorld();
        if (getInput(yesorno) == 'y'){
            this->statusMessage.append("Boom! The obstacle has been destroyed.\n");
            player->useItem(bombs);
            clearScreen();
            return;
        }
    }

    this->statusMessage.append("Your only chance is to climb over it.\nRoll a dice to determine how much HP this will cost you. (r)\n");
    this->redrawWorld();
    getInput(dice);
    damage = rollDice(3);
    player->takeDamage(damage);
    this->statusMessage.append("Oof, that was exhausting. You lost " + std::to_string(damage) + " HP.\n");
    clearScreen();
}

void World::encounterRavine() {
    int damage = 0;
    this->statusMessage.append("The path is blocked by a deep ravine.\n");
    if (player->hasItem(hookshot)){
        this->statusMessage.append("Use hookshot to get over safely? (y/n)\n");
        this->drawWorld();
        if (getInput(yesorno) == 'y'){
            player->useItem(hookshot);
            this->statusMessage.append("The hookshot brought you safely over the ravine.\n");
            clearScreen();
            return;
        }
    }

    this->statusMessage.append("You can only try to jump. If you fall, you're dead. Roll a dice (r).\n");
    this->redrawWorld();
    getInput(dice);
    damage = rollDice(10);
    if (damage == 10) {
        player->setCurrentHealth(0);
        this->statusMessage.append("Ahhhhhh, you fell!!\n");
        clearScreen();
    } else {
        this->statusMessage.append("Pheww, this was close. You lost 1 HP from the impact.");
        player->takeDamage(1);
        clearScreen();
    }
}

void World::encounterLake() {
    int damage = 0;
    this->statusMessage.append("To proceed you need to cross a huge lake.\n");
    if (player->hasItem(raft)){
        this->statusMessage.append("Use raft to cross lake safely? (y/n)\n");
        this->drawWorld();
        if (getInput(yesorno) == 'y'){
            player->useItem(raft);
            this->statusMessage.append("The raft brought you over the lake - then it broke. F.\n");
            clearScreen();
            return;
        }
    }

    this->statusMessage.append("Go swim! Roll a dice to determine how much HP it costs you (r).\n");
    this->redrawWorld();
    getInput(dice);
    damage = rollDice(4);
    player->takeDamage(damage);
    this->statusMessage.append("Oof, you made it. Did you bring a towel?\nYou lost " + std::to_string(damage) + " HP.\n");
    clearScreen();
}