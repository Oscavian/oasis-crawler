//
// Created by Oskar on 13.03.2022.
//

#ifndef CRAWLERKLASSEN_GAMEUTILS_H
#define CRAWLERKLASSEN_GAMEUTILS_H

class Coords {
public:
    Coords() {
        this->x = 0;
        this->y = 0;
    };
    Coords(int x, int y){
        this->x = x;
        this->y = y;
    };
    bool coordsMatch(Coords c) const{
        if (this->x == c.x && this->y == c.y){
            return true;
        } else {
            return false;
        }
    }
    int x;
    int y;
};

enum cellType {
    normal, danger, heal, relic, unused
};

enum inputType {
    movement, dice, yesorno
};

enum itemType {
    hookshot, bombs, raft
};

enum dangerType {
    rock, ravine, lake
};
#endif //CRAWLERKLASSEN_GAMEUTILS_H
