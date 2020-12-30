package com.zhidao.ndktest01.natives;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author: fenglei
 * @date: 2020/12/29
 */

public class NativeRenderer implements GLSurfaceView.Renderer {

    public static final String TAG = "NativeRenderer";
    NativeOperate nativeOperate;
    Context mContext;

    public NativeRenderer(Context context){
        nativeOperate = new NativeOperate();
        mContext = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeOperate.registerAssetManager(mContext.getAssets());
        nativeOperate.glInit();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeOperate.glResize(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeOperate.glDraw();
    }
}
