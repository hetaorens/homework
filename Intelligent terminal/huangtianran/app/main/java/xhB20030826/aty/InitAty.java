package xhB20030826.aty;
import xhB20030826.R;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;



public class InitAty extends Activity {
    private Button init_renjibtn;
    private Button init_lanyabtn;

    private InitButtonListener initButtonListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.init_layout);
        //设置沉浸式标题栏
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            getWindow().addFlags(
                    WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            getWindow().addFlags(
                    WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
        }
        initView();
    }

    private void initView() {
        init_renjibtn = (Button) findViewById(R.id.init_renjibtn);
        init_lanyabtn = (Button) findViewById(R.id.init_lanyabtn);


        initButtonListener = new InitButtonListener();
        init_renjibtn.setOnClickListener(initButtonListener);
        init_lanyabtn.setOnClickListener(initButtonListener);

    }


    private class InitButtonListener implements View.OnClickListener{
        Intent i ;

        @SuppressLint("NonConstantResourceId")
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.init_renjibtn:
                    i = new Intent(InitAty.this,RenjiGameAty.class);
                    //设置从右边出现
                    InitAty.this.overridePendingTransition(R.anim.initactivity_open, 0);
                    i.putExtra("flag",2);
                    startActivity(i);
                break;

                case R.id.init_lanyabtn:
                    i = new Intent(InitAty.this,BlueToothFindOthersAty.class);
                    //设置从右边出现
                    InitAty.this.overridePendingTransition(R.anim.initactivity_open, 0);
                    startActivity(i);
                break;


            }
        }
    }
    long lastBackPressed = 0;
    @Override
    public void onBackPressed() {
        //当前时间
        long currentTime = System.currentTimeMillis();
        if (currentTime - lastBackPressed < 2000) {
            super.onBackPressed();
        } else {
            Toast.makeText(this, "再按一次退出程序", Toast.LENGTH_SHORT).show();
        }
        lastBackPressed = currentTime;
    }
}
