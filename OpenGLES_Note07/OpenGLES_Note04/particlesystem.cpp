//
//  particlesystem.cpp
//  OpenGLES_Note04
//
//  Created by jianzhuangzhao on 2018/7/2.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "particlesystem.h"
#include "until.h"
void ParticleSystem::init(float x, float y, float z)
{
    mModelMatrix = glm::translate(x, y, z);
    mVertexBuffer = new VertexBuffer;
    int particleCount = 180;
    mVertexBuffer->setSize(particleCount);
    for (int i=0;i<particleCount;++i){
        mVertexBuffer->setPositin(i, 2.0f*cosf(float(i) * 8.0f*3.14f / 180.0f), 0.0f, 2.0f*sinf(float(i) * 8.0f*3.14f / 180.0f));
        mVertexBuffer->setColor(i, 1.0f, 1.0f, 1.0f);
    }
    mShader = new Shader;
    mShader->init("res/particle.vs", "res/particle.fs");
    mTexture = createProduceTexture(256);
}
void ParticleSystem::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    mVertexBuffer->bind();
    mShader->bind(glm::value_ptr(mModelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glDrawArrays(GL_POINTS, 0, mVertexBuffer->mVertexCount);
    mVertexBuffer->unbind();
    glDisable(GL_BLEND);
}

void ParticleSystem::update(float deltaTime)
{
    static float angle = 0.0f;
    angle += deltaTime*10.0f;
    mModelMatrix = glm::rotate(angle, 0.0f, 1.0f, 0.0f);
    for (int i = 0; i < mVertexBuffer->mVertexCount; ++i) {
        Vertex &vertex = mVertexBuffer->get(i);
        vertex.Normal[1] = 0.1f*i;
        if (i>90){
            break;
        }
    }
    
}

