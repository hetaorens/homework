package xhB20030826.aty;
import xhB20030826.R;
import xhB20030826.view.BlueToothGoBangView;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothSocket;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AlertDialog;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


/**
 * 蓝牙对战Activity
 */
public class BlueToothGameAty extends Activity implements BlueToothGoBangView.BlueToothActionListner {
    public BlueToothGameAty blueToothGameAty =  this;
    private static BlueToothGoBangView gbv;
    private TextView textView;

    private Button shuaxin;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.bluetoothgame_layout);
        blueToothGameAty = this;
        initView();
    }

    private void initView() {

        gbv = (BlueToothGoBangView) this.findViewById(R.id.bluetooth_gobangview);
        textView = (TextView) findViewById(R.id.bluetooth_text);

        shuaxin = (Button) findViewById(R.id.bluetooth_btn2);

        gbv.setTextView(textView);


        gbv.setActionCallbak(this);


        if (faqi == false) {
            showdialog();
        }
    }





    //数据传输线程
    static ConnectedThread connectedThread;

    //初始化线程来传输或接收数据

    public static boolean faqi = false;

    /**
     * 连接蓝牙socket方法
     *
     * @param socket
     * @param faqi   是否为发起方
     */
    public void manageConnectedSocket(final BluetoothSocket socket, final Boolean faqi) {
        this.faqi = faqi;
        //在一个线程中执行数据传输
        connectedThread = new ConnectedThread(socket);
        connectedThread.start();
        if (faqi == true) {
            String temp = "TIAOZHAN";
            connectedThread.write(temp.getBytes());
        }
    }

    @Override
    public void onPutChess(String temp) {
        Log.d("whalea", "发送给对方我下的棋" + temp);
        connectedThread.write(temp.getBytes());
    }

    @Override
    public void onBtnPress(int i) {
        String command;
        if (i == 0) {
            //如果是悔棋
            command = "HUIQI";
            connectedThread.write(command.getBytes());
        } else {
            //如果是重玩
            command = "REFRESH";
            connectedThread.write(command.getBytes());

        }
    }

    public void chushihua(BlueToothGameAty blueToothGameAty) {
    }

    private AlertDialog.Builder mydialog;

    public void showdialog() {
        //收到挑战
        mydialog = new AlertDialog.Builder(BlueToothGameAty.this);
        mydialog.setMessage("收到新的挑战，是否接受？")
                .setCancelable(false)
                .setPositiveButton("yes", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        dialog.cancel();
                    }
                })
                .setNegativeButton("no", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        String wold = "JUJVE";
                        connectedThread.write(wold.getBytes());

                        Intent i = new Intent(BlueToothGameAty.this, InitAty.class);
                        //设置从右边出现
                        BlueToothGameAty.this.overridePendingTransition(R.anim.initactivity_open, 0);
                        startActivity(i);
                        dialog.cancel();
                    }
                });
        AlertDialog alert = mydialog.create();
        alert.show();


    }

    /**
     * 连接的线程
     */
    private class ConnectedThread extends Thread {
        //传入的socket
        private final BluetoothSocket mmSocket;
        //输入流
        private final InputStream mmInStream;
        //输出流
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            //得到输入输出流，因为成员变量流是final的所以这里要用temp传递
            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }

        public void run() {
            while (true) {
                if (!mmSocket.isConnected()) {
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Intent i = new Intent(BlueToothGameAty.this, InitAty.class);
                            //设置从右边出现
                            BlueToothGameAty.this.overridePendingTransition(R.anim.initactivity_open, 0);
                            startActivity(i);
                        }
                    });
                }

                //得到输入输出流
                DataInputStream datains = new DataInputStream(mmInStream);
                String command = null;
                try {
                    command = datains.readUTF();

                } catch (IOException e) {
                    e.printStackTrace();
                }
                final String finalCommand = command;
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if ((finalCommand != null) && (finalCommand.equals("TIAOZHAN"))) {
                          //  showdialog();
                            Message message = new Message();
                            message.what = 1;
                            mhandler.sendMessageDelayed(message,2000);
                            Log.d("whalea", "收到挑战辣");
                        } else if (finalCommand.equals("JUJVE")) {
                            try {
                                mmSocket.close();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            Intent i = new Intent(BlueToothGameAty.this, InitAty.class);
                            //设置从右边出现
                            BlueToothGameAty.this.overridePendingTransition(R.anim.initactivity_open, 0);
                            startActivity(i);
                        } else {
                            gbv.xiaqi(finalCommand);
                        }
                    }
                });
            }
        }

        /* Call this from the main activity to send data to the remote device */
        public void write(byte[] bytes) {
            try {
                OutputStream out = mmSocket.getOutputStream();
                DataOutputStream dataout = new DataOutputStream(out);
                //发送给服务器需要下载的文件和断点
                String temp = new String(bytes, "utf-8");
                dataout.writeUTF(temp);
                Log.d("whalea", temp);
            } catch (IOException e) {
                Log.d("whalea", "写不出的原因:" + e.getMessage());
            }
        }

     /*    public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) { }
        }*/
    }


    @SuppressLint("HandlerLeak")
    public Handler mhandler = new Handler(){
        @SuppressLint("HandlerLeak")
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            //Toast.makeText(BlueToothGameAty.this, "收到挑战！", Toast.LENGTH_LONG).show();
        }
    };
}

