package com.myself.jnitestdemo;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

/**
 * Description: include JNI file
 * Copyright  : Copyright (c) 2016
 * Email      : jusenr@163.com
 * Company    : 葡萄科技
 * Author     : Jusenr
 * Date       : 2017/3/17 14:57.
 */

public class JniTest {

    /**
     * Used to load the 'native-lib' library on application startup.
     */
    static {
        System.loadLibrary("native-lib");
//        System.loadLibrary("JniTest");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();//本地方法

    public native String getAcquisitionTime();//本地方法

    public native float getTwoNumbersAnd(float a, float b);//本地方法

    public native String getTheCiphertext(String s);//本地方法


    int a;//本示例中将被修改的JAVA变量
    Handler handler;

    public JniTest() {
        if (handler == null)
            handler = new Handler();
        setUp();
    }

    public native void setUp();//本地方法

    public native static int getStringFromNative();//本地方法

    public int getA() {
        return a;
    }

    public Message getMessage() {
        return handler.obtainMessage(1);
    }

    public native void setA(int a);//本地方法

    public void notifyFiledChange() {//本示例中将被C/C++调用的JAVA方法
        Message message = new Message();
        Bundle bundle = new Bundle();
        bundle.putInt("a", a);
        message.setData(bundle);
        message.what = 1;
        handler.sendMessage(message);
    }

}
