//
//  vertexbuffer.h
//  ES
//
//  Created by jianzhuangzhao on 2018/5/28.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#pragma once
#include "ggl.h"
struct Vertex
{
    float Position[4];
    float Color[4];
    float Texcoord[4];
    float Normal[4];
};

class VertexBuffer
{
public:
    /// vbo
    GLuint mVBO;
    
    /// data
    Vertex *mVertexes;
    
    ///  mVertexes's count
    int mVertexCount;
    
    ///  set size and init
    void setSize(int vertexCount);
    
    ///  set position data
    void setPositin(int index, float x, float y, float z, float w=1.0f);
    
    ///  set color data
    void setColor(int index, float r, float g, float b, float a=1.0f);
    
    ///  set texcoord data
    void setTexcoord(int index, float x, float y);
    
    ///  set normal data
    void setNormal(int index, float x, float y ,float z);
    
    ///  bind data
    void bind();
    
    ///  unbind data
    void unbind();
    
    ///  get the index of mVertexes's Vertex
    Vertex& get(int index);
};




