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

/**
 * 提示：(*env).NewStringUTF(ctime_1)==env->NewStringUTF(ctime_1)
 */

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
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    stringFromJNI
 * Signature: ()S
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
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    getAcquisitionTime
 * Signature: ()S
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
//    return (*env).NewStringUTF(ctime_1);
}

/**
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    getTwoNumbersAnd
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL
Java_com_myself_jnitestdemo_JniTest_getTwoNumbersAnd(
        JNIEnv *env,
        jobject instance,
        jfloat a,
        jfloat b) {

    return a + b;
}

/**
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    getStringFromNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL
Java_com_myself_jnitestdemo_JniTest_getStringFromNative
        (JNIEnv *env,
         jclass cls) {

    return 10;
}

jobject m_object;
jmethodID m_mid;
jfieldID m_fid;

/**
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    setUp
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_myself_jnitestdemo_JniTest_setUp
        (JNIEnv *env,
         jobject thiz) {

    jclass clazz = env->GetObjectClass(thiz);//获取该对象的类
    m_object = env->NewGlobalRef(thiz);//创建对象的本地变量
    m_mid = env->GetMethodID(clazz, "notifyFiledChange", "()V");//获取JAVA方法的ID
    m_fid = env->GetFieldID(clazz, "a", "I");//获取java变量的ID
    return;
}

/**
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    setA
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_myself_jnitestdemo_JniTest_setA
        (JNIEnv *env,
         jobject thiz,
         jint i) {

    env->SetIntField(m_object, m_fid, i);
    env->CallVoidMethod(m_object, m_mid);
    return;
}


#ifdef __cplusplus
}
#endif