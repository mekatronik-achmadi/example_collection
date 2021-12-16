/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * JPanelFuses.java
 *
 * Created on 28.02.2009, 20:54:06
 */

package avr8_burn_o_mat;

import java.awt.Component;
import java.util.Vector;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableColumnModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;

/**
 *
 * @author torsten
 */
public class JPanelFuses extends javax.swing.JPanel implements ActionThread.Observer, FusesEditor, FusesObserver {

    private TableModelFuses m_tableModelFuses;

    private AVR m_avr;

    private ActionThread m_actionThread;

    private JPanelBrownOutDetection m_panelBrownOutDetection;

    private JPanelFusesHexEditor m_panelFusesHexEditor;

    private JPanelOscillatorOptions m_panelOscillatorOptions;

    private FusesObservable m_fusesObservable;

    /** Creates new form JPanelFuses */
    public JPanelFuses(ActionThread actionThread) {

        m_actionThread = actionThread;

        m_fusesObservable = new FusesObservable();
        m_fusesObservable.addObserver(this);

        m_tableModelFuses = new TableModelFuses(this);

        initComponents();
        
        if (m_actionThread != null)
            m_actionThread.m_observable.addObserver(this);
        else {
            jButtonReadFuses.setEnabled(false);
            jButtonWriteFuses.setEnabled(false);
            jButtonVerifyFuses.setEnabled(false);
        }

        m_panelBrownOutDetection = new JPanelBrownOutDetection(this);
        jScrollPaneBrownOutDetection.setViewportView(m_panelBrownOutDetection);

        m_panelFusesHexEditor = new JPanelFusesHexEditor(this);
        jScrollPaneFuseHexEdit.setViewportView(m_panelFusesHexEditor);

        jTableAvr.setModel(m_tableModelFuses);
        jTableAvr.setDefaultRenderer(String.class,new CustomTableCellRenderer(m_tableModelFuses));

        jTableAvr.getTableHeader().setReorderingAllowed(false);
    }

    public void setFuse(String fuseName, Fuse.FuseState fuseState) throws Exception {

        if (m_avr == null)
            throw new Exception("Internal error: MCU not set!");

        Vector <Fuse> fuseList = m_avr.getFuseList();

        for (Fuse fuse : fuseList) {
            if (fuse.getName().equals(fuseName)) {
                fuse.setFuseState(fuseState);
                return;
            }
        }

        throw new Exception("Internal error: invalid fuse name: " + fuseName);
    }

    public Fuse.FuseState getFuse(String fuseName) throws Exception {

        if (m_avr == null)
            throw new Exception("Internal error: MCU not set!");

        Vector <Fuse> fuseList = m_avr.getFuseList();

        for (Fuse fuse : fuseList) {
            if (fuse.getName().equals(fuseName)) {
                return fuse.getFuseState();
            }
        }

        throw new Exception("Internal error: invalid fuse name: " + fuseName);
    }

    public FusesObservable getFusesObservable() {
        return m_fusesObservable;
    }

    public void fusesChanged() {
        m_tableModelFuses.fuseListUpdate();
        packColumns();
    }

