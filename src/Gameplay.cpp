//
// Created by dzondzi on 11.1.21..
//

#include <rg/Game.h>
#include <rg/Gameplay.h>
#include <iostream>



bool isAllowedMove(std::vector<std::vector<unsigned int>> matrica, int i, int j){

    if(matrica[i][j] == WALL_BOX)
        return false;
    return true;
}

void pm_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){

    int i = currPos.first;
    int j = currPos.second;

    bool moved = false;
    bool ind = false;

    if(key == GLFW_KEY_I  && action == GLFW_PRESS ){
        brPoena = 149;
    }

    if(key == GLFW_KEY_UP  && action == GLFW_PRESS ){
        if(isAllowedMove(outMatrix, i - 1, j)){
            if(outMatrix[i - 1][j] == FOOD_BOX)
                brPoena++;
            outMatrix[i][j] = NO_BOX;
            currPos = std::make_pair(i-1,j);
            pacmanRotation = 1;
            moved = true;
        }
        std:: cout << i << " " << j << std::endl;
    }
    else if(key == GLFW_KEY_DOWN  && action == GLFW_PRESS ){
        if(isAllowedMove(outMatrix, i + 1, j)){
            if(outMatrix[i + 1][j] == 2)
                brPoena++;
            outMatrix[i][j] = 7;
            currPos = std::make_pair(i+1,j);
            pacmanRotation = 3;
            moved = true;
        }
        std:: cout << i << " " << j << std::endl;

    }
    else if(key == GLFW_KEY_LEFT  && action == GLFW_PRESS){
        if(i == 9 && j == 0){
            currPos = std::make_pair(9,20);
            outMatrix[i][j] = NO_BOX;
            pacmanRotation = 2;
            ind = true;
        }
        if(!ind && isAllowedMove(outMatrix, i, j - 1)){
            if(outMatrix[i][j - 1] == 2)
                brPoena++;
            outMatrix[i][j] = 7;
            currPos = std::make_pair(i,j-1);
            pacmanRotation = 2;
            ind = true;
        }
        if(ind)
            moved = true;
        std:: cout << i << " " << j << std::endl;


    }
    else if(key == GLFW_KEY_RIGHT  && action == GLFW_PRESS){
        if(i == 9 && j == 20){
            currPos = std::make_pair(9,0);
            outMatrix[i][j] = 7;
            pacmanRotation = 0;
            ind = true;

        }
        if(ind == false && isAllowedMove(outMatrix, i, j + 1)){
            if(outMatrix[i][j + 1] == 2)
                brPoena++;
            outMatrix[i][j] = 7;
            currPos = std::make_pair(i,j+1);
            pacmanRotation = 0;
            ind = true;
        }
        if(ind)
            moved = true;
        std:: cout << i << " " << j << std::endl;

    }

    if(moved){
        isEndGame();
        if(endGame){
            newGame();
            return;
        }
        moveAllGhosts();
        isEndGame();
        if(endGame){
            newGame();
            return;
        }
    }

    if(key == GLFW_KEY_N && action == GLFW_PRESS){
        newGame();
    }

    if(key == GLFW_KEY_K && action == GLFW_PRESS){
        mainCamera.resetCamera(glm::vec3(10.0f, -10.0f, 22.0f));
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        glfwMaximizeWindow(window);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glfwRestoreWindow(window);
    }

}

void isEndGame(){
    for(int i = 0; i < 4; i++){
        if(currPos.first == ghostPos[i].first && currPos.second == ghostPos[i].second){
            endGame = true;
            break;
        }
    }
    if(brPoena == BROJ_POLJA)
        endGame = true;

}

void restartPositions(){
    currPos = std::make_pair(15,10);



    ghostPos[0] = std::make_pair(8, 10);
    ghostPos[1] = std::make_pair(9, 9);
    ghostPos[2] = std::make_pair(9, 10);
    ghostPos[3]= std::make_pair(9, 11);

}

void newGame(){
    restartMatrix();
    restartPositions();


    brPoena = 0;
    pacmanRotation = 0;
    lastDirGhost = {1,0,1,3};

    lastBox = NO_BOX;
    endGame = false;
}


int numMovingDir(std::pair<int,int> pos){
    int posi = pos.first;
    int posj = pos.second;
    int count = 0;
    if(outMatrix[posi - 1][posj] != WALL_BOX)
        count++;
    if(outMatrix[posi + 1][posj] != WALL_BOX)
        count++;
    if(outMatrix[posi][posj + 1] != WALL_BOX)
        count++;
    if(outMatrix[posi][posj - 1] != WALL_BOX)
        count++;

    return count;

}

void moveGhost(int num){

    int g_i = ghostPos[num].first;
    int g_j = ghostPos[num].second;


    if(numMovingDir(ghostPos[num]) == 1)
        lastDirGhost[num] = -1;

    while(1){
        int dir = rand() % 4;

        //gore
        if(dir == 1 && lastDirGhost[num] != 3){
            if(isAllowedMove(outMatrix, g_i - 1, g_j)){
                lastDirGhost[num] = 1;
                ghostPos[num] = std::make_pair(g_i-1,g_j);
                return;
            }
        }
        //levo
        if(dir == 2 && lastDirGhost[num] != 0){
            if(g_i == 9 && g_j == 0){
                lastDirGhost[num] = 2;
                ghostPos[num] = std::make_pair(9,20);
                return;
            }
            if(isAllowedMove(outMatrix, g_i, g_j - 1)){
                lastDirGhost[num] = 2;
                ghostPos[num] = std::make_pair(g_i,g_j-1);
                return;
            }

        }
        //dole
        if(dir == 3 && lastDirGhost[num] != 1){
            if(isAllowedMove(outMatrix, g_i + 1, g_j)){
                lastDirGhost[num] = 3;
                ghostPos[num] = std::make_pair(g_i+1,g_j);
                return;
            }

        }
        //desno
        if(dir == 0 && lastDirGhost[num] != 2){
            if(g_i == 9 && g_j == 20){
                lastDirGhost[num] = 0;
                ghostPos[num] = std::make_pair(9,0);
                return;
            }
            if(isAllowedMove(outMatrix, g_i, g_j + 1)){
                lastDirGhost[num] = 0;
                ghostPos[num] = std::make_pair(g_i,g_j+1);
                return;
            }
        }

    }
}

void moveAllGhosts(){
    for(int i = 0; i < 4; i++){
        moveGhost(i);
    }

}


