package com.myself.jnitestdemo.base;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import com.myself.jnitestdemo.utils.CrashHandler;

import butterknife.ButterKnife;
import im.fir.sdk.FIR;


/**
 * Description:
 * Copyright  : Copyright (c) 2016
 * Email      : jusenr@163.com
 * Company    : 葡萄科技
 * Author     : Jusenr
 * Date       : 2016/12/27 16:05.
 */

public class TotalApplication extends Application {
    private static final String TAG = "Jni-Test";
    public static final String FIR_API_TOKEN = "1b91eb3eaaea5f64ed127882014995dd";
    public static Context mContext;
    private static boolean isDebug;

    @Override
    public void onCreate() {
        super.onCreate();
        mContext = getApplicationContext();
        //是否Debug环境
        isDebug = configEnvironment();
        //ButterKnife的Debug模式
        ButterKnife.setDebug(isDebug);
        //Fir-SDk配置
        FIR.init(this);

        //捕捉系统崩溃异常
        CrashHandler.instance().init(new CrashHandler.OnCrashHandler() {
            @Override
            public void onCrashHandler(Throwable ex) {
                onCrash(ex);
            }
        });
    }

    public static Context getInstance() {
        return mContext;
    }

    /**
     * 网络环境切换
     *
     * @return
     */
    protected boolean configEnvironment() {

        return false;
    }

    /**
     * 捕捉到异常就退出App
     *
     * @param ex 异常信息
     */
    protected void onCrash(Throwable ex) {
        Log.e(TAG, "APP崩溃了,错误信息是" + ex.getMessage());
        ex.printStackTrace();

        ActivityManager.getInstance().finishAllActivity();
    }
}
