#include <jni.h>
#include <string>
#include "GLES3/gl3.h"
#include "log/XLog.h"
#include "shader/ShaderUtils.h"

AAssetManager  *g_pAssetManager = NULL;

GLint program;

extern "C" JNIEXPORT jstring JNICALL
Java_com_zhidao_ndktest01_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_zhidao_ndktest01_natives_NativeOperate_glInit(JNIEnv *env, jobject thiz) {
    // TODO: implement glInit()
    char *vertexShaderSource = readAssetFile("vertex.vsh",g_pAssetManager);
    char *fragmentShaderSource = readAssetFile("fragment.fsh",g_pAssetManager);
    program = createProgram(vertexShaderSource,fragmentShaderSource);
    if(program == GL_NONE){
        LOGE("gl init failed!");
    }
    glClearColor(0.0f,0.0f,0.0f,1.0f);

}

JNIEXPORT void JNICALL
Java_com_zhidao_ndktest01_natives_NativeOperate_glResize(JNIEnv *env, jobject thiz, jint width,
                                                         jint height) {
    // TODO: implement glResize()
    glViewport(0,0,width,height);
}
JNIEXPORT void JNICALL
Java_com_zhidao_ndktest01_natives_NativeOperate_glDraw(JNIEnv *env, jobject thiz) {
    // TODO: implement glDraw()
    GLint vertexCount = 3;
    //openGL的世界坐标系是[-1,-1,1,1]
    GLfloat vertices[]={
            0.0f,0.5f,0.0f, //第一个点(x,y,z)
            -0.5f,-0.5f,0.0f,   //第二个点(x,y,z)
            0.5f,-0.5f,0.0f //第三个点(x,y,z)
    };
    glClear(GL_COLOR_BUFFER_BIT); //clear color buffer
    //1.选择使用的程序
    glUseProgram(program);
    //2.加载顶点数据
    // opengl3.0，使用layout(location = 0)已经指定location可以直接使用
    glVertexAttribPointer(0,vertexCount,GL_FLOAT,GL_FALSE,3 * sizeof(float),vertices);
    glEnableVertexAttribArray(0);
    //3.绘制
    glDrawArrays(GL_TRIANGLES,0,vertexCount);
}


JNIEXPORT void JNICALL
Java_com_zhidao_ndktest01_natives_NativeOperate_registerAssetManager(JNIEnv *env, jobject thiz,
                                                                     jobject asset_manager) {
    // TODO: implement registerAssetManager()
    if(asset_manager){
        g_pAssetManager = AAssetManager_fromJava(env,asset_manager);
    }else{
        LOGE("assetManager is null!");
    }
}

}