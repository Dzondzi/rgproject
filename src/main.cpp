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
#include <rg/InitBuffers.h>
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

void moveAllGhosts();
void moveGhost(int num);
void newGame();
void isEndGame();
void restartPositions();
int numMovingDir(std::pair<int,int> pos);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void pm_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
bool isAllowedMove(std::vector<std::vector<unsigned int>> matrica, int i, int j);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

ourCamera mainCamera(glm::vec3(10.0f, -10.0f, 22.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT /  2.0f;
bool firstMouse = true;
int brPoena = 0;

std::pair<int,int> currPos;

std::vector<std::pair<int,int>> ghostPos(4);

bool endGame = false;
int pacmanRotation;

std::vector<int> lastDirGhost = {1, 0, 1, 3};
int lastBox = 7;


int main(){
    ourGlfwInit();
    ourCallbackInit();
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, pm_key_callback);

    srand(time(NULL));
    //ucitavanje matrice outMatrix
    initMatrix("resources/map/map01.txt");


    std::vector<ourTexture> textures = loadTextures();
    std::vector<ourTexture> ghostTextures = loadGhostTextures();

    stbi_set_flip_vertically_on_load(false);
    unsigned int skyboxTexture = loadCubemap();
    stbi_set_flip_vertically_on_load(true);


    ourShader mapShader("resources/shaders/cubeShader.vs",
                        "resources/shaders/cubeShader.fs");
    ourShader ghostShader("resources/shaders/pacmanShader.vs",
                          "resources/shaders/pacmanShader.fs");
    ourShader pacmanShader("resources/shaders/pacmanShader.vs",
                           "resources/shaders/pacmanShader.fs");
    ourShader cubeShader("resources/shaders/lightcubeShader.vs",
                         "resources/shaders/lightcubeShader.fs");
    ourShader skyboxShader("resources/shaders/skyboxShader.vs",
                           "resources/shaders/skyboxShader.fs");

    unsigned int VAO = initBuffers();
    unsigned int VAO2 = initEBOBuffers();
    unsigned int VAOfig = initFIGBuffers();
    unsigned int VAOskybox = initSKYBOXBuffers();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    restartPositions();


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
    ourTexture pacmanTexture = textures[PACMAN];
    pacmanTexture.setWrappingST(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);


    Shader modelShader("modelShader.vs", "modelShader.fs");
    Model outModel("resources/objects/planet/planet.obj");



    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        mainCamera.keyboardInput(window, deltaTime);

        //ako skupimo sve poene vracamo se na pocetak
        if(endGame){
            newGame();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderSkybox(skyboxShader, VAOskybox, mainCamera, skyboxTexture);


        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                renderMap(i, j, outMatrix[j][i], VAO, mapShader, textures, mainCamera, pointLightPositions, numOfPointLights);
            }
        }

        renderPacman(currPos, VAOfig, pacmanShader, pacmanTexture, mainCamera, pointLightPositions, numOfPointLights, pacmanRotation);

        for(int i = 0; i < 4; i++){
            renderGhost(i, ghostShader, VAOfig, ghostPos, mainCamera, pointLightPositions, numOfPointLights, ghostTextures);
        }

        for(auto & pointLightPosition : pointLightPositions){
            renderLightCube(VAO2, cubeShader, mainCamera, pointLightPosition);
        }

        for(auto & pointLightPosition : pointLightPositions){
            renderModel(outModel, modelShader, mainCamera, pointLightPosition);
        }

     //   renderSkybox(skyboxShader, VAOskybox, mainCamera, skyboxTexture);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glDeleteVertexArrays(1,&VAO);
    glDeleteVertexArrays(1,&VAO2);
    glDeleteVertexArrays(1,&VAOfig);

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

    mainCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    mainCamera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

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

    if(key == GLFW_KEY_UP  && action == GLFW_PRESS ){
        if(isAllowedMove(outMatrix, i - 1, j)){
            if(outMatrix[i - 1][j] == 2)
                brPoena++;
            outMatrix[i][j] = 7;
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
            outMatrix[i][j] = 7;
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

    std::pair<int,int> par0 = std::make_pair(8, 10);
    std::pair<int,int> par1 = std::make_pair(9, 9);
    std::pair<int,int> par2 = std::make_pair(9, 10);
    std::pair<int,int> par3 = std::make_pair(9, 11);

    ghostPos[0] = par0;
    ghostPos[1] = par1;
    ghostPos[2] = par2;
    ghostPos[3] = par3;

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

void moveAllGhosts(){
    for(int i = 0; i < 4; i++){
        moveGhost(i);
    }

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