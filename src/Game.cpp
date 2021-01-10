//
// Created by dzondzi on 28.12.20..
//

#include <rg/Game.h>
#include <rg/StartingGlfwInit.h>
#include <string>

#define WALL_BOX 1
#define FOOD_BOX 2
#define GHOST3 3
#define GHOST4 4
#define PACMAN 5
#define GHOST6 6
#define NO_BOX 7
#define GHOST8 8
#define FLOOR_BOX 9
#define FLOOR_SPECULAR 10
#define NO_SPECULAR 9
#define Z_NEAR 0.1f
#define Z_FAR 500.f

extern int brPoena;
extern int randNum;


void renderGhost(int i, ourShader shader,unsigned int VAO, std::vector<std::pair<int,int>> ghostPos, ourCamera camera,
                 glm::vec3 pointLightPositions[], int numOfPointLights, std::vector<ourTexture> ghostTextures){

    float koef = (float)(150-brPoena) * (150-brPoena) / (22500);
    float koef2 = (float)(150-brPoena) / 150;

    if(brPoena > 70){
        if(randNum == 1){
            koef = 1.f;
            koef2 = 1.f;
        }
    }


    glBindVertexArray(VAO);
    shader.use();

    shader.setVec3("viewPos", camera.Position);
    shader.setFloat("material.shininess", 16.0f);

    glm::vec3 ambient = glm::vec3(0.05f * koef2 , 0.05f* koef2 , 0.05f * koef2 );
    glm::vec3 diffuse = glm::vec3(0.4f * koef2 + 0.2, 0.4f * koef2 + 0.2, 0.4f * koef2 + 0.2);
    glm::vec3 specular = glm::vec3(0.2f * koef2, 0.2f * koef2, 0.2f * koef2);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.30f;

    //setting point light TODO foreach petlja
    for(int i = 0; i < numOfPointLights; i++) {
        setPointLight(shader, ambient, diffuse, specular, constant, linear, quadratic, pointLightPositions[i], i);
    }

    //setting direction light
    shader.setVec3("dirLight.direction", 0.0f, 0.0f, -1.f);
    shader.setVec3("dirLight.ambient", 0.02f * koef, 0.02f * koef, 0.02f * koef);
    shader.setVec3("dirLight.diffuse", 0.2f * koef, 0.2f * koef, 0.2f*koef);
    shader.setVec3("dirLight.specular", 0.2f*koef, 0.2f*koef, 0.2f*koef);


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR, Z_FAR);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)ghostPos[i].second,(float)-(ghostPos[i].first), 0.0));
    shader.setMat4("model", model);

    shader.use();
    ghostTextures[i].activateTexture(0);

    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 0);

    glBindVertexArray(VAO);

    shader.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,6);


}

void renderSkybox(ourShader shader,unsigned int VAOskybox,ourCamera mainCamera, unsigned int skyboxTexture){



    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    shader.use();
    glm::mat4 view = glm::mat4(glm::mat3(mainCamera.GetViewMatrix())); // remove translation from the view matrix
    shader.setMat4("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR, Z_FAR);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAOskybox);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}


void renderPacman(std::pair<int,int> currPos,unsigned int VAO,ourShader shader,ourTexture pacmanTexture, ourCamera camera,
                  glm::vec3 pointLightPositions[],int numOfPointLights,int pacmanRotation){

    float koef = (float)(150-brPoena) / 150;
    koef = 0.9;

    glBindVertexArray(VAO);
    shader.use();

    shader.setVec3("viewPos", camera.Position);
    shader.setFloat("material.shininess", 32.0f);

    glm::vec3 ambient = glm::vec3(0.05f * koef, 0.05f* koef, 0.05f * koef);
    glm::vec3 diffuse = glm::vec3(0.8f * koef, 0.8f * koef, 0.8f * koef);
    glm::vec3 specular = glm::vec3(0.5f * koef, 0.5f * koef, 0.5f * koef);
    float constant = 1.f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    ambient = glm::vec3(0.f);
    diffuse = glm::vec3(0.f);
    specular = glm::vec3(0.f);

    for(int i = 0; i < numOfPointLights; i++) {
        setPointLight(shader, ambient, diffuse, specular, constant, linear, quadratic, pointLightPositions[i], i);
    }

    //setting direction light
    shader.setVec3("dirLight.direction", 0.0f, 0.0f, -1.f);
    shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("dirLight.diffuse", 0.5f * koef, 0.5f * koef, 0.5f * koef);
    shader.setVec3("dirLight.specular", 0.5f * koef, 0.5f * koef, 0.5f * koef);


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR, Z_FAR);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)currPos.second,(float)-(currPos.first), 0.0));
    model = glm::rotate(model, glm::radians(90.f * pacmanRotation), glm::vec3(0.f,0.f,1.f));
    shader.setMat4("model", model);

    shader.use();
    pacmanTexture.activateTexture(0);

    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 0);

    glBindVertexArray(VAO);

    shader.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,6);


}

