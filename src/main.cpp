#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <learnopengl/shader.h>
#include <rg/model.h>

#include <rg/StartingGlfwInit.h>
#include <rg/StartingCallbackInit.h>
#include <rg/ourShader.h>
#include <rg/ourTexture.h>
#include <rg/MatrixChanges1.h>
#include <rg/Game.h>
#include <rg/LoadTextures.h>
#include <rg/ourCamera.h>
#include <learnopengl/shader.h>
#include <time.h>


#define BROJ_POLJA 150
#define WALL_BOX 1
#define FOOD_BOX 2
#define GHOST3 3
#define GHOST4 4
#define PACMAN 5
#define GHOST6 6
#define NO_BOX 7
#define GHOST8 8

void moveGhost();
void newGame();
void isEndGame();
std::pair<int,int> findPosition(std::vector<std::vector<unsigned int>> matrica, int n, int m, unsigned int findThis);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void pm_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
bool isAllowedMove(std::vector<std::vector<unsigned int>> matrica, int i, int j);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

ourCamera kamera(glm::vec3(11.0f, -11.0f, 20.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT /  2.0f;
bool firstMouse = true;
int brPoena = 0;

std::pair<int,int> currPos;
std::pair<int,int> ghostPos;
bool endGame = false;
int pacmanRotation;
int lastDirGhost = -1;
int lastBox = 7;


int main(){
    ourGlfwInit();
    ourCallbackInit();
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, pm_key_callback);

    srand(time(NULL));

    //ucitavanje matrice matrica
    initMatrix("resources/map/map01.txt");


    std::vector<ourTexture> teksture = loadTextures();


    ourShader shader("resources/shaders/cubeShader.vs", "resources/shaders/cubeShader.fs");
    ourShader shader2("resources/shaders/lightCube.vs", "resources/shaders/lightCube.fs");

    unsigned int VAO = initBuffers();
    unsigned int VAO2 = initEBOBuffers();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    currPos = findPosition(matrica,n,m, PACMAN);


    glm::vec3 pointLightPositions[] = {
            glm::vec3( 1.f,  0.f,  1.0f),
            glm::vec3( 19.f,  -20.f, 1.0f),
            glm::vec3( 19.f,  0.f, 1.0f),
            glm::vec3( 1.f,  -20.0f, 1.0f),
            glm::vec3(4.f,-8.f,1.f),
            glm::vec3(4.f,-10.f,1.f),
            glm::vec3(16.f,-8.f,1.f),
            glm::vec3(16.f,-10.f,1.f)

    };
    int numOfPointLights = 0;

    for(auto &i : pointLightPositions){
        numOfPointLights++;
    }

    pacmanRotation = 0;

    Shader modelShader("modelShader.vs", "modelShader.fs");
    Model nasModel("resources/objects/planet/planet.obj");

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        kamera.keyboardInput(window, deltaTime);

        //ako skupimo sve poene vracamo se na pocetak
        if(endGame){
            newGame();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                renderBox(i, j, matrica[j][i], VAO, shader, teksture, kamera, pointLightPositions, numOfPointLights
                          ,pacmanRotation);
            }
        }

        for(auto & pointLightPosition : pointLightPositions){
            renderLightCube(VAO2, shader2, kamera, pointLightPosition);
        }

        for(auto & pointLightPosition : pointLightPositions){
            renderModel(nasModel, modelShader, kamera, pointLightPosition);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    kamera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    kamera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}
std::pair<int,int> findPosition(std::vector<std::vector<unsigned int>> matrica, int n, int m,unsigned int findThis){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(matrica[i][j] == findThis)
                return std::make_pair(i,j);
        }
    }
    return std::make_pair(0,0);

}

bool isAllowedMove(std::vector<std::vector<unsigned int>> matrica, int i, int j){
    if(matrica[i][j] == FOOD_BOX || matrica[i][j] == NO_BOX || matrica[i][j] == GHOST3 || matrica[i][j] == PACMAN)
        return true;

    return false;
}

