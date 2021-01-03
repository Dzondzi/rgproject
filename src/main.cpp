#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <rg/StartingGlfwInit.h>
#include <rg/StartingCallbackInit.h>
#include <rg/Shader.h>
#include <rg/Texture2D.h>
#include <rg/MatrixChanges1.h>
#include <rg/Game.h>
#include <rg/LoadTextures.h>
#include <rg/ourCamera.h>
#include <time.h>

#define BROJ_POLJA 150
#define PACMAN 5
#define GHOST3 3

void moveGhost();
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


    std::vector<Texture> teksture = loadTextures();


    Shader shader("resources/shaders/cubeShader.vs", "resources/shaders/cubeShader.fs");
    Shader shader2("resources/shaders/lightCube.vs", "resources/shaders/lightCube.fs");

    unsigned int VAO = initBuffers();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    currPos = findPosition(matrica,n,m, PACMAN);


    glm::vec3 pointLightPositions[] = {
            glm::vec3( 1.f,  0.f,  1.0f),
            glm::vec3( 19.f,  -20.f, 1.0f),
            glm::vec3( 19.f,  0.f, 1.0f),
            glm::vec3( 1.f,  -20.0f, 1.0f)

    };

    pacmanRotation = 0;

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
        if(brPoena == BROJ_POLJA){
            restartMatrix();
            currPos = findPosition(matrica,n, m, PACMAN);
            brPoena = 0;
            pacmanRotation = 0;
            lastDirGhost = -1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                renderBox(i, j, matrica[j][i], VAO, shader, teksture, kamera, pointLightPositions, pacmanRotation);
            }
        }

        for(auto & pointLightPosition : pointLightPositions){
            renderLightCube(VAO, shader2, kamera, pointLightPosition);
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
    if(matrica[i][j] == 2 || matrica[i][j] == 0 || matrica[i][j] == 7)
        return true;
    return false;
}

void pm_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){

    int i = currPos.first;
    int j = currPos.second;

    bool moved = false;

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

            return;
        }
        if(isAllowedMove(matrica,i,j-1)){
            if(matrica[i][j-1] == 2)
                brPoena++;
            matrica[i][j] = 7;
            matrica[i][j-1] = PACMAN;
            currPos = std::make_pair(i,j-1);
            pacmanRotation = 2;
            moved = true;
        }

    }
    else if(key == GLFW_KEY_RIGHT  && action == GLFW_PRESS){
        if(i == 9 && j == 20){
            currPos = std::make_pair(9,0);
            matrica[9][0] = 5;
            matrica[i][j] = 7;
            pacmanRotation = 0;
            return;
        }
        if(isAllowedMove(matrica,i,j+1)){
            if(matrica[i][j+1] == 2)
                brPoena++;
            matrica[i][j] = 7;
            matrica[i][j+1] = 5;
            currPos = std::make_pair(i,j+1);
            pacmanRotation = 0;
            moved = true;

        }
    }

    if(moved){
        moveGhost();
    }

    if(key == GLFW_KEY_N && action == GLFW_PRESS){
        restartMatrix();
        currPos = findPosition(matrica, n, m, PACMAN);
        brPoena = 0;
        pacmanRotation = 0;
        lastDirGhost = -1;
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        glfwMaximizeWindow(window);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glfwRestoreWindow(window);
    }
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