void renderMap(int i,int j,int type,unsigned int VAO,ourShader shader, std::vector<ourTexture> teksture,
               ourCamera camera, glm::vec3 pointLightPositions[],int numOfPointLights){

    if(type == 0) return;


    float koef = (float)(150-brPoena) * (150-brPoena) / (150*150);
    float koef2 = (float)(150-brPoena) / 150;

    if(brPoena > 70){
        if(randNum == 1){
            koef = 1.f;
            koef2 = 1.f;
        }
    }




    glm::vec3 scalingVector = glm::vec3(1.f);

    shader.use();
    shader.setVec3("viewPos", camera.Position);
    shader.setFloat("material.shininess", 32.0f);


    //setting point light
    glm::vec3 ambient = glm::vec3(0.05f * koef2, 0.05f * koef2, 0.05f * koef2);
    glm::vec3 diffuse = glm::vec3(0.4f * koef2, 0.4f * koef2, 0.4f * koef2);
    glm::vec3 specular = glm::vec3(0.4f * koef2, 0.4f * koef2, 0.4f * koef2);
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    for(int i = 0; i < numOfPointLights; i++) {
        setPointLight(shader, ambient, diffuse, specular, constant, linear, quadratic, pointLightPositions[i], i);
    }

    //setting direction light
    shader.setVec3("dirLight.direction", 0.0f, 0.0f, -1.f);
    shader.setVec3("dirLight.ambient", 0.08f, 0.08f, 0.08f);
    shader.setVec3("dirLight.diffuse", 0.2f * koef, 0.2f * koef, 0.2f * koef);
    shader.setVec3("dirLight.specular", 0.2f * koef, 0.2f * koef, 0.2f * koef);


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR, Z_FAR);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    if(type == FOOD_BOX){
        //OSTAVI OSVETLJENJE ZA FOOD BOX
        shader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
        scalingVector*=0.2;
    }
    //trik koji cini da gornja kocka nestane TODO srediti naci bolje resenje
    if(type == NO_BOX){
        scalingVector*=0.0001f;
    }

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)(i),(float)(-j), 0.0));
    model = glm::scale(model, scalingVector);
    shader.setMat4("model", model);

    shader.use();
    teksture[type].activateTexture(0);
    teksture[NO_SPECULAR].activateTexture(1);

    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);


    shader.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,36);

//donja strana mape

    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)(i),(float)(-j), -1.0));
    shader.setMat4("model", model);

    teksture[FLOOR_BOX].activateTexture(0);
    teksture[FLOOR_SPECULAR].activateTexture(1);
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);

    glDrawArrays(GL_TRIANGLES,0,36);

}

void renderLightCube(unsigned int VAO, ourShader shader,ourCamera camera, glm::vec3 pointLightPosition){

    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR, Z_FAR);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.f);
    model = glm::mat4(1.f);
    model = glm::translate(model, pointLightPosition);
    model = glm::scale(model, glm::vec3(0.5f));

    shader.setMat4("model", model);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void renderModel(Model nasModel, Shader modelShader, ourCamera kamera, glm::vec3 position) {

    float koef = (float)(150-brPoena) * (150-brPoena) / (22500);
    float koef2 = (float)(150-brPoena) / 150;

    if(brPoena > 70){
        if(randNum == 1){
            koef = 1.f;
            koef2 = 1.f;
        }
    }

    modelShader.use();
    glm::mat4 projection = glm::perspective(glm::radians(kamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR,Z_FAR);
    glm::mat4 view = kamera.GetViewMatrix();
    modelShader.setMat4("projection", projection);
    modelShader.setMat4("view", view);


    modelShader.setVec3("viewPos", kamera.Position);
    modelShader.setVec3("dirLight.direction", 0.0f, 0.0f, -1.f);
    modelShader.setVec3("dirLight.ambient", 0.25*koef2 + 0.05f, 0.25f*koef2 + 0.05f, 0.25f*koef2 + 0.05f);
    modelShader.setVec3("dirLight.diffuse", 1.0f * koef2 + 0.4f, 1.0f *koef2 + 0.4f, 1.0f*koef2 + 0.4f);
    modelShader.setVec3("dirLight.specular", 0.5f * koef2 + 0.1f, 0.5f * koef2 + 0.1f, 0.5f*koef2+ 0.1f);

// render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.15));	// it's a bit too big for our scene, so scale it down
    modelShader.setMat4("model", model);
    nasModel.Draw(modelShader);

}

void setPointLight(ourShader shader, glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,
                   float constant,float linear,float quadratic,glm::vec3 pointLightPosition,int num){

    shader.use();
    std::string name = "pointLights[" + std::to_string(num) + "].";
    shader.setVec3(name+"position", pointLightPosition);
    shader.setVec3(name+"ambient",ambient);
    shader.setVec3(name+"diffuse", diffuse);
    shader.setVec3(name+"specular", specular);
    shader.setFloat(name+"constant", constant);
    shader.setFloat(name+"linear", linear);
    shader.setFloat(name+"quadratic", quadratic);

}
