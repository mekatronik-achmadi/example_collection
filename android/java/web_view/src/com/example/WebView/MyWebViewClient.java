package com.example.WebView;

import android.graphics.Bitmap;
import android.webkit.CookieManager;
import android.webkit.WebView;
import android.webkit.WebViewClient;

/**
 * Created by achmadi on 10/18/19.
 */
public class MyWebViewClient extends WebViewClient {

    String currentURL;
    int chURLstt=0;
    int onLoadURL=0;
    int onFinishedURL=0;

    @Override
    public boolean shouldOverrideUrlLoading(WebView view, String url){

        view.loadUrl(url);
        CookieManager.getInstance().setAcceptCookie(true);

        currentURL=url;
        chURLstt =1;

        return true;
    }

    @Override
    public void onPageStarted(WebView view, String url, Bitmap favicon) {
        super.onPageStarted(view, url,favicon);

        currentURL=url;
        chURLstt =1;
    }

    @Override
    public void onPageFinished(WebView view, String url) {
        super.onPageFinished(view, url);

        if(onFinishedURL==1) {
            currentURL = url;
            chURLstt = 1;
        }
    }

    @Override
    public void onLoadResource(WebView view, String url) {
        super.onLoadResource(view, url);

        if(onLoadURL==1) {
            currentURL = url;
            chURLstt = 1;
        }
    }
}
