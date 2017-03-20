#include <jni.h>
#include <string>
#include <android/log.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/inotify.h>

/**
 * 提示：(*env).NewStringUTF(ctime_1)==env->NewStringUTF(ctime_1)
 */
//string x = "10";
//int i = atoi(x.c_str());//string-->int、long
//或者32位平台转换为long int
//int ilove = strtol(x.c_str(), NULL, 10);
//float f = atof(x.c_str());//string-->float、double

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
//    std::string hello("JNI:Hello from C++");//另一种写法

    const char *s = env->GetStringUTFChars(tag, 0);

    LOGD("notify message is: %s", s);

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

    LOGI("asctime() Date is: %s", ctime_0);
    LOGW("ctime() Date is: %s", ctime_1);

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

    jfloat f = a + b;

    LOGW("a + b is: %f", f);

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

    int x = 10;

    LOGE("number is: %d", x);

    return x;
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

/**
 * 字符串加密(当前无法使用)
 * Class:     com_myself_jnitestdemo_JniTest
 * Method:    getTheCiphertext
 * Signature: ()S
 */
JNIEXPORT jstring JNICALL
Java_com_myself_jnitestdemo_JniTest_getTheCiphertext(
        JNIEnv *env,
        jobject instance,
        jstring s_) {

    jstring key_s = env->NewStringUTF("a1b2c3d4");
    const char *key_s_c = env->GetStringUTFChars(key_s, 0);
    unsigned char *key = (unsigned char *) key_s_c;

    LOGI("key---> %s", key);

    const char *s = env->GetStringUTFChars(s_, 0);
    unsigned char *mingwen = (unsigned char *) s;

    LOGI("mingwen---> %s", mingwen);

    // TODO
    char miwen_hex[1024];
    char result[1024];
    //char miwen_hex[] = "8FEEEFE524F8B68DC1FCA2899AC1A6B82E636F6D";

//    AES aes(key);
//    aes.Cipher(mingwen, miwen_hex);
//    aes.InvCipher(miwen_hex, result);
    getchar();

    LOGI("mingwen: %s", s);
    LOGI("miwen_hex: %s", miwen_hex);

    LOGI("result: %s", s);

    return env->NewStringUTF(s);
}


#ifdef __cplusplus
}
#endif