package com.myself.jnitestdemo;

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
    public native String stringFromJNI();

    public native String getAcquisitionTime();

    public native float getTwoNumbersAnd(float a, float b);
}
