package com.myself.jnitestdemo;

/**
 * Description:
 * Copyright  : Copyright (c) 2017
 * Email      : jusenr@163.com
 * Author     : Jusenr
 * Date       : 2017/05/26
 * Time       : 15:45.
 */

public class JniUtils {

    /**
     * Used to load the 'native-lib' library on application startup.
     */
    static {
        System.loadLibrary("jniutils");
    }

    public native String getCLanguageString();

}
