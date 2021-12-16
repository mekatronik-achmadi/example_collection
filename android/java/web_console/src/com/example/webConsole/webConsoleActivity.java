package com.example.webConsole;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class webConsoleActivity extends Activity {
    Button btnTest;
    Button btnSerial;
    TextView txtOut;
    WebView webHTML;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);

        btnTest = (Button) findViewById(R.id.btnTest);
        btnSerial = (Button) findViewById(R.id.btnSerial);
        txtOut = (TextView) findViewById(R.id.txtOut);
        webHTML = (WebView) findViewById(R.id.webHTML);

        webHTML.getSettings().setJavaScriptEnabled(true);
        webHTML.getSettings().setUseWideViewPort(true);
        webHTML.getSettings().setLoadWithOverviewMode(true);
        webHTML.getSettings().setSupportZoom(true);
        webHTML.getSettings().setBuiltInZoomControls(true);
        webHTML.getSettings().setSupportMultipleWindows(true);

        webHTML.setScrollBarStyle(View.SCROLLBARS_INSIDE_OVERLAY);
        webHTML.setBackgroundColor(Color.WHITE);

        btnTest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtOut.append("request a test\n");
                MyClientTask mct = new MyClientTask("192.168.4.1",3000,"");
                mct.execute();
            }
        });

        btnSerial.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtOut.append("request a serial test\n");
                MyClientTask mct = new MyClientTask("192.168.4.1",3000,"serial");
                mct.execute();
            }
        });

        txtOut.append("Ready\n");
    }

    @SuppressLint("StaticFieldLeak")
    public class MyClientTask extends AsyncTask<Void, Void, Void> {
        String dataReq;
        String strReq;
        String hostIP;
        int hostPort;
        int strRead;
        StringBuilder strBld = new StringBuilder();

        MyClientTask(String strIP, int intPort, String strDataReq){
            hostIP = strIP;
            hostPort = intPort;
            dataReq = strDataReq;
        }

        @Override
        protected Void doInBackground(Void... arg0){
            Socket socket = null;
            DataInputStream dataInputStream = null;
            DataOutputStream dataOutputStream = null;

            try{
                socket = new Socket(hostIP,hostPort);
                dataInputStream = new DataInputStream(socket.getInputStream());
                dataOutputStream = new DataOutputStream(socket.getOutputStream());

                strReq = "GET /";
                strReq += dataReq;
                strReq += " HTTP/1.1\r\n";
                byte[] byteReq = strReq.getBytes("8859_1");
                dataOutputStream.write(byteReq,0,byteReq.length);
                dataOutputStream.flush();

                while((strRead = dataInputStream.read()) != -1){
                    strBld.append((char) strRead);
                }
            }catch (IOException e){}
            finally{
                if(socket != null){
                    try {
                        socket.close();
                    }catch(IOException e1){}
                }
                if(dataInputStream != null){
                    try {
                        dataInputStream.close();
                    }catch(IOException e2){}
                }
                if(dataOutputStream != null){
                    try {
                        dataOutputStream.close();
                    }catch(IOException e2){}
                }
            }

            return null;
        }

        @Override
        protected void onPostExecute(Void result){
            txtOut.append(strBld.toString()+"\n");
            webHTML.loadData(strBld.toString(),"text/html; charset=utf-8", "UTF-8");
            super.onPostExecute(result);
        }
    }
}
