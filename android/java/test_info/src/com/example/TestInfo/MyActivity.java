package com.example.TestInfo;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MyActivity extends Activity {
    private static SysInfo nfo;

    Button btnConsole;
    Button btnDialog;
    TextView txtOut;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        btnConsole = (Button) findViewById(R.id.btnConsole);
        btnDialog = (Button) findViewById(R.id.btnDialog);
        txtOut = (TextView) findViewById(R.id.txtOut);
        txtOut.setMovementMethod(new ScrollingMovementMethod());

        nfo = new SysInfo();

        btnDialog.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Pesan(nfo.InfoMessage());
            }
        });

        btnConsole.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtOut.setText(nfo.InfoMessage());
            }
        });
    }

    private void Pesan(String txtpesan){
        Context context = getApplicationContext();
        int duration = Toast.LENGTH_LONG;

        Toast toast = Toast.makeText(context,txtpesan,duration);

        toast.setGravity(Gravity.CENTER,0,0);
        toast.show();
    }
}
