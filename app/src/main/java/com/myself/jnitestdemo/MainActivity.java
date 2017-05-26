package com.myself.jnitestdemo;

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.myself.jnitestdemo.base.AppInfoActivity;
import com.myself.jnitestdemo.base.BaseActivity;
import com.myself.jnitestdemo.base.FirInfoBean;
import com.myself.jnitestdemo.base.TotalApplication;

import butterknife.BindView;
import butterknife.OnClick;
import butterknife.OnLongClick;
import im.fir.sdk.FIR;
import im.fir.sdk.VersionCheckCallback;

import static com.myself.jnitestdemo.base.AppInfoActivity.BUNDLE_APP_INFO;

public class MainActivity extends BaseActivity {

    public static final String express = "葡萄科技";

    @BindView(R.id.tv_left)
    TextView mTvLeft;
    @BindView(R.id.tv_main)
    TextView mTvMain;
    @BindView(R.id.tv_right)
    TextView mTvRight;
    @BindView(R.id.sample_text)
    TextView mSampleText;
    @BindView(R.id.tv_text)
    TextView mTvText;
    @BindView(R.id.tv_add)
    TextView mTvAdd;
    @BindView(R.id.tv_int)
    TextView mTvInt;
    @BindView(R.id.tv_number)
    TextView mTvNumber;
    @BindView(R.id.tv_msg)
    TextView mTvMsg;
    @BindView(R.id.tv_jiami)
    TextView mTvJiami;
    @BindView(R.id.btn_test_fileprovider)
    Button mBtnTestFileprovider;

    private FirInfoBean mBean;

    @Override
    protected int getLayoutId() {
        return R.layout.activity_main;
    }

    @Override
    protected void onViewCreatedFinish(Bundle saveInstanceState) {
        getFirAppVersionInfo();

//        JniTest jniTest = new JniTest();
//        mSampleText.setText(jniTest.stringFromJNI());
//        mTvText.setText(jniTest.getAcquisitionTime());
//        float add = jniTest.getTwoNumbersAnd(5f, 12f);
//        mTvAdd.setText(String.valueOf(add));
//        int a = jniTest.getA();
//        mTvInt.setText(String.valueOf("a=" + a));
//        mTvNumber.setText(String.valueOf("number= " + jniTest.getStringFromNative()));
//        mTvMsg.setText(jniTest.getMessage().getData().toString());
//        String s = jniTest.getTheCiphertext(express);
//        mTvJiami.setText(String.valueOf("密文：" + s));

//        JniUtils jniUtils = new JniUtils();
//        String string = jniUtils.getCLanguageString();
//        mSampleText.setText(string);


    }

    @OnClick({R.id.tv_left, R.id.tv_right, R.id.btn_test_fileprovider})
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.tv_left:
//                mTvLeft.setText(5 / 3);
                break;
            case R.id.tv_right:
                Bundle bundle = new Bundle();
                bundle.putSerializable(BUNDLE_APP_INFO, mBean);
                startActivity(AppInfoActivity.class, bundle);
                break;
            case R.id.btn_test_fileprovider:
//                startActivity(FileProviderTestActivity.class);
                break;
        }
    }

    /**
     * 返回键
     *
     * @param keyCode
     * @param event
     * @return
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            return exit();
        }
        return super.onKeyDown(keyCode, event);
    }

    /**
     * Fir获取版本信息测试(FIR)
     */
    @OnLongClick(R.id.tv_main)
    public boolean getFirAppVersionInfo() {
        FIR.checkForUpdateInFIR(TotalApplication.FIR_API_TOKEN, new VersionCheckCallback() {
            @Override
            public void onSuccess(String versionJson) {
                Log.i("FIR", "check from fir.im success! " + "\n" + versionJson);
                mBean = new Gson().fromJson(versionJson, FirInfoBean.class);
                Log.d(TAG, "name------->" + mBean.getName() + "\n" +
                        "version----->" + mBean.getVersionShort() + "\n" +
                        "changelog--->" + mBean.getChangelog() + "\n" +
                        "installUrl-->" + mBean.getInstallUrl());
            }

            @Override
            public void onFail(Exception exception) {
                Log.i("FIR", "check fir.im fail! " + "\n" + exception.getMessage());
                Toast.makeText(getApplicationContext(), R.string.no_network_tips, Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onStart() {
                Toast.makeText(getApplicationContext(), "正在获取", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onFinish() {
                if (null != mBean)
                    Toast.makeText(getApplicationContext(), "当前版本：" + mBean.getVersionShort(), Toast.LENGTH_SHORT).show();
            }
        });
        return false;
    }
}
