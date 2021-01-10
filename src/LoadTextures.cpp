//
// Created by dzondzi on 28.12.20..
//

#include <rg/LoadTextures.h>

unsigned int loadCubemap(){
    std::vector<std::string> faces = {
            "resources/textures/skybox2/posx.jpg",
            "resources/textures/skybox2/negx.jpg",
            "resources/textures/skybox2/posy.jpg",
            "resources/textures/skybox2/negy.jpg",
            "resources/textures/skybox2/posz.jpg",
            "resources/textures/skybox2/negz.jpg"
    };

    unsigned int texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    int width, height, nrChannels;
    for(int i = 0; i < faces.size(); i++){
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else{
            std::cout << "cubemap tex " << faces[i] << " failed to load" << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texID;
}

std::vector<ourTexture> loadGhostTextures(){
    std::vector<ourTexture> teksture;

    ourTexture tex0("resources/textures/ghost1.png");
    ourTexture tex1("resources/textures/ghost2.png");
    ourTexture tex2("resources/textures/ghost3.png");
    ourTexture tex3("resources/textures/ghost4.png");


    teksture.push_back(tex0);
    teksture.push_back(tex1);
    teksture.push_back(tex2);
    teksture.push_back(tex3);


    return teksture;

}


std::vector<ourTexture> loadTextures(){
    std::vector<ourTexture> textures;

    ourTexture tex0("resources/textures/container.jpg");
    ourTexture tex1("resources/textures/pacwall.jpg");
    ourTexture tex2("resources/textures/awesomeface.png");
    ourTexture tex3("resources/textures/ghost1.png");
    ourTexture tex4("resources/textures/ghost2.png");
    ourTexture tex5("resources/textures/pm.png");
    ourTexture tex6("resources/textures/ghost3.png");
    ourTexture tex7("resources/textures/container.jpg");
    ourTexture tex8("resources/textures/ghost4.png");
    ourTexture tex9("resources/textures/noSpecular.jpg");
    ourTexture tex10("resources/textures/stripes3.jpg");



    textures.push_back(tex0);
    textures.push_back(tex1);
    textures.push_back(tex2);
    textures.push_back(tex3);
    textures.push_back(tex4);
    textures.push_back(tex5);
    textures.push_back(tex6);
    textures.push_back(tex7);
    textures.push_back(tex8);
    textures.push_back(tex9);
    textures.push_back(tex10);


    return textures;

}