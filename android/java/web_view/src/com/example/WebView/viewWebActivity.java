package com.example.WebView;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.Window;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ProgressBar;
import android.widget.Toast;

public class viewWebActivity extends Activity {
    /**
     * Called when the activity is first created.
     */

    WebView webView;
    EditText txtURL;
    ProgressBar barLoad;
    ImageButton btnGo,btnBack,btnNext,btnStop,btnReload,btnHome;

    String urlHome = "https://duckduckgo.com";
    String strURL;
    Handler chURL_hndl;
    Runnable chRUL_run;

    MyWebViewClient myWebViewClient;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);

        webView = (WebView) findViewById(R.id.webView);
        txtURL = (EditText) findViewById(R.id.txtURL);
        barLoad = (ProgressBar) findViewById(R.id.barLoad);
        btnGo = (ImageButton) findViewById(R.id.btnGo);
        btnBack = (ImageButton) findViewById(R.id.btnBack);
        btnNext = (ImageButton) findViewById(R.id.btnNext);
        btnStop = (ImageButton) findViewById(R.id.btnStop);
        btnHome = (ImageButton) findViewById(R.id.btnHome);
        btnReload = (ImageButton) findViewById(R.id.btnReload);

        myWebViewClient = new MyWebViewClient();
        myWebViewClient.onLoadURL=0;
        myWebViewClient.onFinishedURL=0;

        barLoad.setMax(100);
        barLoad.setVisibility(ProgressBar.VISIBLE);

        if(savedInstanceState != null){
            webView.restoreState(savedInstanceState);
        }
        else{
            webView.getSettings().setJavaScriptEnabled(true);
            webView.getSettings().setUseWideViewPort(true);
            webView.getSettings().setLoadWithOverviewMode(true);
            webView.getSettings().setSupportZoom(true);
            webView.getSettings().setBuiltInZoomControls(true);
            webView.getSettings().setSupportMultipleWindows(true);

            webView.setScrollBarStyle(View.SCROLLBARS_INSIDE_OVERLAY);
            webView.setBackgroundColor(Color.WHITE);

            webView.setWebChromeClient(new WebChromeClient(){
                @Override
                public void onProgressChanged(WebView view, int newProgress){
                    super.onProgressChanged(view,newProgress);

                    barLoad.setProgress(newProgress);
                    if(barLoad.getVisibility() == ProgressBar.GONE){
                        barLoad.setVisibility(ProgressBar.VISIBLE);
                    }
                    if(newProgress == 100){
                        barLoad.setProgress(0);
                    }
                }
            });
        }

        webView.setWebViewClient(myWebViewClient);
        btnGo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    if(!NetworkState.connectionAvailable(viewWebActivity.this)){
                        Toast.makeText(viewWebActivity.this, R.string.check_connection, Toast.LENGTH_SHORT).show();
                    }
                    else{
                        InputMethodManager inputMethodManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                        inputMethodManager.hideSoftInputFromWindow(txtURL.getWindowToken(),0);

                        if(txtURL.getText().toString().contains("http")){
                            strURL = txtURL.getText().toString();
                        }
                        else{
                            strURL = "http://" + txtURL.getText().toString();
                        }

                        webView.loadUrl(strURL);
                    }
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        });

        btnBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(webView.canGoBack()){
                    webView.goBack();
                }
            }
        });

        btnNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(webView.canGoForward()){
                    webView.goForward();
                }
            }
        });

        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                webView.stopLoading();
            }
        });

        btnReload.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                webView.reload();
            }
        });

        btnHome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                webView.loadUrl(urlHome);
            }
        });

        chURL_hndl = new Handler();
        chRUL_run = new Runnable() {
            @Override
            public void run() {
                if(myWebViewClient.chURLstt==1){
                    txtURL.setText(myWebViewClient.currentURL);
                    myWebViewClient.chURLstt=0;
                }
                chURL_hndl.postDelayed(this,100);
            }
        };
        chURL_hndl.post(chRUL_run);

        webView.loadUrl(urlHome);
    }
}
