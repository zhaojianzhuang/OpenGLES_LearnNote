//
//  model.cpp
//  OpenGLES_Note04
//
//  Created by jianzhuangzhao on 2018/6/27.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "model.h"
#include "until.h"
Model::Model()
{
    
}
void Model::init(const char *modelPath)
{
    
    struct FloatData {
        float v[3];
    };
    std::vector<FloatData> positions, texoords, normals;
    struct VertexDefine {
        int posIndex;
        int texcoordIndex;
        int normalIndex;
    };
    std::vector<VertexDefine>vertexes;
    
    int nFileSize = 0 ;
    
    unsigned char *fileContent = loadFileContent(modelPath, nFileSize);
    if (fileContent == nullptr)
    {
        return;
    }
    std::stringstream ssFileContent((char *)fileContent);
    char szOneLine[256];
    std::string temp;
    while (!ssFileContent.eof())
    {
        memset(szOneLine, 0, 256);
        ssFileContent.getline(szOneLine, 256);
        if (strlen(szOneLine) > 0 )
        {
            std::stringstream ssOneLine(szOneLine);
            if (szOneLine[0] == 'v') {
                if (szOneLine[1] == 't')
                {
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    texoords.push_back(floatData);
                    printf("texcoords:%f  %f\n", floatData.v[0], floatData.v[1]);
                } else if (szOneLine[1] == 'n')
                {
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    ssOneLine >> floatData.v[2];
                    normals.push_back(floatData);
                    printf("normals:%f  %f  %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
                } else
                {
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    ssOneLine >> floatData.v[2];
                    positions.push_back(floatData);
                    printf("positions:%f  %f  %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
                }
            } else if (szOneLine[0] == 'f')
            {
                ssOneLine >> temp;
                std::string vertexStr;
                for (int i = 0 ; i < 3; i++) {
                    ssOneLine >> vertexStr;
                    size_t pos =  vertexStr.find_first_of('/');
                    std::string posIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
                    VertexDefine vd;
                    vd.posIndex = atoi(posIndexStr.c_str());
                    vd.normalIndex = atoi(normalIndexStr.c_str());
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
                    vertexes.push_back(vd);
                }
            }
            
        }
        
    }
    
    delete fileContent;
    int vertexCount = (int )vertexes.size();
    mVertexBuffer = new VertexBuffer;
    mVertexBuffer->setSize(vertexCount);
    for (int i = 0 ; i < vertexCount; i++) {
        float *temp = positions[vertexes[i].posIndex - 1].v;
        mVertexBuffer->setPositin(i, temp[0], temp[1], temp[2]);
        temp = normals[vertexes[i].normalIndex - 1].v;
        mVertexBuffer->setNormal(i, temp[0], temp[1], temp[2]);
        temp = texoords[vertexes[i].texcoordIndex - 1].v;
        mVertexBuffer->setTexcoord(i, temp[0], temp[1]);
    }
    mShader = new Shader;
    mShader->init("res/model.vs", "res/model.fs");
}


void Model::setPosition(float x, float y, float z)
{
    mModelMatrix = glm::translate(x, y, z);
}

void Model::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMarix, float x, float y, float z)
{
    mShader->setVec4("U_CameraPos", x, y, z, 1.0f);
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->bind();
    glm::mat4 it = glm::inverseTranspose(mModelMatrix);
    mShader->bind(glm::value_ptr(mModelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMarix));
    glUniformMatrix4fv(glGetUniformLocation(mShader->mProgram, "IT_ModelMatrix"), 1, GL_FALSE, glm::value_ptr(it));
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->mVertexCount);
    mVertexBuffer->unbind();
}
void Model::setTexture(const char *imagePath)
{
    mShader->setTexture("U_Texture", imagePath);
}

