package com.test.SerialBT;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.view.Window;
import android.widget.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;

public class SerialActivity extends Activity implements AdapterView.OnItemSelectedListener{
    /**
     * Called when the activity is first created.
     */
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static final int REQUEST_ENABLE_BT = 1;
    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private BluetoothDevice btDevice;
    String addressBT;

    final int RECIEVE_MESSAGE = 1;
    int sttConnected= 0;
    private StringBuilder stb = new StringBuilder();
    Handler hRecieve;
    connThread connThd;
    String endline = "\r\n";

    Button btnConnect;
    Button btnClear;
    Button btnQuit;
    Button btnSend;
    Button btnScan;
    TextView txtConsole;
    Spinner lstAddress;
    EditText txtSend;
    List<String> btList;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);

        btnConnect = (Button) findViewById(R.id.btnConnect);
        btnClear = (Button) findViewById(R.id.btnClear);
        btnQuit = (Button) findViewById(R.id.btnQuit);
        btnSend = (Button) findViewById(R.id.btnSend);
        btnScan = (Button) findViewById(R.id.btnScan);
        txtConsole = (TextView) findViewById(R.id.txtConsole);
        lstAddress = (Spinner) findViewById(R.id.lstAddress);
        txtSend = (EditText) findViewById(R.id.txtSend);

        lstAddress.setOnItemSelectedListener(this);

        txtConsole.setMovementMethod(new ScrollingMovementMethod());

        hRecieve = new Handler(){
            public void handleMessage(Message msg){
                if(msg.what == RECIEVE_MESSAGE){
                    byte[] readbuf = (byte[]) msg.obj;
                    String strIn = new String(readbuf,0,msg.arg1);
                    txtConsole.append(strIn);
                }
            }
        };

        btnClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtConsole.setText("");
            }
        });

        btnConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(sttConnected == 0 ){ tryConnect(); }
                else{ tryDisconnect(); }
            }
        });

        btnQuit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tryDisconnect();
                System.exit(0);
            }
        });

        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String outString = txtSend.getText().toString();
                if(sttConnected==1) {
                    if(!(outString == "")) {
                        connThd.write(outString  + endline);
                        txtConsole.append(outString + endline);
                    }
                }
                else{ Toast.makeText(getBaseContext(),"Serial Bluetooth not connected",Toast.LENGTH_SHORT).show(); }
            }
        });

        btnScan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tryScan();
            }
        });

        tryScan();
        txtConsole.setText("Choose Address then Click Connect\n");
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id){}
    public void onNothingSelected(AdapterView<?> arg0){}

    public void tryScan(){
        txtConsole.append("Scanning available Paired Devices\n");

        checkBT();

        Set<BluetoothDevice> btPaired = btAdapter.getBondedDevices();
        btList = new ArrayList<String>();
        for(BluetoothDevice bt:btPaired){ btList.add(bt.getAddress()+" ("+bt.getName()+")");}

        ArrayAdapter<String> arrbtList = new ArrayAdapter<String>(getBaseContext(),android.R.layout.simple_spinner_item,btList);
        arrbtList.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        lstAddress.setAdapter(arrbtList);

        txtConsole.append("Scan Finished\n");
    }

    public void tryConnect(){
        if(sttConnected==1){return;}

        checkBT();

        String strItem = lstAddress.getSelectedItem().toString();
        String[] strSplit = strItem.split(" ");
        addressBT = strSplit[0];

        txtConsole.append("Trying to connect to "+strSplit[1]+"\n");

        if(!(addressBT == "")){ btDevice = btAdapter.getRemoteDevice(addressBT); }

        try{
            btSocket = createBTsocket(btDevice);
        }catch (IOException e){}

        btAdapter.cancelDiscovery();

        try {
            btSocket.connect();
        }catch (IOException e){
            try {
                btSocket.close();
            }catch (IOException e1){}
        }

        connThd = new connThread(btSocket);
        connThd.start();
        sttConnected = 1;
        btnConnect.setText("Disconnect");
        txtConsole.append("Serial Bluetooth Connected\n");
    }

    public void tryDisconnect(){
        try {
            btSocket.close();
        }catch (IOException e1){}

        btnConnect.setText("Connect");
        sttConnected = 0;
        txtConsole.append("Serial Bluetooth Disconnected\n");
    }

    private void checkBT(){
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        if(btAdapter==null){Toast.makeText(getBaseContext(),"No Bluetooth adapter found",Toast.LENGTH_SHORT).show();}
        else{
            if(!btAdapter.isEnabled()) {
                Intent btIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(btIntent, REQUEST_ENABLE_BT);
            }
        }
    }

    private BluetoothSocket createBTsocket(BluetoothDevice device) throws IOException{
        if(Build.VERSION.SDK_INT >= 10){
            try {
                final Method mthd = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] {UUID.class});
                return (BluetoothSocket) mthd.invoke(device,MY_UUID);
            }catch (Exception e){}
        }
        return device.createRfcommSocketToServiceRecord(MY_UUID);
    }

    private class connThread extends Thread{
        private final InputStream inStream;
        private final OutputStream outStream;

        public connThread(BluetoothSocket socket){
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try{
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            }catch(IOException e){}

            inStream = tmpIn;
            outStream = tmpOut;
        }

        public void run(){
            byte[] buffer = new byte[256];
            int bytes;

            while(true){
                try{
                    bytes = inStream.read(buffer);
                    hRecieve.obtainMessage(RECIEVE_MESSAGE, bytes, -1,buffer).sendToTarget();
                }catch (IOException e){break;}
            }
        }

        public void write(String message){
            byte[] msgBuffer = message.getBytes();
            try {
                outStream.write(msgBuffer);
            }catch (IOException e){}
        }
    }
}
