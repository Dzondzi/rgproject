#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <rg/StartingGlfwInit.h>
#include <rg/StartingCallbackInit.h>
#include <rg/Shader.h>
#include <rg/Texture2D.h>
#include <rg/MatrixChanges1.h>
#include <rg/LoadMatrix.h>
#include <rg/Game.h>
#include <rg/Camera.h>
#include <rg/LoadTextures.h>


int main(){
    ourGlfwInit();
    ourCallbackInit();

    glEnable(GL_DEPTH_TEST);
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
        processInput(window);
        changingMatrixInput(window);

        // render
        // ------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                renderBox(i, j, matrica[j][i], VAO, shader, teksture);
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

