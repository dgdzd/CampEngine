//
//  post_processor.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 19/04/2024.
//

#include <render/post_processor.h>

PostProcessor::PostProcessor() {
    
}

PostProcessor::PostProcessor(Shader shader, unsigned int width, unsigned int height) : PPShader(shader), width(width), height(height) {
    glGenFramebuffers(1, &MSFBO);
    glGenFramebuffers(1, &FBO);
    glGenRenderbuffers(1, &RBO);
    
    glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 1, GL_RGB, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "[PostProcessor] Failed to initialize MSFBO\n";
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    texture.generate(width, height, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "[PostProcessor] Failed to initialize FBO\n";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
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
    glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::end() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void PostProcessor::render() {
    PPShader.use();
    glActiveTexture(GL_TEXTURE1);
    texture.use();
    PPShader.setInt("screenTexture", 1);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
