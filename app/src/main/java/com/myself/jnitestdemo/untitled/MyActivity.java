package com.myself.jnitestdemo.untitled;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.myself.jnitestdemo.R;

public class MyActivity extends Activity {

    static {
        Log.d("onEvent", "load jni lib");
        System.loadLibrary("hello-jni");
    }

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Intent intent = new Intent(this, SDCardListenerService.class);
        startService(intent);

        init();
    }

    private native void init();
}