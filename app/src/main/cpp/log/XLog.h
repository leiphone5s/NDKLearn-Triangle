//
// Created by fenglei on 2020/12/29.
//

#ifndef NDKTEST01_XLOG_H
#define NDKTEST01_XLOG_H


#include "android/log.h"

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG,"apkcore-ndk",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"apkcore-ndk",FORMAT,##__VA_ARGS__);
#endif //NDKTEST01_XLOG_H
