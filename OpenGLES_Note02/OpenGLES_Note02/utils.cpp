//
//  utils.cpp
//  OpenGLES_Note02
//
//  Created by jianzhuangzhao on 2018/6/19.
//  Copyright © 2018年 ZJZ. All rights reserved.
//

#include "utils.h"

GLuint compileShader(GLenum shaderType, const char *shaderCode)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE)
    {
        char szLog[1024] = {0};
        GLsizei loglen = 0;
        glGetShaderInfoLog(shader, 1024, &loglen, szLog);
        printf("compile shader failed error log\n: %s shaderCode:\n%s", szLog, shaderCode);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint createProgram(GLuint vsShader, GLuint fsShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vsShader);
    glAttachShader(program, fsShader);
    glLinkProgram(program);
    glDetachShader(program, vsShader);
    glDetachShader(program, fsShader);
    GLint nResult;
    glGetProgramiv(program, GL_LINK_STATUS, &nResult);
    if (nResult==GL_FALSE)
    {
        char log[1024]={0};
        GLsizei writed = 0;
        glGetProgramInfoLog(program, 1024, &writed, log);
        printf("%sreate gpu program failed link error: \n s% \n", log);
        glDeleteProgram(program);
        program = 0;
        
    }
    return program;
}
