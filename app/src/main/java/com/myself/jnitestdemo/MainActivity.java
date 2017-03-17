package com.myself.jnitestdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
//        System.loadLibrary("hello-jni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView sample_text = (TextView) findViewById(R.id.sample_text);
        TextView tv_text = (TextView) findViewById(R.id.tv_text);
        sample_text.setText(stringFromJNI());
//        tv_text.setText(initJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

//    public native String initJNI();
//    public native String stringFromJNI();
}
