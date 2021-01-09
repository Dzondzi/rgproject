//
// Created by dzondzi on 28.12.20..
//

#include <rg/LoadTextures.h>

std::vector<ourTexture> loadGhostTextures(){
    std::vector<ourTexture> textures;

    ourTexture tex0("resources/textures/ghost1.png");
    ourTexture tex1("resources/textures/ghost2.png");
    ourTexture tex2("resources/textures/ghost3.png");
    ourTexture tex3("resources/textures/ghost4.png");


    textures.push_back(tex0);
    textures.push_back(tex1);
    textures.push_back(tex2);
    textures.push_back(tex3);

    for(auto &tekstura : textures){
        tekstura.setWrappingST(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    }

    return textures;

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