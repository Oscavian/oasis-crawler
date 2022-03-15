#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define SIDE_LENGTH 5

using namespace std;

enum cellType {
    normal, danger, heal, relic
};

typedef struct cell {
    enum cellType type;
} cell;

typedef struct hero {
    int relicsFound;
    int takenDmg;
    int healthRestored;
    int enemiesMet;
    int currentHealth;
    int posX;
    int posY;

} hero;

typedef struct field {
    cell cells[SIDE_LENGTH][SIDE_LENGTH];
    int relicCount;
} field;

void printField (hero Hero, hero Enemy1, hero Enemy2) {
    for (int i = 0; i<SIDE_LENGTH; i++) {
        for (int j = 0; j<SIDE_LENGTH; j++) {
            if (Hero.posX == i && Hero.posY == j) {
                cout << 'H';
            } else if (Enemy1.posX == i && Enemy1.posY == j) {
                cout << 'G';
            } else if (Enemy2.posX == i && Enemy2.posY == j) {
                cout << 'Z';
            } else {
                cout << '*';
            }
        }
        cout << endl;
    }
}

bool moveInDir(char direction, hero* Hero) {

    //assert("U dead man, u cant move" && Hero->currentHealth > 0);

    switch (direction) {
        case 'w': {
            if(Hero->posX >= SIDE_LENGTH - (SIDE_LENGTH - 1)) {
                Hero->posX--;
                assert("Field boundaries: " && Hero->posX >= 0);
                return true;
            } else {
                return false;
            }
        }
        case 's': {
            if(Hero->posX <= SIDE_LENGTH - 2) {
                Hero->posX++;
                assert("Field boundaries: " && Hero->posX < SIDE_LENGTH);
                return true;
            } else {
                return false;
            }
        }
        case 'a': {
            if(Hero->posY >= SIDE_LENGTH - (SIDE_LENGTH - 1)) {
                Hero->posY--;
                assert("Field boundaries: " && Hero->posY >= 0);
                return true;
            } else {
                return false;
            }
        }
        case 'd': {
            if(Hero->posY <= SIDE_LENGTH - 2) {
                Hero->posY++;
                assert("Field boundaries: " && Hero->posY < SIDE_LENGTH);
                return true;
            } else {
                return false;
            }
        }
        case 'x':
            return true;
        default:
            cout << "wrong input\n";
            return false;
    }
}

field initField(){
    field Field;

    while ((Field.relicCount) == 0) { //generate field until there's at least one relic
        srand (time(NULL));
        for (int i = 0; i<SIDE_LENGTH; i++) {
            for (int j = 0; j<SIDE_LENGTH; j++) {
                int randNum = rand() % 100;

                assert("Randnum: " && randNum < 100 && randNum >= 0);

                if (randNum < 40) {
                    Field.cells[i][j].type = normal;
                } else if (randNum < 80) {
                    Field.cells[i][j].type = danger;
                } else if (randNum < 90) {
                    Field.cells[i][j].type  = heal;
                } else if (randNum < 100) {
                    Field.cells[i][j].type  = relic;
                    Field.relicCount++;
                }
            }
        }
    }

    return Field;
}

hero initHero(int hp){
    hero Hero;
    Hero.currentHealth = hp;
    Hero.relicsFound = 0;
    Hero.enemiesMet = 0;
    Hero.healthRestored = 0;
    Hero.takenDmg = 0;
    Hero.posX = 0;
    Hero.posY = 0;

    return Hero;
}

int main() {

    //init field
    field Field = initField();

    srand (time(NULL));
    assert("Number of Relics: " && Field.relicCount > 0);


    //init Hero
    hero Link = initHero(5);

    //init enemies
    //Functions for init was buggy because of rand(), for whatever reason
    hero Ganon;
    hero Zanto;
    Ganon.posX = rand() % SIDE_LENGTH;
    Ganon.posY = rand() % SIDE_LENGTH;

    Zanto.posX = rand() % SIDE_LENGTH;
    Zanto.posY = rand() % SIDE_LENGTH;


    cout << "Welcome to the Game!\n Goal: Help Link find all the relics and don't die.\n You (H) start with 5 HP.\n Don't get caught by Ganon or Zanto, they're after you!\n";

    printField(Link, Ganon, Zanto);

    string input;
    char direction = '\0';


    do {

        cout << "walk to (w,a,s,d): ";
        getline(cin, input);

        if (input.length() != 1) {
            cout << "only single characters allowed.\n";
            continue;
        } else {
            direction = input[0];
        }

        //chance the enemies walk in either x or y direction is 50% each
        bool enemyMvX = rand() % 2;
        bool enemyMvY = rand() % 2;

        //move
        if (moveInDir(direction, &Link) == true) {
            //enemies move too
            if (enemyMvX) {

                //Ganon & Zanto follow Link
                if (Ganon.posX > Link.posX) {
                    moveInDir('w', &Ganon);
                } else if (Ganon.posX < Link.posX) {
                    moveInDir('s', &Ganon);
                }

                if (Zanto.posX > Link.posX) {
                    moveInDir('w', &Zanto);
                } else {
                    moveInDir('s', &Zanto);
                }
            }
            if (enemyMvY) {

                if (Ganon.posY > Link.posY) {
                    moveInDir('a', &Ganon);
                } else if (Ganon.posY < Link.posY) {
                    moveInDir('d', &Ganon);
                }

                if (Zanto.posY > Link.posY) {
                    moveInDir('a', &Zanto);
                } else {
                    moveInDir('d', &Zanto);
                }
            }

            printField(Link, Ganon, Zanto);
        } else {
            cout << "what's your plan?\n";
            continue;
        }

        //check current cell
        if (Field.cells[Link.posX][Link.posY].type == danger) {
            int damageChance = rand() % 60;
            if (damageChance < 10) {
                Link.currentHealth--;
                Link.takenDmg++;
                cout << "Ouch. You lost 1 HP.\n";
            } else {
                cout << "You escaped the danger zone.\n";
            }
        } else if (Field.cells[Link.posX][Link.posY].type == heal) {
            cout << "You restored 1 HP!\n";
            Link.healthRestored++;
            Link.currentHealth++;
        } else if (Field.cells[Link.posX][Link.posY].type == relic) {
            cout << "You found a relic!\n";
            Link.relicsFound++;
        }

        // Hero and Enemy meet
        if ((Link.posX == Ganon.posX && Link.posY == Ganon.posY) || (Link.posX == Zanto.posX && Link.posY == Zanto.posY)) {
            Link.currentHealth -= 2;
            Link.takenDmg += 2;
            Link.enemiesMet++;
            cout << "Ouch, an enemy hit you. You lost 2 HP\n";
        }

        //set cell to normal
        Field.cells[Link.posX][Link.posY].type = normal;

    } while (Link.currentHealth > 0 && Link.relicsFound < Field.relicCount && direction != 'x');

    //Game Ended
    if (Link.currentHealth <= 0) {
        cout << "You died, F.\n";
    } else if (direction == 'x') {
        cout << "Game aborted.\n";
    } else {
        cout << "Congratulations, you found all relics!\n";
    }

    cout << "-------------" << endl << "Relics found: " << Link.relicsFound << endl << "Damage Taken: " << Link.takenDmg << endl << "Damage restored: " << Link.healthRestored << endl << "Enemies faced: " << Link.enemiesMet;

    return 0;
}