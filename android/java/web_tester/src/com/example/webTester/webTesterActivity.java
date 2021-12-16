package com.example.webTester;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.webkit.ValueCallback;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.TextView;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class webTesterActivity extends Activity {
    Button btnTest;
    Button btnSerial;
    Button btnInfo;
    Button btnClear;
    TextView txtOut;
    WebView webHTML;

    MyWebViewClient myWebViewClient;
    String hostIP = "192.168.4.1";
    String hostPort = "3000";

    String strHTML;
    int strHTMLstt;

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
        btnInfo = (Button) findViewById(R.id.btnInfo);
        btnClear = (Button) findViewById(R.id.btnClear);
        txtOut = (TextView) findViewById(R.id.txtOut);
        webHTML = (WebView) findViewById(R.id.webHTML);

        myWebViewClient = new MyWebViewClient();

        if(savedInstanceState != null){
            webHTML.restoreState(savedInstanceState);
        }
        else{
            webHTML.getSettings().setJavaScriptEnabled(true);
            webHTML.getSettings().setUseWideViewPort(true);
            webHTML.getSettings().setLoadWithOverviewMode(true);
            webHTML.getSettings().setSupportZoom(true);
            webHTML.getSettings().setBuiltInZoomControls(true);
            webHTML.getSettings().setSupportMultipleWindows(true);

            webHTML.setScrollBarStyle(View.SCROLLBARS_INSIDE_OVERLAY);
            webHTML.setBackgroundColor(Color.WHITE);

            webHTML.setWebChromeClient(new WebChromeClient(){
                @Override
                public void onProgressChanged(WebView view, int newProgress){
                    super.onProgressChanged(view, newProgress);
                    if(newProgress==100){
                        webHTML.evaluateJavascript("(function(){return window.document.body.outerHTML})();",
                                new ValueCallback<String>() {
                                    @Override
                                    public void onReceiveValue(String s) {
                                        if(strHTMLstt==0) {
                                            strHTML = removeUTFChars(s).toString();
                                            txtOut.append("HTML Data:\r\n" + strHTML  + "\r\n");
                                            strHTMLstt = 1;
                                        }
                                    }
                                }
                        );
                    }
                }
            });
        }

        webHTML.setWebViewClient(myWebViewClient);

        btnTest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HttpRequest(hostIP,hostPort,"");
                txtOut.append("Request Test Webpage\r\n");
            }
        });

        btnSerial.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HttpRequest(hostIP,hostPort,"serial");
                txtOut.append("Request Test Serial\r\n");
            }
        });

        btnInfo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HttpRequest(hostIP,hostPort,"infosta");
                txtOut.append("Request Station Info\r\n");
            }
        });

        btnClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtOut.setText("");
            }
        });

        txtOut.append("Ready\r\n");
    }

    public static StringBuffer removeUTFChars(String data) {
        Pattern p = Pattern.compile("\\\\u(\\p{XDigit}{4})");
        Matcher m = p.matcher(data);
        StringBuffer buf = new StringBuffer(data.length());
        while (m.find()) {
            String ch = String.valueOf((char) Integer.parseInt(m.group(1), 16));
            m.appendReplacement(buf, Matcher.quoteReplacement(ch));
        }
        m.appendTail(buf);
        return buf;
    }

    public void HttpRequest(String strIP, String strPort, String strReq){

        String strURL;

        strURL = "http://";

        strURL += strIP;
        strURL += ":";

        strURL += strPort;
        strURL += "/";

        strURL += strReq;

        try {
            if(NetworkState.connectionAvailable(webTesterActivity.this)){
                webHTML.loadUrl(strURL);
                strHTMLstt = 0;
            }
        }catch (Exception e){}
    }
}
