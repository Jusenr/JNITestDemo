//
// Email      : jusenr@163.com
// Author     : Jusenr
// Date       : 2017/05/26
// Time       : 16:37.
//

#include "com_myself_jnitestdemo_JniUtils.h"
/*
 * Class:     com_myself_jnitestdemo_JniUtils
 * Method:    getCLanguageString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_com_myself_jnitestdemo_JniUtils_getCLanguageString(
        JNIEnv *env,
        jobject obj) {
    return (*env)->NewStringUTF(env, "This just a test for Android Studio NDK JNI developer!");
}

