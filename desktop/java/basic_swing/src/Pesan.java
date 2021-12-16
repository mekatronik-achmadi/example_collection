import javax.swing.*;

/**
 * Created by achmadi on 10/20/18.
 */
public class Pesan {
    public Pesan(){}

    void PesanOK(){
        JOptionPane.showMessageDialog(null,
                "Program says OK",
                "OK",
                JOptionPane.WARNING_MESSAGE);
    }

    void PesanCancel(){
        JOptionPane.showMessageDialog(null,
                "Program says Cancel",
                "Cancel",
                JOptionPane.ERROR_MESSAGE
        );
    }

    void PesanTampil(String input){
        JOptionPane.showMessageDialog(null,
                input,
                "Info",
                JOptionPane.INFORMATION_MESSAGE
        );
    }
}
