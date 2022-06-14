package xhB20030826.aty;
import xhB20030826.R;
import xhB20030826.view.RenjiGobangView;

import android.app.Activity;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;

import android.view.WindowManager;
import android.widget.Button;

import android.widget.ImageView;
import android.widget.TextView;



public class RenjiGameAty extends Activity implements RenjiGobangView.OnWinListener {
    public   RenjiGameAty renjiGameAty = this;
    RenjiGobangView gbv;
    TextView textView;
    Button huiqi;
    Button shuaxin;

    ImageView renjibeijing;
    AnimationDrawable animationDrawable;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.renjigame_layout);
        renjiGameAty = this;
        initView();
    }

    private void initView() {

        gbv = (RenjiGobangView) this.findViewById(R.id.gobangview);
        textView = (TextView) findViewById(R.id.text);
        renjibeijing = (ImageView) findViewById(R.id.renjibeijingdongtu);
        renjibeijing.setImageResource(R.drawable.renjibackground_animation);
        animationDrawable = (AnimationDrawable) renjibeijing.getDrawable();
        animationDrawable.start();

        shuaxin = (Button) findViewById(R.id.btn2);


        gbv.setTextView(textView);
        gbv.setButtons(shuaxin);

        gbv.setWinListner(this);
    }



    @Override
    public void onWin(int i) {
        final AlertDialog mydialog= new AlertDialog.Builder(RenjiGameAty.this).create();
        if(i==1) {
            //如果黑棋赢了
            mydialog.show();
            mydialog.getWindow().clearFlags(WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM);
            mydialog.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_VISIBLE);
            mydialog.getWindow().setContentView(R.layout.win_dialog);


            TextView showview = (TextView) mydialog.getWindow().findViewById(R.id.windialog_tv);
            showview.setText("YOU WIN");

            mydialog.getWindow()
                    .findViewById(R.id.windialog_cancle)
                    .setOnClickListener(v -> mydialog.dismiss());
        }else {
            //如果白棋赢了
            mydialog.show();
            mydialog.getWindow().setContentView(R.layout.lose_dialog);
            mydialog.getWindow()
                    .findViewById(R.id.losedialog_submit)
                    .setOnClickListener(v -> mydialog.dismiss());
        }
    }




}
