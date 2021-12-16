package com.example.TestInfo;

import java.util.Enumeration;
import java.util.Properties;

/**
 * Created by achmadi on 10/21/18.
 */
public class SysInfo {
    public SysInfo(){}

    public String InfoMessage(){

        String msginfo;
        Properties msgprop;

        msginfo = "System Information \n";
        msginfo += "\n";

//        msginfo += "Java Version: " + System.getProperty("java.version") + "\n";
//        msginfo += "Java Vendor: " + System.getProperty("java.vendor") + "\n";
//        msginfo += "JVM Name: " + System.getProperty("java.vm.name") + "\n";
//        msginfo += "JVM Version: " + System.getProperty("java.vm.version") + "\n";
//        msginfo += "Java Path: " + System.getProperty("java.home") + "\n";
//        msginfo += "\n";
//
//        msginfo += "OS Name: " + System.getProperty("os.name") + "\n";
//        msginfo += "OS Arch: " + System.getProperty("os.arch") + "\n";
//        msginfo += "OS Version: " + System.getProperty("os.version") + "\n";
//        msginfo += "Encoding: " + System.getProperty("file.encoding") + "\n";
//        msginfo += "\n";
//
//        msginfo += "User Name: " + System.getProperty("user.name") + "\n";
//        msginfo += "User Dir : " + System.getProperty("user.dir") + "\n";
//        msginfo += "\n";

        msgprop = System.getProperties();
        msginfo += msgprop.toString();
        msginfo += "\n\n";

        Enumeration<String> lstprop = (Enumeration<String>) msgprop.propertyNames();
        while (lstprop.hasMoreElements()){
            String nprop = lstprop.nextElement();
            msginfo += nprop;
            msginfo += " : ";
            msginfo += System.getProperty(nprop);
            msginfo += "\n\n";
        }

        return msginfo;
    }

}
