package com.myself.jnitestdemo.test;

import android.os.Bundle;
import android.widget.ImageView;

import com.myself.jnitestdemo.R;
import com.myself.jnitestdemo.base.BaseActivity;

import butterknife.BindView;

public class FileProviderTestActivity extends BaseActivity {

    @BindView(R.id.iv_image)
    ImageView ivImage;

    @Override
    protected int getLayoutId() {
        return R.layout.activity_file_provider_test;
    }

    @Override
    protected void onViewCreatedFinish(Bundle saveInstanceState) {
        //android 7.0+
//        File imagePath = new File(Context.getFilesDir(), "images");
//        File newFile = new File(imagePath, "default_image.jpg");
//        Uri contentUri = getUriForFile(getContext(), "com.mydomain.fileprovider", newFile);
        ivImage.setImageResource(R.drawable.image_1);
    }
}
