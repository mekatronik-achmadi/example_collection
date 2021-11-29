package com.example.dinApp;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.media.Ringtone;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.text.method.ScrollingMovementMethod;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

public class MyActivity extends Activity {
    /**
     * Called when the activity is first created.
     */

    Button btnReq;
    Button btnNotif;
    Button btnStart;
    TextView txtAx;
    TextView txtAy;
    TextView txtAz;
    TextView txtMag;
    TextView txtMic;
    TextView txtFall;
    TextView txtFuzz;
    TextView txtOut;

    private Runnable datreq;
    Handler hreq;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        btnReq = (Button) findViewById(R.id.btnReq);
        btnNotif = (Button) findViewById(R.id.btnNotif);
        btnStart = (Button) findViewById(R.id.btnStart);
        txtAx = (TextView) findViewById(R.id.txtAx);
        txtAy = (TextView) findViewById(R.id.txtAy);
        txtAz = (TextView) findViewById(R.id.txtAz);
        txtMag = (TextView) findViewById(R.id.txtMag);
        txtMic = (TextView) findViewById(R.id.txtMic);
        txtFall = (TextView) findViewById(R.id.txtFall);
        txtFuzz = (TextView) findViewById(R.id.txtFuzz);
        txtOut = (TextView) findViewById(R.id.txtOut);
        txtOut.setMovementMethod(new ScrollingMovementMethod());

        hreq = new Handler();
        datreq = new Runnable() {
            @Override
            public void run() {
                txtOut.append("Trying to Request\n");
                MyClientTask mycl = new MyClientTask("192.168.4.1");
                mycl.execute();
                hreq.postDelayed(this,500);
            }
        };

        btnReq.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtOut.append("Trying to Request\n");
                MyClientTask mycl = new MyClientTask("192.168.4.1");
                mycl.execute();
            }
        });

        btnNotif.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showNotification();
            }
        });

        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtOut.append("...Data Request Start...\n");
                hreq.post(datreq);
                btnStart.setEnabled(false);
                btnNotif.setEnabled(false);
                btnReq.setEnabled(false);
            }
        });

        txtOut.append("Ready\n");
    }

    private void Pesan(String txtpesan) {
        Context context = getApplicationContext();
        int duration = Toast.LENGTH_LONG;

        Toast toast = Toast.makeText(context, txtpesan, duration);

        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    private void showNotification() {

        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        String MyText = "Peringatan";
        Notification mNotification = new Notification(R.drawable.ic_launcher, MyText, System.currentTimeMillis() );

        String MyNotificationTitle = "Nenek anda terjatuh!";
        String MyNotificationText  = "Tolong lihat Nenek anda";

        Intent MyIntent = new Intent(Intent.ACTION_VIEW);
        PendingIntent StartIntent = PendingIntent.getActivity(getApplicationContext(),0,MyIntent, PendingIntent.FLAG_CANCEL_CURRENT);

        mNotification.setLatestEventInfo(getApplicationContext(), MyNotificationTitle, MyNotificationText, StartIntent);

        int NOTIFICATION_ID = 1;
        notificationManager.notify(NOTIFICATION_ID , mNotification);

        try {
            Uri notifSnd = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_ALARM);
            Ringtone r = RingtoneManager.getRingtone(getApplicationContext(), notifSnd);
            r.play();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    @SuppressLint("StaticFieldLeak")
    public class MyClientTask extends AsyncTask<Void, Void, Void> {

        String hostIP;
        int str;
        StringBuilder strData = new StringBuilder();

        MyClientTask(String strIP) {
            hostIP = strIP;
        }

        @Override
        protected Void doInBackground(Void... arg0){
            Socket socket = null;
            DataInputStream dataInputStream = null;

            try {
                socket = new Socket(hostIP,80);

                dataInputStream = new DataInputStream(socket.getInputStream());

                while ((str = dataInputStream.read()) != -1) {
                    strData.append((char) str);
                }

            } catch (IOException e) {
                Pesan("e");
            } finally {
                if (socket != null) {
                    try {
                        socket.close();
                    } catch (IOException e) {
                        Pesan("e");
                    }
                }
                if (dataInputStream != null) {
                    try {
                        dataInputStream.close();
                    } catch (IOException e) {
                        Pesan("e");
                    }
                }
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            txtOut.append(strData.toString() + "\n");

            String resData = strData.toString().trim();

            if (resData.length() > 0) {
                String[] arrStrData = resData.split(":");

                if (arrStrData.length > 6) {
                    txtMic.setText(arrStrData[0].trim());
                    txtAx.setText(arrStrData[1].trim());
                    txtAy.setText(arrStrData[2].trim());
                    txtAz.setText(arrStrData[3].trim());
                    txtMag.setText(arrStrData[4].trim());
                    txtFuzz.setText(arrStrData[5].trim());
                    txtFall.setText(arrStrData[6].trim());

                    if(Integer.parseInt(arrStrData[6].trim())==1){
                        showNotification();
                    }

                }
            }

            super.onPostExecute(result);
        }
    }
}