//
// Created by matf-rg on 30.10.20..
//

#ifndef PROJECT_BASE_TEXTURE2D_H
#define PROJECT_BASE_TEXTURE2D_H
#include <glad/glad.h>
#include <stb_image.h>
#include <learnopengl/filesystem.h>
#include <iostream>


class ourTexture
{
    unsigned int tex;
public:
    ourTexture(std::string path){

        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load((FileSystem::getPath(path)).c_str(), &width, &height, &nrChannels, 0);

        GLint type;
        if (nrChannels == 1)
            type = GL_RED;
        else if (nrChannels == 3)
            type = GL_RGB;
        else if (nrChannels == 4)
            type = GL_RGBA;

        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{
            std::cout << FileSystem::getPath(path) << "\n";
            std::cout << "Failed to load texture" << std::endl;
            exit(EXIT_FAILURE);
        }
        stbi_image_free(data);

    }

    void setWrappingST(GLint param1, GLint param2){
        activateTexture(this->tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param2);
    }

    void setFilteringMinMag(GLint param1, GLint param2){
        activateTexture(tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2);
    }


    void activateTexture(int value){
        glActiveTexture(GL_TEXTURE0 + value);
        glBindTexture(GL_TEXTURE_2D, this->tex);
    }

    unsigned int getTex(){
        return tex;
    }
};


#endif //PROJECT_BASE_TEXTURE2D_H
