import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by achmadi on 10/20/18.
 */
public class frmInfo {
    private JPanel pnlInfo;
    private JButton btnConsole;
    private JButton btnDialog;

    private static TestInfo nfo;

    public frmInfo(){
        nfo = new TestInfo();

        btnConsole.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                nfo.ConsoleInfo();
            }
        });

        btnDialog.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                nfo.DialogInfo();
            }
        });

    }

    public static void main(String[] args){
        JFrame appframe = new JFrame("System Info");
        appframe.setContentPane(new frmInfo().pnlInfo);
        appframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        appframe.pack();
        appframe.setVisible(true);
    }
}
