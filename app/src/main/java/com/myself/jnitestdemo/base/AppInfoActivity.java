package com.myself.jnitestdemo.base;

import android.os.Bundle;
import android.widget.TextView;

import com.myself.jnitestdemo.R;
import com.myself.jnitestdemo.utils.AppUtils;
import com.myself.jnitestdemo.utils.DateUtils;
import com.myself.jnitestdemo.utils.FileUtils;
import com.myself.jnitestdemo.utils.StringUtils;

import butterknife.BindView;
import butterknife.OnClick;

public class AppInfoActivity extends BaseActivity {
    public static final String BUNDLE_APP_INFO = "BUNDLE_APP_INFO";

    @BindView(R.id.tv_left)
    TextView tv_left;
    @BindView(R.id.tv_main)
    TextView tv_main;
    @BindView(R.id.tv_right)
    TextView tv_right;

    @BindView(R.id.tv_appname)
    TextView tv_appname;
    @BindView(R.id.tv_version)
    TextView tv_version;
    @BindView(R.id.tv_versionShort)
    TextView tv_versionShort;
    @BindView(R.id.tv_fsize)
    TextView tv_fsize;
    @BindView(R.id.tv_updatetime)
    TextView tv_updatetime;
    @BindView(R.id.tv_changelog)
    TextView tv_changelog;
    @BindView(R.id.tv_update_url)
    TextView tv_update_url;
    @BindView(R.id.tv_installUrl)
    TextView tv_installUrl;

    private FirInfoBean mBean;
    private String mVersionName;


    @Override
    protected int getLayoutId() {
        return R.layout.activity_app_info;
    }

    @Override
    protected void onViewCreatedFinish(Bundle saveInstanceState) {
        mVersionName = AppUtils.getVersionName(mContext);

        mBean = (FirInfoBean) args.getSerializable(BUNDLE_APP_INFO);

        initView();
        upgrade();
    }

    @OnClick(R.id.tv_left)
    public void onBackClick() {
        finish();
    }

    private void upgrade() {
        if (mBean != null) {
            String versionShort = mBean.getVersionShort();
            try {
                if (!StringUtils.isEmpty(versionShort)) {
                    String substring = mBean.getVersionShort().substring(1);
                    Float aFloat0 = Float.valueOf(mVersionName.substring(1));
                    Float aFloat1 = Float.valueOf(substring);
                    if (aFloat0 < aFloat1)
                        UpgradeHelper.showUpdateDialog(this, false, mBean);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private void initView() {
        tv_right.setText(mVersionName);
        if (mBean != null) {
            tv_appname.setText(mBean.getName());
            tv_version.setText(mBean.getBuild());
            tv_versionShort.setText(mBean.getVersionShort());
            tv_fsize.setText(FileUtils.getFormatSize(mBean.getBinary().getFsize()));
            tv_updatetime.setText(DateUtils.millisecondToDate(mBean.getUpdated_at(), DateUtils.YMD_HMS_PATTERN));
            tv_changelog.setText(mBean.getChangelog());
            tv_update_url.setText(mBean.getUpdate_url());
            tv_installUrl.setText(mBean.getInstallUrl());
        }
    }
}