    public void actionThreadStateChanged(ActionThread.Action newState) {

        final ActionThread.Action newStateTmp = newState;

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                setState(newStateTmp);
            }
        });

    }

    public void setState(ActionThread.Action state) {

        switch (state) {

            case IDLE:
                jButtonReadFuses.setEnabled(true);
                jButtonWriteFuses.setEnabled(true);
                jButtonVerifyFuses.setEnabled(true);
                jButtonResetToDefault.setEnabled(true);
                jComboBoxMode.setEnabled(true);
                jTableAvr.setEnabled(true);
                jTabbedPaneFuses.setEnabled(true);

                m_fusesObservable.fusesChanged(this);
                break;

            default:
                jButtonReadFuses.setEnabled(false);
                jButtonWriteFuses.setEnabled(false);
                jButtonVerifyFuses.setEnabled(false);
                jButtonResetToDefault.setEnabled(false);
                jComboBoxMode.setEnabled(false);
                jTableAvr.setEnabled(false);
                jTabbedPaneFuses.setEnabled(false);
                break;

        }

    }

    public void setAVR(AVR avr) {

        m_avr = avr;
        m_tableModelFuses.setFuseList(m_avr.getFuseList());

        packColumns();

        m_panelBrownOutDetection.setAVR(avr);
        m_panelFusesHexEditor.setAVR(avr);

        setAvrOscillatorOptions(avr);

        validate();
        repaint();
    }

    public AVR getAVR() {
        return m_avr;
    }

    private void setAvrOscillatorOptions(AVR avr) {

        jScrollPaneOscillatorOptions.getViewport().removeAll();

        if (m_panelOscillatorOptions != null)
            m_panelOscillatorOptions.destroy();

        m_panelOscillatorOptions = null;

        if (avr.getOscillatorOptions() != null) {
            m_panelOscillatorOptions = avr.getOscillatorOptions().createPanel(this);
            jScrollPaneOscillatorOptions.setViewportView(m_panelOscillatorOptions);
        } else {
            jScrollPaneOscillatorOptions.setViewportView(new JLabel("not supported for selected MCU"));
        }
    }

    private void packColumns() {
        for (int c = 0; c < jTableAvr.getColumnCount(); c++) {
            packColumn(jTableAvr,c,5);
        }
    }

    private void packColumn(JTable table, int vColIndex, int margin) {
        TableModel model = table.getModel();
        DefaultTableColumnModel colModel = (DefaultTableColumnModel)table.getColumnModel();
        TableColumn col = colModel.getColumn(vColIndex);
        int width = 0;

        // Get width of column header
        TableCellRenderer renderer = col.getHeaderRenderer();
        if (renderer == null) {
            renderer = table.getTableHeader().getDefaultRenderer();
        }
        Component comp = renderer.getTableCellRendererComponent(
                table, col.getHeaderValue(), false, false, 0, 0);
        width = comp.getPreferredSize().width;

        // Get maximum width of column data
        for (int r=0; r<table.getRowCount(); r++) {
            renderer = table.getCellRenderer(r, vColIndex);
            comp = renderer.getTableCellRendererComponent(
                    table, table.getValueAt(r, vColIndex), false, false, r, vColIndex);
            width = Math.max(width, comp.getPreferredSize().width);
        }

        // Add margin
        width += 2*margin;

        // Set the width
        col.setPreferredWidth(width);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jButtonReadFuses = new javax.swing.JButton();
        jButtonWriteFuses = new javax.swing.JButton();
        jButtonVerifyFuses = new javax.swing.JButton();
        jButtonResetToDefault = new javax.swing.JButton();
        jComboBoxMode = new javax.swing.JComboBox();
        jPanel2 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jTabbedPaneFuses = new javax.swing.JTabbedPane();
        jScrollPaneFuseList = new javax.swing.JScrollPane();
        jTableAvr = new javax.swing.JTable();
        jScrollPaneFuseHexEdit = new javax.swing.JScrollPane();
        jScrollPaneBrownOutDetection = new javax.swing.JScrollPane();
        jScrollPaneOscillatorOptions = new javax.swing.JScrollPane();

        setLayout(new java.awt.BorderLayout());

        jPanel1.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT, 10, 10));

        jButtonReadFuses.setText("read fuses");
        jButtonReadFuses.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonReadFusesActionPerformed(evt);
            }
        });
        jPanel1.add(jButtonReadFuses);

        jButtonWriteFuses.setText("write fuses");
        jButtonWriteFuses.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonWriteFusesActionPerformed(evt);
            }
        });
        jPanel1.add(jButtonWriteFuses);

        jButtonVerifyFuses.setText("verify fuses");
        jButtonVerifyFuses.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonVerifyFusesActionPerformed(evt);
            }
        });
        jPanel1.add(jButtonVerifyFuses);

        jButtonResetToDefault.setText("reset to default");
        jButtonResetToDefault.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonResetToDefaultActionPerformed(evt);
            }
        });
        jPanel1.add(jButtonResetToDefault);

        jComboBoxMode.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Mode: normal", "Mode: expert" }));
        jComboBoxMode.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                jComboBoxModeItemStateChanged(evt);
            }
        });
        jPanel1.add(jComboBoxMode);

        add(jPanel1, java.awt.BorderLayout.NORTH);

        jPanel2.setPreferredSize(new java.awt.Dimension(10, 50));
        jPanel2.setLayout(new java.awt.GridLayout(2, 1, 5, 5));

        jLabel1.setText("checked means programmed (bit = 0)");
        jPanel2.add(jLabel1);

        jLabel2.setText("unchecked means unprogrammed (bit = 1)");
        jPanel2.add(jLabel2);

        add(jPanel2, java.awt.BorderLayout.SOUTH);

        jTableAvr.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jTableAvr.setAutoResizeMode(javax.swing.JTable.AUTO_RESIZE_OFF);
        jTableAvr.setIntercellSpacing(new java.awt.Dimension(3, 3));
        jTableAvr.setSelectionForeground(new java.awt.Color(0, 0, 0));
        jTableAvr.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        jScrollPaneFuseList.setViewportView(jTableAvr);

        jTabbedPaneFuses.addTab("Fuse Editor", jScrollPaneFuseList);
        jTabbedPaneFuses.addTab("Fuse Hex Editor", jScrollPaneFuseHexEdit);
        jTabbedPaneFuses.addTab("Brown out detection", jScrollPaneBrownOutDetection);
        jTabbedPaneFuses.addTab("Oscillator/Clock Options", jScrollPaneOscillatorOptions);

        add(jTabbedPaneFuses, java.awt.BorderLayout.CENTER);
    }// </editor-fold>//GEN-END:initComponents

    private void jButtonReadFusesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonReadFusesActionPerformed

        try {
            if (m_actionThread != null)
                m_actionThread.readFuses(m_avr);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error reading Fuses: " + e.getMessage());
        }
    }//GEN-LAST:event_jButtonReadFusesActionPerformed

    private void jButtonWriteFusesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonWriteFusesActionPerformed

        try {
            if (m_actionThread != null)
                m_actionThread.writeFuses(m_avr);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error writing Fuses: " + e.getMessage());
        }
    }//GEN-LAST:event_jButtonWriteFusesActionPerformed

    private void jButtonResetToDefaultActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonResetToDefaultActionPerformed

        m_tableModelFuses.resetToDefault();

        m_fusesObservable.fusesChanged(this);
    }//GEN-LAST:event_jButtonResetToDefaultActionPerformed

    private void jComboBoxModeItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_jComboBoxModeItemStateChanged

        String s = (String)jComboBoxMode.getSelectedItem();

        if (s.equals("Mode: expert"))
            m_tableModelFuses.setFuseMode(Fuse.FuseMode.EXPERT);
        else
            m_tableModelFuses.setFuseMode(Fuse.FuseMode.NORMAL);

        packColumns();
    }//GEN-LAST:event_jComboBoxModeItemStateChanged

    private void jButtonVerifyFusesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonVerifyFusesActionPerformed

        try {
            if (m_actionThread != null)
                m_actionThread.verifyFuses(m_avr);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error verifying Fuses: " + e.getMessage());
        }
    }//GEN-LAST:event_jButtonVerifyFusesActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButtonReadFuses;
    private javax.swing.JButton jButtonResetToDefault;
    private javax.swing.JButton jButtonVerifyFuses;
    private javax.swing.JButton jButtonWriteFuses;
    private javax.swing.JComboBox jComboBoxMode;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPaneBrownOutDetection;
    private javax.swing.JScrollPane jScrollPaneFuseHexEdit;
    private javax.swing.JScrollPane jScrollPaneFuseList;
    private javax.swing.JScrollPane jScrollPaneOscillatorOptions;
    private javax.swing.JTabbedPane jTabbedPaneFuses;
    private javax.swing.JTable jTableAvr;
    // End of variables declaration//GEN-END:variables

}
