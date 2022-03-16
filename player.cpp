//
// Created by oskar on 03.03.22.
//

#include "iostream"
#include "header/player.h"
#include "header/gameUtils.h"

Player::Player(int startHealth) {
    this->m_currentHealth = startHealth;
    this->m_relicsFound = 0;
    this->m_hasRaft = false;
    this->m_hasBombs = false;
    this->m_hasHookshot = false;
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
}

void Player::takeDamage(int dmgAmount) {
    if (this->m_currentHealth - dmgAmount <= 0){
        this->m_currentHealth = 0;

    } else {
        this->m_currentHealth -= dmgAmount;
    }
}

void Player::findRelic() {
    this->m_relicsFound++;
}

bool Player::hasItem(enum itemType item) const {
    switch (item) {
        case bombs:
            if (m_hasBombs){
                return true;
            }
            break;
        case hookshot:
            if (m_hasHookshot){
                return true;
            }
            break;
        case raft:
            if (m_hasRaft){
                return true;
            }
            break;
        default:
            return false;
    }

    return false;
}

void Player::giveItem(enum itemType item){
    switch (item) {
        case bombs:
            m_hasBombs = true;
            break;
        case hookshot:
            m_hasHookshot = true;
            break;
        case raft:
            m_hasRaft = true;
            break;
    }
}

std::string Player::getItemList() const {
    std::string list;
    if (hasItem(bombs)){
        list.append("Bombs, ");
    }
    if (hasItem(raft)) {
        list.append("Raft, ");
    }
    if (hasItem(hookshot)) {
        list.append("Hookshot, ");
    }
    return list;
}

void Player::useItem(enum itemType item) {
    switch (item) {
        case bombs:
            m_hasBombs = false;
            break;
        case hookshot:
            m_hasHookshot = false;
            break;
        case raft:
            m_hasRaft = false;
            break;
        default:
            break;
    }
}

void Player::setCurrentHealth(int health) {
    if (health >= 0){
        m_currentHealth = health;
    }
}
