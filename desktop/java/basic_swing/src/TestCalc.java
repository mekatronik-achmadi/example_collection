import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by achmadi on 10/20/18.
 */
public class TestCalc {
    private JPanel pnlCalc;
    private JButton btnOK;
    private JButton btnCancel;
    private JButton btnPesan;
    private JTextField txtV1;
    private JTextField txtV2;
    private JTextField txtV3;
    private JButton btnPlus;
    private JButton btnMin;
    private JButton btnMul;
    private JButton btnDiv;
    private JButton btnMod;
    private JButton btnClear;
    private static Hitung calc;
    private static Pesan psn;

    public TestCalc(){
        txtV1.setHorizontalAlignment(SwingConstants.RIGHT);
        txtV2.setHorizontalAlignment(SwingConstants.RIGHT);
        txtV3.setHorizontalAlignment(SwingConstants.RIGHT);

        calc = new Hitung();

        btnPlus.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if(! (txtV1.getText().isEmpty() || txtV2.getText().isEmpty()) ){
                    txtV3.setText(
                            String.valueOf(calc.Tambah(
                                Integer.parseInt(txtV1.getText().trim()),
                                Integer.parseInt(txtV2.getText().trim())
                    )));
                }
            }
        });

        btnMin.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if(! (txtV1.getText().isEmpty() || txtV2.getText().isEmpty()) ){
                    txtV3.setText(
                            String.valueOf(calc.Kurang(
                                    Integer.parseInt(txtV1.getText().trim()),
                                    Integer.parseInt(txtV2.getText().trim())
                            )));
                }
            }
        });

        btnMul.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if(! (txtV1.getText().isEmpty() || txtV2.getText().isEmpty()) ){
                    txtV3.setText(
                            String.valueOf(calc.Kali(
                                    Integer.parseInt(txtV1.getText().trim()),
                                    Integer.parseInt(txtV2.getText().trim())
                            )));
                }
            }
        });

        btnDiv.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if(! (txtV1.getText().isEmpty() || txtV2.getText().isEmpty()) ){
                    txtV3.setText(
                            String.valueOf(calc.Bagi(
                                    Integer.parseInt(txtV1.getText().trim()),
                                    Integer.parseInt(txtV2.getText().trim())
                            )));
                }
            }
        });

        btnMod.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if(! (txtV1.getText().isEmpty() || txtV2.getText().isEmpty()) ){
                    txtV3.setText(
                            String.valueOf(calc.Sisa(
                                    Integer.parseInt(txtV1.getText().trim()),
                                    Integer.parseInt(txtV2.getText().trim())
                            )));
                }
            }
        });

        btnClear.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                txtV1.setText("");
                txtV2.setText("");
                txtV3.setText("");
            }
        });

    // Just for testing MessageBox
        psn = new Pesan();

        btnOK.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                psn.PesanOK();
                System.out.println("OK");
            }
        });

        btnCancel.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                psn.PesanCancel();
                System.out.println("Cancel");
            }
        });

        btnPesan.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                String info = "Just Information";
                psn.PesanTampil(info);
                System.out.println(info);
            }
        });

    }

    public static void main(String[] args){
        JFrame frmCalc = new JFrame("Simple Calculator");
        frmCalc.setContentPane(new TestCalc().pnlCalc);
        frmCalc.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frmCalc.pack();
        frmCalc.setVisible(true);
    }
}
