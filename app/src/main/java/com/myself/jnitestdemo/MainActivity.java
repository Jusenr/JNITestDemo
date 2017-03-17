package com.myself.jnitestdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView sample_text = (TextView) findViewById(R.id.sample_text);
        TextView tv_text = (TextView) findViewById(R.id.tv_text);
        TextView tv_add = (TextView) findViewById(R.id.tv_add);

        JniTest jniTest = new JniTest();
        sample_text.setText(jniTest.stringFromJNI());
        tv_text.setText(jniTest.getAcquisitionTime());
        float add = jniTest.getTwoNumbersAnd(5f, 12f);
        tv_add.setText(String.valueOf(add));
    }
}
