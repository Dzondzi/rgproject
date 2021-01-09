//
// Created by dzondzi on 28.12.20..
//

#include <rg/LoadTextures.h>

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

    for(auto &tekstura : teksture){
        tekstura.setWrappingST(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    }

    return teksture;

}


std::vector<ourTexture> loadTextures(){
    std::vector<ourTexture> teksture;

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


    teksture.push_back(tex0);
    teksture.push_back(tex1);
    teksture.push_back(tex2);
    teksture.push_back(tex3);
    teksture.push_back(tex4);
    teksture.push_back(tex5);
    teksture.push_back(tex6);
    teksture.push_back(tex7);
    teksture.push_back(tex8);
    teksture.push_back(tex9);
    teksture.push_back(tex10);


    return teksture;

}