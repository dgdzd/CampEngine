//
//  post_processor.h
//  CampEngine++
//
//  Created by Noah Campagne on 19/04/2024.
//

#ifndef CE_POST_PROCESSOR_H
#define CE_POST_PROCESSOR_H

#include <CampEngine/Graphics/Shader.h>
#include <CampEngine/Graphics/Texture.h>

#include <map>
#include <string>

class PostProcessor {
public:
    
    Shader PPShader;
    Texture texture;
    unsigned int width, height;
    
    PostProcessor();
    PostProcessor(Shader shader, unsigned int width, unsigned int height);
    
    void start();
    void end();
    void render();
    void render(glm::vec2 frame);
    
    private:
    unsigned int MSFBO, FBO;
    unsigned int RBO;
    unsigned int VAO;
    
    void initData();
};

#endif /* post_processor_h */
