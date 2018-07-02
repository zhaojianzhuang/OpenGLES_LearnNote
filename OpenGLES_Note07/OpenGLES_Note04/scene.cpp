//
//  scene.cpp
//  ES
//
//  Created by jianzhuangzhao on 2018/5/26.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "scene.h"
#include "until.h"
#include "particlesystem.h"
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
glm::vec3 cameraPos(5.0f, 4.0f, 10.0f);
glm::mat4 fsqViewMatrix;

ParticleSystem ps;
void init()
{
    viewMatrix=glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    ps.init(0.0f, 0.0f, 0.0f);
}

void setViewPortSize(float width, float height)
{
    projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void draw()
{
    float frameTime = getFrameTime();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ps.update(frameTime);
    ps.draw(viewMatrix, projectionMatrix);
}