void pm_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){

    int i = currPos.first;
    int j = currPos.second;

    bool moved = false;
    bool ind = false;

    if(key == GLFW_KEY_UP  && action == GLFW_PRESS ){
        if(isAllowedMove(matrica,i-1,j)){
            if(matrica[i-1][j] == 2)
                brPoena++;
            matrica[i][j] = 7;
            matrica[i-1][j] = PACMAN;
            currPos = std::make_pair(i-1,j);
            pacmanRotation = 1;
            moved = true;
        }

    }
    else if(key == GLFW_KEY_DOWN  && action == GLFW_PRESS ){
        if(isAllowedMove(matrica,i+1,j)){
            if(matrica[i+1][j] == 2)
                brPoena++;
            matrica[i][j] = 7;
            matrica[i+1][j] = PACMAN;
            currPos = std::make_pair(i+1,j);
            pacmanRotation = 3;
            moved = true;
        }
    }
    else if(key == GLFW_KEY_LEFT  && action == GLFW_PRESS){
        if(i == 9 && j == 0){
            currPos = std::make_pair(9,20);
            matrica[9][20] = PACMAN;
            matrica[i][j] = 7;
            pacmanRotation = 2;
            ind = true;
        }
        if(!ind && isAllowedMove(matrica,i,j-1)){
            if(matrica[i][j-1] == 2)
                brPoena++;
            matrica[i][j] = 7;
            matrica[i][j-1] = PACMAN;
            currPos = std::make_pair(i,j-1);
            pacmanRotation = 2;
            ind = true;
        }
        if(ind)
            moved = true;

    }
    else if(key == GLFW_KEY_RIGHT  && action == GLFW_PRESS){
        if(i == 9 && j == 20){
            currPos = std::make_pair(9,0);
            matrica[9][0] = 5;
            matrica[i][j] = 7;
            pacmanRotation = 0;
            ind = true;

        }
        if(ind == false && isAllowedMove(matrica,i,j+1)){
            if(matrica[i][j+1] == 2)
                brPoena++;
            matrica[i][j] = 7;
            matrica[i][j+1] = 5;
            currPos = std::make_pair(i,j+1);
            pacmanRotation = 0;
            ind = true;
        }
        if(ind)
            moved = true;
    }

    if(moved){
        isEndGame();
        if(endGame){
            newGame();
            return;
        }
        moveGhost();
        isEndGame();
        if(endGame){
            newGame();
            return;
        }
    }

    if(key == GLFW_KEY_N && action == GLFW_PRESS){
        newGame();
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        glfwMaximizeWindow(window);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glfwRestoreWindow(window);
    }

}

void isEndGame(){
    if(currPos.first == ghostPos.first && currPos.second == ghostPos.second)
        endGame = true;
    if(brPoena == BROJ_POLJA)
        endGame = true;

}
void newGame(){
    restartMatrix();
    currPos = findPosition(matrica, n, m, PACMAN);
    brPoena = 0;
    pacmanRotation = 0;
    lastDirGhost = -1;
    lastBox = NO_BOX;
    endGame = false;
}

void moveGhost(){
    ghostPos = findPosition(matrica,n,m,GHOST3);
    int g_i = ghostPos.first;
    int g_j = ghostPos.second;
    std::cout << g_i << "  " << g_j << std::endl;

    //
    while(1){
        int dir = rand() % 4;
        //gore
        if(dir == 1 && lastDirGhost != 3){
            if(isAllowedMove(matrica, g_i-1,g_j)){
                matrica[g_i][g_j] = lastBox;
                lastBox = matrica[g_i-1][g_j];
                matrica[g_i-1][g_j] = GHOST3;
                lastDirGhost = 1;
                ghostPos = std::make_pair(g_i-1,g_j);
                return;
            }
        }
        //levo
        if(dir == 2 && lastDirGhost != 0){
            if(g_i == 9 && g_j == 0){
                matrica[g_i][g_j] = lastBox;
                lastBox = matrica[9][20];
                matrica[9][20] = GHOST3;
                lastDirGhost = 2;
                ghostPos = std::make_pair(9,20);
                return;
            }
            if(isAllowedMove(matrica, g_i,g_j-1)){
                matrica[g_i][g_j] = lastBox;
                lastBox = matrica[g_i][g_j-1];
                matrica[g_i][g_j-1] = GHOST3;
                lastDirGhost = 2;
                ghostPos = std::make_pair(g_i,g_j-1);
                return;

            }

        }
        //dole
        if(dir == 3 && lastDirGhost != 1){
            if(isAllowedMove(matrica, g_i+1,g_j)){
                matrica[g_i][g_j] = lastBox;
                lastBox = matrica[g_i+1][g_j];
                matrica[g_i+1][g_j] = GHOST3;
                lastDirGhost = 3;
                ghostPos = std::make_pair(g_i+1,g_j);
                return;

            }

        }
        //desno
        if(dir == 0 && lastDirGhost != 2){
            if(g_i == 9 && g_j == 20){
                matrica[g_i][g_j] = lastBox;
                lastBox = matrica[9][0];
                matrica[9][0] = GHOST3;
                lastDirGhost = 0;
                ghostPos = std::make_pair(9,0);
                return;
            }
            if(isAllowedMove(matrica, g_i,g_j+1)){
                matrica[g_i][g_j] = lastBox;
                lastBox = matrica[g_i][g_j+1];
                matrica[g_i][g_j+1] = GHOST3;
                lastDirGhost = 0;
                ghostPos = std::make_pair(g_i,g_j+1);
                return;

            }

        }

    }
}