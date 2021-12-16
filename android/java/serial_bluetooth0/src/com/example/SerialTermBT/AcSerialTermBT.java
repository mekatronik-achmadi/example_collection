package com.example.SerialTermBT;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.inputmethodservice.KeyboardView;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.UUID;

public class AcSerialTermBT extends Activity {
    /**
     * Called when the activity is first created.
     */
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private BluetoothAdapter btAdapter=null;
    private BluetoothSocket btSocket=null;
    private BluetoothDevice btDevice;
    String addressBT;

    final int RECIEVE_MESSAGE = 1;
    int Connected= 0;
    private StringBuilder sb = new StringBuilder();
    private ConThread mConThread;
    Handler h;

    Button btnConnect;
    Button btnSend;
    Button btnClear;
    EditText txtAddress;
    EditText txtSend;
    TextView txtData;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        btnConnect = (Button) findViewById(R.id.btnConnect);
        btnSend = (Button) findViewById(R.id.btnSend);
        btnClear = (Button) findViewById(R.id.btnClear);
        txtAddress= (EditText) findViewById(R.id.txtAddrr);
        txtSend=(EditText) findViewById(R.id.txtSend);
        txtData= (TextView) findViewById(R.id.txtData);

        h = new Handler(){
            public void handleMessage(Message msg){
                if(msg.what==RECIEVE_MESSAGE){
                    byte[] readbuf=(byte[])msg.obj;
                    String strIn= new String(readbuf,0,msg.arg1);

                    txtData.append(strIn);  //read existing in buffer
                    /*
                    sb.append(strIn);
                    int endline=sb.indexOf("\n");  //ending buffer characters

                    if(endline>0){
                        String sbView=sb.substring(0,endline);
                        sb.delete(0,sb.length());
                        txtData.setText(sbView);
                    } */
                }
            }
        };

        btnClear.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtData.setText("");txtSend.setText("");
            }
        });

        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                 mConThread.write(txtSend.getText().toString());
            }
        });

        btnConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tryConnect();
            }
        });
    }

    public void tryConnect(){
        if(Connected==1){return;}

        btAdapter=BluetoothAdapter.getDefaultAdapter();

        if(btAdapter==null){
            Toast.makeText(getBaseContext(),"BlueTooth Adapter tidak ketemu",Toast.LENGTH_LONG).show();
        } else{
            Intent btIntent=new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(btIntent,1);
        }

        addressBT=txtAddress.getText().toString();

        if(!(addressBT=="")){
            btDevice=btAdapter.getRemoteDevice(addressBT);
        }

        try {
            btSocket = createBluetoothSocket(btDevice);
        } catch (IOException e) {}

        btAdapter.cancelDiscovery();

        try{
            btSocket.connect();
        }catch (IOException e){
            try{
                btSocket.close();
            }catch (IOException e1){}
        }

        mConThread=new ConThread(btSocket);
        mConThread.start();
        Connected=1;
        btnConnect.setEnabled(false);
    }

    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        if(Build.VERSION.SDK_INT >= 10){
            try {
                final Method m = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
                return (BluetoothSocket) m.invoke(device, MY_UUID);
            } catch (Exception e) {}
        }
        return  device.createRfcommSocketToServiceRecord(MY_UUID);
    }

    private class ConThread extends Thread {
        private final InputStream mInStream;
        private final OutputStream mOutStream;

        public ConThread(BluetoothSocket socket) {
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            // Get the input and output streams, using temp objects because
            // member streams are final
            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) { }

            mInStream = tmpIn;
            mOutStream = tmpOut;
        }

        public void run() {
            byte[] buffer = new byte[256];  // buffer store for the stream
            int bytes; // bytes returned from read()

            // Keep listening to the InputStream until an exception occurs
            while (true) {
                try {
                    // Read from the InputStream
                    bytes = mInStream.read(buffer);		// Get number of bytes and message in "buffer"
                    h.obtainMessage(RECIEVE_MESSAGE, bytes, -1, buffer).sendToTarget();		// Send to message queue Handler
                } catch (IOException e) {
                    break;
                }
            }
        }

        /* Call this from the main activity to send data to the remote device */
        public void write(String message) {
            byte[] msgBuffer = message.getBytes();
            try {
                mOutStream.write(msgBuffer);
            } catch (IOException e) {}
        }
    }

}
