#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <learnopengl/shader.h>
#include <rg/model.h>

#include <rg/StartingGlfwInit.h>
#include <rg/ourShader.h>
#include <rg/ourTexture.h>
#include <rg/MatrixChanges1.h>
#include <rg/Game.h>
#include <rg/InitBuffers.h>
#include <rg/LoadTextures.h>
#include <rg/ourCamera.h>
#include <learnopengl/shader.h>
#include <time.h>
#include <rg/Gameplay.h>


#define BROJ_POLJA 150
#define WALL_BOX 1
#define FOOD_BOX 2
#define GHOST3 3
#define GHOST4 4
#define PACMAN 5
#define GHOST6 6
#define NO_BOX 7
#define GHOST8 8


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

ourCamera mainCamera(glm::vec3(10.0f, -10.0f, 27.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT /  2.0f;
bool firstMouse = true;

int randNum;
int brPoena = 0;

std::pair<int,int> pacmanPos;

std::vector<std::pair<int,int>> ghostPos(4);

bool endGame = false;
int pacmanRotation;

std::vector<int> lastDirGhost = {1, 0, 1, 3};
int lastBox = 7;


int main(){
    ourGlfwInit();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetKeyCallback(window, movingKeyCallback);


    glEnable(GL_DEPTH_TEST);
    srand(time(NULL));
    //ucitavanje matrice outMatrix
    initMatrix("resources/map/map01.txt");


    std::vector<ourTexture> textures = loadTextures();
    std::vector<ourTexture> ghostTextures = loadGhostTextures();
    unsigned int skyboxTexture = loadCubemap();

    unsigned int VAOMapCubes = initBuffers();
    unsigned int VAOLightCube = initEBOBuffers();
    unsigned int VAOfig = initFIGBuffers();
    unsigned int VAOskybox = initSKYBOXBuffers();

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
            glm::vec3(16.f,-10.f,1.f),
    };

    int numOfPointLights = 0;
    for(auto &i : pointLightPositions){
        numOfPointLights++;
    }

    pacmanRotation = 0;
    ourTexture pacmanTexture = textures[PACMAN];
    pacmanTexture.setWrappingST(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);


    Shader modelShader("modelShader.vs", "modelShader.fs");
    Model ourModel("resources/objects/planet/planet.obj");


    while (!glfwWindowShouldClose(window))
    {


        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(window);
        mainCamera.keyboardInput(window, deltaTime);

        if(endGame)
            newGame();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        randNum = rand() % 15;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                renderMap(i, j, outMatrix[j][i], VAOMapCubes, mapShader, textures, mainCamera, pointLightPositions, numOfPointLights);
            }
        }

        renderPacman(pacmanPos, VAOfig, pacmanShader, pacmanTexture, mainCamera, pointLightPositions, numOfPointLights, pacmanRotation);

        for(int i = 0; i < 4; i++){
            renderGhost(i, ghostShader, VAOfig, ghostPos, mainCamera, pointLightPositions, numOfPointLights, ghostTextures);
        }

        for(auto & pointLightPosition : pointLightPositions){
            renderLightCube(VAOLightCube, cubeShader, mainCamera, pointLightPosition);
        }


        for(auto & pointLightPosition : pointLightPositions){
            renderModel(ourModel, modelShader, mainCamera, pointLightPosition);
        }


        renderSkybox(skyboxShader, VAOskybox, mainCamera, skyboxTexture);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1,&VAOMapCubes);
    glDeleteVertexArrays(1,&VAOLightCube);
    glDeleteVertexArrays(1,&VAOfig);
    glDeleteVertexArrays(1,&VAOskybox);

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
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


