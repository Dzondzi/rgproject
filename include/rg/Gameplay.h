//
// Created by dzondzi on 11.1.21..
//

#ifndef MAIN_CPP_GAMEPLAY_H
#define MAIN_CPP_GAMEPLAY_H

#include <iostream>
#include <vector>
#include <rg/LoadMatrix.h>

#define BROJ_POLJA 150
#define WALL_BOX 1
#define FOOD_BOX 2
#define GHOST3 3
#define GHOST4 4
#define PACMAN 5
#define GHOST6 6
#define NO_BOX 7
#define GHOST8 8


extern std::pair<int,int> pacmanPos;
extern std::vector<std::pair<int,int>> ghostPos;
extern std::vector<int> lastDirGhost;

extern ourCamera mainCamera;

extern bool endGame;
extern int brPoena;
extern int pacmanRotation;
extern int lastBox;

extern std::vector<std::vector<unsigned int>> outMatrix;

void moveAllGhosts();
void moveGhost(int num);
void newGame();
void isEndGame();
void restartPositions();
int numMovingDir(std::pair<int,int> pos);
bool isAllowedMove(std::vector<std::vector<unsigned int>> matrica, int i, int j);


void movingKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);


#endif //MAIN_CPP_GAMEPLAY_H

