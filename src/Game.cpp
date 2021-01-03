//
// Created by dzondzi on 28.12.20..
//

#include <rg/Game.h>
#include <rg/StartingGlfwInit.h>
#include <string>

void setPointLight(Shader shader, glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,
                   float constant,float linear,float quadratic,glm::vec3 pointLightPosition,int num);


unsigned int initBuffers() {

    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int  VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    return VAO;
}


void renderBox(int i, int j, int type, unsigned int VAO, Shader shader,std::vector<Texture> teksture, ourCamera camera,
               glm::vec3 pointLightPositions[], int pacmanRotation){

    if(type == 0)
        return;

    glm::vec3 scalingVector = glm::vec3(1.f);
    glm::vec3 unscalingVector = glm::vec3(1.f);

    shader.use();
    shader.setVec3("viewPos", camera.Position);
    shader.setFloat("material.shininess", 32.0f);


    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f);
    float constant = 1.f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    //setting point light
    for(int i = 0; i < 4; i++) {
        setPointLight(shader, ambient, diffuse, specular, constant, linear, quadratic, pointLightPositions[i], i);
    }

    //setting direction light
    shader.setVec3("dirLight.direction", 0.0f, 0.5f, -1.f);
    shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    if(type == 2){
        scalingVector*=0.2;
    }
    //trik koji cini da gornja kocka nestane TODO srediti naci bolje resenje
    if(type == 7){
        scalingVector*=0.001f;
    }
    if(type == 5){
        float rotation = pacmanRotation * 90.f;
    }



    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)(i),(float)(0-j), 0.0));
    model = glm::scale(model, scalingVector);
    if(type == 5){
        float rotation = pacmanRotation * 90.f;
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f,0.f,1.f));
    }


    shader.setMat4("model", model);


    shader.use();
    teksture[type].activateTexture(type);
    teksture[8].activateTexture(8);

    shader.setInt("material.diffuse", type);
    shader.setInt("material.specular", 8);


    glBindVertexArray(VAO);

    shader.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,36);

//donja strana mape


    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)(i),(float)(0-j), -1.0));
    shader.setMat4("model", model);

    teksture[6].activateTexture(6);
    teksture[8].activateTexture(8);
    shader.setInt("material.diffuse", 6);
    shader.setInt("material.specular", 8);

    glDrawArrays(GL_TRIANGLES,0,36);
}

void renderLightCube(unsigned int VAO, Shader shader,ourCamera camera, glm::vec3 pointLightPosition){
    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.f);
    model = glm::mat4(1.f);
    model = glm::translate(model, pointLightPosition);
    model = glm::scale(model, glm::vec3(0.5f));

    shader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void setPointLight(Shader shader, glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,
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
