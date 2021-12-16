package com.example.webTester;

import android.content.Context;
import android.net.ConnectivityManager;

/**
 * Created by achmadi on 10/18/19.
 */
public class NetworkState {
    public static boolean connectionAvailable(Context context){
        ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        return connectivityManager.getActiveNetworkInfo() != null;
    }
}
