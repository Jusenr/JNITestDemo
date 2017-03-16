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

    const char *tag_0 = LOG_TAG;

    std::string hello = "Hello from C++";

//    LOGE("notify message is:", hello);

    return env->NewStringUTF(hello.c_str());
}

/*jstring
Java_com_myself_jnitestdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject thiz) {

    jstring tag = env->NewStringUTF(LOG_TAG);

    //初始化log
//    LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &b_IS_COPY),
//              (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "init OK"), &b_IS_COPY));

    std::string init_OK = "init OK";

    LOG_DEBUG(env->GetStringUTFChars(tag, &b_IS_COPY),
              env->GetStringUTFChars(env->NewStringUTF(init_OK.c_str()),
                                     &b_IS_COPY));

    LOG_INFO(env->GetStringUTFChars(tag, &b_IS_COPY), env->GetStringUTFChars(tag, &b_IS_COPY));

    LOG_WARN(env->GetStringUTFChars(tag, &b_IS_COPY),
             env->GetStringUTFChars(env->NewStringUTF(init_OK.c_str()),
                                    &b_IS_COPY));

    //fork子进程，以执行轮询任务
    pid_t pid = fork();

    std::string fork_failed = "fork failed !!!";

    if (pid < 0) {
        //出错log
        LOG_ERROR(env->GetStringUTFChars(tag, &b_IS_COPY),
                  env->GetStringUTFChars(env->NewStringUTF(fork_failed.c_str()),
                                         &b_IS_COPY));

    }
    else if (pid == 0) {
        //子进程注册"/data/data/pym.test.uninstalledobserver"目录监听器
        int fileDescriptor = inotify_init();

        std::string inotify_init = "inotify_init failed !!!";

        if (fileDescriptor < 0) {
            LOG_DEBUG(env->GetStringUTFChars(tag, &b_IS_COPY),
                      env->GetStringUTFChars(env->NewStringUTF(inotify_init.c_str()),
                                             &b_IS_COPY));
            exit(1);
        }

        int watchDescriptor;
        watchDescriptor = inotify_add_watch(fileDescriptor, "/data/data/com.myself.jnitestdemo",
                                            IN_DELETE);

        std::string inotify_add_watch = "inotify_add_watch failed !!!";

        if (watchDescriptor < 0) {
            LOG_DEBUG(env->GetStringUTFChars(tag, &b_IS_COPY),
                      env->GetStringUTFChars(env->NewStringUTF(inotify_add_watch.c_str()),
                                             &b_IS_COPY));
            exit(1);
        }

        //分配缓存，以便读取event，缓存大小=一个struct inotify_event的大小，这样一次处理一个event
        void *p_buf = malloc(sizeof(struct inotify_event));

        std::string malloc_failed = "malloc failed !!!";

        if (p_buf == NULL) {
            LOG_DEBUG(env->GetStringUTFChars(tag, &b_IS_COPY),
                      env->GetStringUTFChars(env->NewStringUTF(malloc_failed.c_str()),
                                             &b_IS_COPY));

            exit(1);
        }

        std::string start_observer = "start observer !";

        //开始监听
        LOG_DEBUG(env->GetStringUTFChars(tag, &b_IS_COPY),
                  env->GetStringUTFChars(env->NewStringUTF(start_observer.c_str()),
                                         &b_IS_COPY));
        size_t readBytes = read(fileDescriptor, p_buf, sizeof(struct inotify_event));

        //read会阻塞进程，走到这里说明收到目录被删除的事件，注销监听器
        free(p_buf);
        inotify_rm_watch(fileDescriptor, IN_DELETE);

        std::string uninstalled = "uninstalled !";

        //目录不存在log
        LOG_DEBUG(env->GetStringUTFChars(tag, &b_IS_COPY),
                  env->GetStringUTFChars(env->NewStringUTF(uninstalled.c_str()),
                                         &b_IS_COPY));

        //执行命令am start -a android.intent.action.VIEW -d http://shouji.360.cn/web/uninstall/uninstall.html
        // execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d", "http://shouji.360.cn/web/uninstall/uninstall.html", (char *)NULL);
        //4.2以上的系统由于用户权限管理更严格，需要加上 --user 0
        execlp("am", "am", "start", "--user", "0", "-a", "android.intent.action.VIEW", "-d",
               "https://www.google.com", (char *) NULL);

    }
    else {
        //父进程直接退出，使子进程被init进程领养，以避免子进程僵死
    }

    std::string hello = "Hello from JNI !";

    return env->NewStringUTF(hello.c_str());
}*/

