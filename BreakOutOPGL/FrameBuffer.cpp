#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const int& screenWidth, const int& screenHeight, Shader & shader): shader(shader) {
   
    
    //FrameBufferObject
    glGenFramebuffers(1, &frameID);
    glBindFramebuffer(GL_FRAMEBUFFER, frameID);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texID);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, screenWidth, screenHeight,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texID, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer échec" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    setVAO();
}
FrameBuffer::~FrameBuffer() {
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteRenderbuffers(1, &frameID);
}
void FrameBuffer::setVAO() {
    float quadVal[] = {
        //position          //texCoor
       -1.0f, -1.0f, 0.0f, 0.0f,
       -1.0f, 1.0f, 0.0f, 1.0f,
       1.0f, -1.0f, 1.0f, 0.0f,
       -1.0f, 1.0f, 0.0f, 1.0f,
       1.0f, 1.0f, 1.0f, 1.0f,
       1.0f, -1.0f, 1.0f, 0.0f

    }; 
   
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVal), &quadVal, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
    glBindVertexArray(0);

}
void const FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameID);
}



void FrameBuffer::Draw() {
    this->shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texID);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}