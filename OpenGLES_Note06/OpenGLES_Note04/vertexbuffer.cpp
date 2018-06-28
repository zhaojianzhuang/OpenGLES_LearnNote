//
//  vertexbuffer.cpp
//  ES
//
//  Created by jianzhuangzhao on 2018/5/28.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "vertexbuffer.h"
#include "until.h"
void VertexBuffer::setSize(int vertexCount)
{
    mVertexCount = vertexCount;
    mVertexes = new Vertex[vertexCount];
    memset(mVertexes, 0, sizeof(Vertex) * mVertexCount);
    mVBO = createBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, GL_STATIC_DRAW);
}

void VertexBuffer::setPositin(int index, float x, float y, float z, float w)
{
    mVertexes[index].Position[0] = x;
    mVertexes[index].Position[1] = y;
    mVertexes[index].Position[2] = z;
    mVertexes[index].Position[3] = w;
}
void VertexBuffer::setColor(int index, float r, float g, float b, float a)
{
    mVertexes[index].Color[0] = r;
    mVertexes[index].Color[1] = g;
    mVertexes[index].Color[2] = b;
    mVertexes[index].Color[3] = a;
}
void VertexBuffer::setTexcoord(int index, float x, float y  )
{
    mVertexes[index].Texcoord[0] = x;
    mVertexes[index].Texcoord[1] = y;
}
void VertexBuffer::setNormal(int index, float x, float y, float z)
{
    mVertexes[index].Normal[0] = x;
    mVertexes[index].Normal[1] = y;
    mVertexes[index].Normal[2] = z;
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * mVertexCount , mVertexes);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vertex& VertexBuffer::get(int index)
{
    return mVertexes[index];
}



