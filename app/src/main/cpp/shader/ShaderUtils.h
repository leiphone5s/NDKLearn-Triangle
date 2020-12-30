//
// Created by Lenovo on 2020/11/30.
//

#ifndef OPENGLTRIANGLE_SHADERUTILS_H
#define OPENGLTRIANGLE_SHADERUTILS_H

#include <stdlib.h>
#include <android/asset_manager_jni.h>
#include "GLES3/gl3.h"
#include "../log/XLog.h"

static GLuint loadShader(GLenum shaderType,const char *shaderSource){
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(shaderType);
    if(shader == GL_NONE){
        LOGE("create shader failed! shaderType: %d",shaderType);
        return GL_NONE;
    }
    //load the shader source
    glShaderSource(shader,1,&shaderSource,NULL);

    //compile the shader source
    glCompileShader(shader);

    //check the compile status
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
    if(!compiled){
        //retrieve the compiler messages when compilation fails
        GLint infoLen = 0;

        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLen);

        if(infoLen > 1){
            char *infoLog = static_cast<char *>(malloc(sizeof(char) * infoLen));
            glGetShaderInfoLog(shader,infoLen,NULL,infoLog);
            LOGE("Error compiling shader:\n%s\n",infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return GL_NONE;
    }
    return shader;
}

static GLuint createProgram(const char *vertexSource,const char *fragmentSource){
    int vertexShader = loadShader(GL_VERTEX_SHADER,vertexSource);
    if(vertexShader == GL_NONE){
        LOGE("load vertex shader failed!");
        return GL_NONE;
    }
    int fragmentShader = loadShader(GL_FRAGMENT_SHADER,fragmentSource);
    if(fragmentShader == GL_NONE){
        LOGE("load fragment shader failed!");
        return GL_NONE;
    }
    int program = glCreateProgram();
    if(program == GL_NONE){
        LOGE("create program failed!");
        return GL_NONE;
    }
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);

    //把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program,GL_LINK_STATUS,&linked);
    if(linked == GL_FALSE){
        GLint len = 0;
        glGetProgramiv(program,GL_INFO_LOG_LENGTH,&len);
        if(len > 1){
            char *infoLog = static_cast<char *>(malloc(sizeof(char) * len));
            glGetProgramInfoLog(program,len,NULL,infoLog);
            LOGE("Error link program:%s",infoLog);
            free(infoLog);
        }
        return GL_NONE;
    }
    return program;
}

static char* readAssetFile(const char *filename,AAssetManager *mgr){
    if(mgr == NULL){
        LOGE("pAssetManager is null");
        return NULL;
    }
    AAsset  *pAsset = AAssetManager_open(mgr,filename,AASSET_MODE_UNKNOWN);
    off_t  len = AAsset_getLength(pAsset);
    char *pBuffer = (char*) malloc(len+1);
    pBuffer[len] = '\0';
    int numByte = AAsset_read(pAsset,pBuffer,len);
    LOGD("numByte:%d,len:%ld",numByte,len);
    AAsset_close(pAsset);
    return pBuffer;

}


#endif //OPENGLTRIANGLE_SHADERUTILS_H
