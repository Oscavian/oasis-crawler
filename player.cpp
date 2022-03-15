//
// Created by oskar on 03.03.22.
//

#include "iostream"
#include "header/player.h"
#include "header/gameUtils.h"

Player::Player(int startHealth) {
    this->m_currentHealth = startHealth;
    this->m_enemiesMet = 0;
    this->m_relicsFound = 0;
    this->m_takenDmg = 0;
}

int Player::getCurrentHealth() const {
    return this->m_currentHealth;
}

int Player::getFoundRelics() const {
    return this->m_relicsFound;
}

void Player::setPosition(Coords coords) {
    this->m_coords = coords;
}

Coords Player::getPosition() const {
    return this->m_coords;
}

int Player::getY() const {
    return this->m_coords.y;
}

int Player::getX() const {
    return this->m_coords.x;
}

void Player::restoreHP(int hp) {
    this->m_currentHealth += hp;
    std::cout << "\nYou restored " << hp << "HP!\n";
}

void Player::takeDamage(int dmgAmount, bool isEnemy) {
    if (this->m_currentHealth - dmgAmount <= 0){
        this->m_currentHealth = 0;
        std::cout << "\nYou died!\n";

    } else {
        this->m_currentHealth -= dmgAmount;
        std::cout << "\nYou lost " << dmgAmount << "HP!\n";
    }
}

void Player::findRelic() {
    this->m_relicsFound++;
}

