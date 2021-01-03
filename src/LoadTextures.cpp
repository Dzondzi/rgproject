//
// Created by dzondzi on 28.12.20..
//

#include <rg/LoadTextures.h>

std::vector<Texture> loadTextures(){
    std::vector<Texture> teksture;

    Texture tex0("resources/textures/container.jpg");
    Texture tex1("resources/textures/bricks2.jpg");
    Texture tex2("resources/textures/awesomeface.png");
    Texture tex3("resources/textures/redpm.png");
    Texture tex4("resources/textures/blueghostPM.png");
    Texture tex5("resources/textures/pm.png");
    Texture tex6("resources/textures/mincrgrass.jpg");
    Texture tex7("resources/textures/white.png");
    Texture tex8("resources/textures/noSpecular.jpg");
    Texture tex9("resources/textures/container2.png");
    Texture tex10("resources/textures/container2_specular.png");


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