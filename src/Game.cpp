//
// Created by dzondzi on 28.12.20..
//

#include <rg/Game.h>
#include <rg/StartingGlfwInit.h>
#include <string>

#define NO_BOX 7
#define FOOD_BOX 2
#define PACMAN 5

void setPointLight(ourShader shader, glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,
                   float constant,float linear,float quadratic,glm::vec3 pointLightPosition,int num);


unsigned int initEBOBuffers(){
    float vertices[] = {
            -0.5f, -0.5f, -0.5f, // levo dole nazad
            0.5f, -0.5f, -0.5f, //desno dole nazad
            -0.5f, 0.5f, -0.5f, // levo gore nazad
            0.5f, 0.5f, -0.5f, // desno gore nazad
            -0.5f, -0.5f, 0.5f, // levo dole napred
            0.5f, -0.5f, 0.5f, // desno dole napred
            -0.5f, 0.5f, 0.5f, // levo gore napred
            0.5f, 0.5f, 0.5f //desno gore napred
    };

    unsigned int indices[] = {
        0, 1, 2, //iza
        1, 2, 3,

        4, 5, 6,//ispred
        5, 6, 7,

        0, 4, 2,//levo
        4, 2, 6,

        1, 5, 3,//desno
        5, 3, 7,

        2, 3, 6, //gore
        3, 6, 7,

        0, 1, 4,//dole
        1, 4, 5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return VAO;
}

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


void renderBox(int i, int j, int type, unsigned int VAO, ourShader shader,std::vector<ourTexture> teksture, ourCamera camera,
               glm::vec3 pointLightPositions[], int pacmanRotation){

    if(type == 0)
        return;

    glm::vec3 scalingVector = glm::vec3(1.f);

    shader.use();
    shader.setVec3("viewPos", camera.Position);
    shader.setFloat("material.shininess", 32.0f);


    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float constant = 0.1f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    //setting point light TODO foreach petlja
    for(int i = 0; i < 8; i++) {
        setPointLight(shader, ambient, diffuse, specular, constant, linear, quadratic, pointLightPositions[i], i);
    }


    //setting direction light
    shader.setVec3("dirLight.direction", 0.0f, 0.5f, -1.f);
    shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    if(type == FOOD_BOX){
        scalingVector*=0.2;
    }
    //trik koji cini da gornja kocka nestane TODO srediti naci bolje resenje
    if(type == NO_BOX){
        scalingVector*=0.001f;
    }



    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3((float)(i),(float)(-j), 0.0));
    if(type == PACMAN){
        float rotation = pacmanRotation * 90.f;
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f,0.f,1.f));
    }
    model = glm::scale(model, scalingVector);
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
    model = glm::translate(model, glm::vec3((float)(i),(float)(-j), -1.0));
    shader.setMat4("model", model);

    teksture[6].activateTexture(6);
    teksture[7].activateTexture(7);
    shader.setInt("material.diffuse", 6);
    shader.setInt("material.specular", 7);

    glDrawArrays(GL_TRIANGLES,0,36);
}

void renderLightCube(unsigned int VAO, ourShader shader,ourCamera camera, glm::vec3 pointLightPosition){

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
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void renderModel(Model nasModel, Shader modelShader, ourCamera kamera, glm::vec3 position) {
        modelShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(kamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = kamera.GetViewMatrix();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);


        modelShader.setVec3("viewPos", kamera.Position);
        modelShader.setVec3("dirLight.direction", 0.0f, 0.5f, -1.f);
        modelShader.setVec3("dirLight.ambient", 0.25f, 0.25f, 0.25f);
        modelShader.setVec3("dirLight.diffuse", 1.4f, 1.4f, 1.4f);
        modelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

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
