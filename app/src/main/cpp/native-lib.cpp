#include <jni.h>
#include <string>


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/inotify.h>
//#include <helper.h>

extern "C"

/* 宏定义begin */
//清0宏
#define MEM_ZERO(pDest, destSize) memset(pDest, 0, destSize)

//LOG宏定义
#define LOG_TAG "Native_Lib"
#define LOG_DEBUG(tag, msg) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,tag, msg)
#define LOG_INFO(tag, msg) __android_log_print(ANDROID_LOG_INFO, LOG_TAG,tag, msg)
#define LOG_WARN(tag, msg) __android_log_print(ANDROID_LOG_WARN, LOG_TAG,tag, msg)
#define LOG_ERROR(tag, msg) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,tag, msg)

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

/* 内全局变量begin */
//static jboolean b_IS_COPY = JNI_TRUE;

jstring
Java_com_myself_jnitestdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject thiz) {

    jstring tag = env->NewStringUTF(LOG_TAG);

    std::string hello = "JNI:Hello from C++";

//    LOGE("notify message is:", hello);

    return env->NewStringUTF(hello.c_str());
}


/*jstring
Java_com_myself_jnitestdemo_MainActivity_initJNI(
        JNIEnv *env,
        jobject thiz) {

    jstring tag = env->NewStringUTF(LOG_TAG);

    std::string hello = "JNI:Hello from JNI !";

//    LOGE("notify message is:", hello);

    return env->NewStringUTF(hello.c_str());
}*/
