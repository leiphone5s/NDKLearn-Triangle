package com.zhidao.ndktest01.natives;

import android.content.res.AssetManager;

/**
 * @author: fenglei
 * @date: 2020/12/29
 */

public class NativeOperate {

    static {
        System.loadLibrary("native-lib");
    }

    public native void glInit();

    public native void glResize(int width, int height);

    public native void glDraw();

    public native void registerAssetManager(AssetManager assetManager);
}
