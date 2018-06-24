//
//  skybox.cpp
//  ES
//
//  Created by jianzhuangzhao on 2018/6/17.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include <stdio.h>
#include "skybox.h"
#include "until.h"
void SkyBox::init(const char *imageDir) {
    mVertexBuffer = new VertexBuffer[6];
    mShader = new Shader[6];
    initFront(imageDir);
    initBack(imageDir);
    initLeft(imageDir);
    initRight(imageDir);
    initTop(imageDir);
    initBottom(imageDir);
}
void SkyBox::initFront(const char *imageDir) {
    mShader[0].init("res/skybox.vs", "res/skybox.fs");
    char temp[256];
    memset(temp, 0, 256);
    strcpy(temp, imageDir);
    strcat(temp, "front.bmp");
    mShader[0].setTexture("U_Texture", temp);
    mVertexBuffer[0].setSize(4);
    mVertexBuffer[0].setPositin(0, -0.5f, -0.5f, -0.5f);
    mVertexBuffer[0].setTexcoord(0, 0.0f,0.0f);
    mVertexBuffer[0].setPositin(1, 0.5f, -0.5f, -0.5f);
    mVertexBuffer[0].setTexcoord(1, 1.0f, 0.0f);
    mVertexBuffer[0].setPositin(2, -0.5f, 0.5f, -0.5f);
    mVertexBuffer[0].setTexcoord(2, 0.0f, 1.0f);
    mVertexBuffer[0].setPositin(3, 0.5f, 0.5f, -0.5f);
    mVertexBuffer[0].setTexcoord(3, 1.0f, 1.0f);
}
void SkyBox::initBack(const char *imageDir) {
    mShader[1].init("res/skybox.vs", "res/skybox.fs");
    char temp[256];
    memset(temp, 0, 256);
    strcpy(temp, imageDir);
    strcat(temp, "back.bmp");
    mShader[1].setTexture("U_Texture", temp);
    mVertexBuffer[1].setSize(4);
    mVertexBuffer[1].setPositin(0, 0.5f, -0.5f, 0.5f);
    mVertexBuffer[1].setTexcoord(0, 0.0f,0.0f);
    mVertexBuffer[1].setPositin(1, -0.5f, -0.5f, 0.5f);
    mVertexBuffer[1].setTexcoord(1, 1.0f, 0.0f);
    mVertexBuffer[1].setPositin(2, 0.5f, 0.5f, 0.5f);
    mVertexBuffer[1].setTexcoord(2, 0.0f, 1.0f);
    mVertexBuffer[1].setPositin(3, -0.5f, 0.5f, 0.5f);
    mVertexBuffer[1].setTexcoord(3, 1.0f, 1.0f);
}
void SkyBox::initLeft(const char *imageDir) {
    mShader[2].init("res/skybox.vs", "res/skybox.fs");
    char temp[256];
    memset(temp, 0, 256);
    strcpy(temp, imageDir);
    strcat(temp, "left.bmp");
    mShader[2].setTexture("U_Texture", temp);
    mVertexBuffer[2].setSize(4);
    mVertexBuffer[2].setPositin(0, -0.5f, -0.5f, 0.5f);
    mVertexBuffer[2].setTexcoord(0, 0.0f,0.0f);
    mVertexBuffer[2].setPositin(1, -0.5f, -0.5f, -0.5f);
    mVertexBuffer[2].setTexcoord(1, 1.0f, 0.0f);
    mVertexBuffer[2].setPositin(2, -0.5f, 0.5f, 0.5f);
    mVertexBuffer[2].setTexcoord(2, 0.0f, 1.0f);
    mVertexBuffer[2].setPositin(3, -0.5f, 0.5f, -0.5f);
    mVertexBuffer[2].setTexcoord(3, 1.0f, 1.0f);
}
void SkyBox::initRight(const char *imageDir) {
    mShader[3].init("res/skybox.vs", "res/skybox.fs");
    char temp[256];
    memset(temp, 0, 256);
    strcpy(temp, imageDir);
    strcat(temp, "right.bmp");
    mShader[3].setTexture("U_Texture", temp);
    mVertexBuffer[3].setSize(4);
    mVertexBuffer[3].setPositin(0, 0.5f, -0.5f, -0.5f);
    mVertexBuffer[3].setTexcoord(0, 0.0f,0.0f);
    mVertexBuffer[3].setPositin(1, 0.5f, -0.5f, 0.5f);
    mVertexBuffer[3].setTexcoord(1, 1.0f, 0.0f);
    mVertexBuffer[3].setPositin(2, 0.5f, 0.5f, -0.5f);
    mVertexBuffer[3].setTexcoord(2, 0.0f, 1.0f);
    mVertexBuffer[3].setPositin(3, 0.5f, 0.5f, 0.5f);
    mVertexBuffer[3].setTexcoord(3, 1.0f, 1.0f);
}
void SkyBox::initTop(const char *imageDir) {
    mShader[4].init("res/skybox.vs", "res/skybox.fs");
    char temp[256];
    memset(temp, 0, 256);
    strcpy(temp, imageDir);
    strcat(temp, "top.bmp");
    mShader[4].setTexture("U_Texture", temp);
    mVertexBuffer[4].setSize(4);
    mVertexBuffer[4].setPositin(0, -0.5f, 0.5f, -0.5f);
    mVertexBuffer[4].setTexcoord(0, 0.0f,0.0f);
    mVertexBuffer[4].setPositin(1, 0.5f, 0.5f, -0.5f);
    mVertexBuffer[4].setTexcoord(1, 1.0f, 0.0f);
    mVertexBuffer[4].setPositin(2, -0.5f, 0.5f, 0.5f);
    mVertexBuffer[4].setTexcoord(2, 0.0f, 1.0f);
    mVertexBuffer[4].setPositin(3, 0.5f, 0.5f, 0.5f);
    mVertexBuffer[4].setTexcoord(3, 1.0f, 1.0f);
}
void SkyBox::initBottom(const char *imageDir) {
    mShader[5].init("res/skybox.vs", "res/skybox.fs");
    char temp[256];
    memset(temp, 0, 256);
    strcpy(temp, imageDir);
    strcat(temp, "bottom.bmp");
    mShader[5].setTexture("U_Texture", temp);
    mVertexBuffer[5].setSize(4);
    mVertexBuffer[5].setPositin(0, -0.5f, -0.5f, 0.5f);
    mVertexBuffer[5].setTexcoord(0, 0.0f,0.0f);
    mVertexBuffer[5].setPositin(1, 0.5f, -0.5f, 0.5f);
    mVertexBuffer[5].setTexcoord(1, 1.0f, 0.0f);
    mVertexBuffer[5].setPositin(2, -0.5f, -0.5f, -0.5f);
    mVertexBuffer[5].setTexcoord(2, 0.0f, 1.0f);
    mVertexBuffer[5].setPositin(3, 0.5f, -0.5f, -0.5f);
    mVertexBuffer[5].setTexcoord(3, 1.0f, 1.0f);
}
void SkyBox::draw(glm::mat4 &v, glm::mat4 &p, float x, float y, float z)
{
    glDisable(GL_DEPTH_TEST);
    mModelMatrix = glm::translate(x, y, z);
    for (int i = 0 ; i < 6; i++)
    {
        mVertexBuffer[i].bind();
        mShader[i].bind(glm::value_ptr(mModelMatrix), glm::value_ptr(v), glm::value_ptr(p));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        mVertexBuffer[i].unbind();
    }
}
