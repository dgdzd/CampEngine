//
//  post_processor.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 19/04/2024.
//

#include <CampEngine/Graphics/PostProcessor.h>

#include <glad/glad.h>

#include <CampEngine/Game/Constants.h>

PostProcessor::PostProcessor() {
    
}

PostProcessor::PostProcessor(Shader shader, unsigned int width, unsigned int height) : PPShader(shader), width(width), height(height) {
    texture.generate(width, height, NULL, GL_RGB);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Logger::CampEngine.error("Failed to initialize FBO");
    }
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Logger::CampEngine.error("Failed to initialize MSFBO");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    initData();
}

void PostProcessor::initData() {
    unsigned int VBO;
    float vertices[] = {
    //  Position      Texture
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 1.0f,  0.0f, 1.0f,
        
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f, 1.0f,   1.0f, 1.0f
        
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PostProcessor::start() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessor::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void PostProcessor::render() {
    PPShader.use();
    glActiveTexture(GL_TEXTURE0);
    texture.use();
    PPShader.setInt("screenTexture", 0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PostProcessor::render(glm::vec2 frame) {
    PPShader.use();
    glActiveTexture(GL_TEXTURE0);
    texture.use();
    PPShader.setInt("screenTexture", 0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
