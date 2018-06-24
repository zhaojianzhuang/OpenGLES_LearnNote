//
//  scene.cpp
//  ES
//
//  Created by jianzhuangzhao on 2018/5/26.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "scene.h"
#include "until.h"
#include "skybox.h"
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
glm::vec3 cameraPos(10.0f, 10.0f, 10.0f);
SkyBox skybox;

void init()
{
    viewMatrix=glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    skybox.init("res/");
}

void setViewPortSize(float width, float height)
{
    projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skybox.draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
}
