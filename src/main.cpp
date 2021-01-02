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

std::pair<int,int> findPosition(std::vector<std::vector<unsigned int>> matrica, int n, int m);
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

std::pair<int,int> currPos;

int main(){
    ourGlfwInit();
    ourCallbackInit();
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //ucitavanje matrice matrica
    initMatrix("resources/map/map01.txt");


    std::vector<Texture> teksture = initTextures();


    Shader shader("resources/shaders/cubeShader.vs", "resources/shaders/cubeShader.fs");
    unsigned int VAO = initBuffers();
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shader.setInt("texture1", 0);

    currPos = findPosition(matrica,n,m);

    glfwSetKeyCallback(window, pm_key_callback);


    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
       // changingMatrixInput(window, currPos);
        kamera.keyboardInput(window, deltaTime);

        // render
        // ------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                renderBox(i, j, matrica[j][i], VAO, shader, teksture, kamera);
            }
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
std::pair<int,int> findPosition(std::vector<std::vector<unsigned int>> matrica, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(matrica[i][j] == 5)
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




    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ){
        if(isAllowedMove(matrica,i-1,j)){
            matrica[i][j] = 7;
            matrica[i-1][j] = 5;
            currPos = std::make_pair(i-1,j);
        }
    }
    else if(key == GLFW_KEY_DOWN  && action == GLFW_PRESS ){
        if(isAllowedMove(matrica,i+1,j)){
            matrica[i][j] = 7;
            matrica[i+1][j] = 5;
            currPos = std::make_pair(i+1,j);
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ){
        if(isAllowedMove(matrica,i,j-1)){
            matrica[i][j] = 7;
            matrica[i][j-1] = 5;
            currPos = std::make_pair(i,j-1);
        }
        if(i == 9 && j == 0){
            currPos = std::make_pair(9,20);
            matrica[9][20] = 5;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ){
        if(isAllowedMove(matrica,i,j+1)){
            matrica[i][j] = 7;
            matrica[i][j+1] = 5;
            currPos = std::make_pair(i,j+1);
        }
        if(i == 9 && j == 20){
            currPos = std::make_pair(9,0);
            matrica[9][0] = 5;
        }
    }


    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        glfwMaximizeWindow(window);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glfwRestoreWindow(window);
    }
}