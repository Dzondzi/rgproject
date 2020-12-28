//
// Created by dzondzi on 28.12.20..
//

#include <rg/LoadTextures.h>

std::vector<Texture> initTextures(){
    std::vector<Texture> teksture;

    Texture tex0("resources/textures/container.jpg");
    Texture tex1("resources/textures/awesomeface.png");
    Texture tex2("resources/textures/bricks2.jpg");
    Texture tex3("resources/textures/redpm.png");
    Texture tex4("resources/textures/blueghostPM.png");
    Texture tex5("resources/textures/pm.png");



    teksture.push_back(tex0);
    teksture.push_back(tex1);
    teksture.push_back(tex2);
    teksture.push_back(tex3);
    teksture.push_back(tex4);
    teksture.push_back(tex5);

    return teksture;

}