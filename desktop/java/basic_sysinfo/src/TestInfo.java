import javax.swing.*;
import java.util.Enumeration;
import java.util.Properties;

/**
 * Created by achmadi on 10/20/18.
 */
public class TestInfo {
    private String msginfo;

    public TestInfo(){}

    private void InfoMessage(){
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
//        msginfo += "User Home: " + System.getProperty("user.home") + "\n";
//        msginfo += "\n";

        msgprop = System.getProperties();
        msginfo += msgprop.toString();
        msginfo += "\n\n";

        Enumeration<String> lstprop = (Enumeration<String>) msgprop.propertyNames();
        while(lstprop.hasMoreElements()){
            String nprop = lstprop.nextElement();
            msginfo += nprop;
            msginfo += " : ";
            msginfo += System.getProperty(nprop);
            msginfo += "\n\n";
        }

        msginfo += "more info: \n";
        msginfo += "$> java -XshowSettings:all \n";
    }

    public void ConsoleInfo(){
        InfoMessage();
        System.out.println("============================");
        System.out.print(msginfo);
        System.out.println("============================");
    }

    public void DialogInfo(){
        InfoMessage();
        JOptionPane.showMessageDialog(null,
                msginfo,
                "System Information",
                JOptionPane.INFORMATION_MESSAGE);
    }
}
