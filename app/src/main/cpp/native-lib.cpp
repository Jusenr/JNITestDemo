#include <jni.h>
#include <iostream>
#include <string>
#include <map>
#include <android/log.h>

using namespace std;


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

//从C语言的map转Java hashmap
jobject cMap2jHashMap(JNIEnv *env, std::map<char *, char *> c_map) {
    jclass jmapclass = env->FindClass("java/util/HashMap");
    jmethodID mid = env->GetMethodID(jmapclass, "<init>", "()V");
    jmethodID putmethod = env->GetMethodID(jmapclass, "put",
                                           "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jobject j_map = env->NewObject(jmapclass, mid);
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jstring encoding = env->NewStringUTF("utf-8");
    std::map<char *, char *>::iterator it;
    for (it = c_map.begin(); it != c_map.end(); it++) {
        char *key = it->first;
        jbyteArray keybytes = env->NewByteArray(strlen(key));
        env->SetByteArrayRegion(keybytes, 0, strlen(key), (jbyte *) key);
        jstring jkey = (jstring) env->NewObject(strClass, ctorID, keybytes, encoding);
        char *value = it->second;
        jbyteArray valuebytes = env->NewByteArray(strlen(value));
        env->SetByteArrayRegion(valuebytes, 0, strlen(value), (jbyte *) value);
        jstring jvalue = (jstring) env->NewObject(strClass, ctorID, valuebytes, encoding);
        env->CallVoidMethod(j_map, putmethod, jkey, jvalue);
    }
    return j_map;
}

//java hashmap转c map
std::map<char *, char *> jMap2cMap(JNIEnv *env, jobject jobj) {
    std::map<char *, char *> c_map;
    jclass jmapclass = env->FindClass("java/util/HashMap");
    jmethodID jkeysetmid = env->GetMethodID(jmapclass, "keySet", "()Ljava/util/Set;");
    jmethodID jgetmid = env->GetMethodID(jmapclass, "get",
                                         "(Ljava/lang/Object;)Ljava/lang/Object;");
    jobject jsetkey = env->CallObjectMethod(jobj, jkeysetmid);
    jclass jsetclass = env->FindClass("java/util/Set");
    jmethodID jtoArraymid = env->GetMethodID(jsetclass, "toArray", "()[Ljava/lang/Object;");
    jobjectArray jobjArray = (jobjectArray) env->CallObjectMethod(jsetkey, jtoArraymid);
    if (jobjArray == NULL) {
        LOGD("param is NULL");
    }
    jsize arraysize = env->GetArrayLength(jobjArray);
    int i = 0;
    for (i = 0; i < arraysize; i++) {
        jstring jkey = (jstring) env->GetObjectArrayElement(jobjArray, i);
        jstring jvalue = (jstring) env->CallObjectMethod(jobj, jgetmid, jkey);
        char *key = (char *) env->GetStringUTFChars(jkey, 0);
        char *value = (char *) env->GetStringUTFChars(jvalue, 0);
        c_map[key] = value;
    }
    return c_map;
}

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
 * Method:    generateSign
 * Signature: ()O
 */
JNIEXPORT jobject JNICALL
Java_com_myself_jnitestdemo_JniTest_generateSign(
        JNIEnv *env,
        jobject instance,
        jobject j_map,
        jstring secretkey) {


    map<char *, char *> name_score_map;
    name_score_map["LiMin"] = "88";
    name_score_map["ZiLinMi"] = "79";
    name_score_map["BoB"] = "92";
    name_score_map["Ding"] = "99";
    name_score_map["MoB"] = "86";
    name_score_map["Albert"] = "86";
    for (map<char *, char *>::iterator iter = name_score_map.begin();
         iter != name_score_map.end(); ++iter) {
    }


    jstring tag = env->NewStringUTF("Native-Lib");

    std::string hello = "JNI:cMap2jHashMap(env, name_score_map)";
//    std::string hello("JNI:Hello from C++");//另一种写法

    const char *s = env->GetStringUTFChars(tag, 0);

    LOGD("notify message is: %s", s);

//    return cMap2jHashMap(env, name_score_map);

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

    getchar();

    LOGI("mingwen: %s", s);
    LOGI("miwen_hex: %s", miwen_hex);

    LOGI("result: %s", s);

    return env->NewStringUTF(s);
}


#ifdef __cplusplus
}
#endif