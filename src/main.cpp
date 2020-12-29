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


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

ourCamera kamera(glm::vec3(11.0f, -11.0f, 20.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


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
    shader.setInt("texture2", 1);




    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        changingMatrixInput(window);
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
