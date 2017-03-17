#include <jni.h>
#include <string>
#include <android/log.h>

#include <iostream>
#include <time.h>

using namespace std;

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>


#ifdef __cplusplus  //禁止编译器改函数名字
extern "C" {
#endif

//LOG定义
#define  LOG_TAG    "Native_Jni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

/* 内全局变量begin */
//static jboolean b_IS_COPY = JNI_TRUE;

/**
 * 返回一个字符串
 */
JNIEXPORT jstring JNICALL
Java_com_myself_jnitestdemo_JniTest_stringFromJNI(
        JNIEnv *env,
        jobject thiz) {

    jstring tag = env->NewStringUTF("Native-Lib");

    std::string hello = "JNI:Hello from C++";

    LOGD("notify message is: %d", 6);

    return env->NewStringUTF(hello.c_str());
}

/**
 * 获取当前时间
 */
JNIEXPORT jstring JNICALL
Java_com_myself_jnitestdemo_JniTest_getAcquisitionTime(
        JNIEnv *env,
        jobject instance) {

    struct tm *ptr;
    time_t lt;
    lt = time(NULL);
    ptr = gmtime(&lt);//世界时间
//    ptr = localtime(&lt);//当地时间

    char *ctime_0 = asctime(ptr);//Sat Jul 30 08:43:03 2005
    char *ctime_1 = ctime(&lt);

//    LOGI("asctime() Date is: ", &ctime_0);
//    LOGW("ctime() Date is: ", &ctime_1);

//    LOGE("ctime_r() Date is: ", " ");

    return env->NewStringUTF(ctime_1);
}

/**
 * 两个数求和
 */
JNIEXPORT jfloat JNICALL
Java_com_myself_jnitestdemo_JniTest_getTwoNumbersAnd(
        JNIEnv *env,
        jobject instance,
        jfloat a,
        jfloat b) {

    return a + b;
}

#ifdef __cplusplus
}
#endif