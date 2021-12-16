/*
    AVR8 Burn-O-Mat
 
    Copyright (C) 2007  Torsten Brischalle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
 */

package avr8_burn_o_mat;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.Vector;
import java.util.prefs.Preferences;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class FormAvrdudeSettings extends javax.swing.JFrame {
    
    private AvrdudeControl m_avrdudeCtrl;
    
    private JFileChooser m_fileChooserAvrdude = new JFileChooser();
    
    private JFileChooser m_fileChooserAvrdudeConfig = new JFileChooser();
    
    /** Creates new form FormAvrdudeCfg */
    public FormAvrdudeSettings(AvrdudeControl avrdudeCtrl) {
        
        m_avrdudeCtrl = avrdudeCtrl;
        
        m_fileChooserAvrdude.setFileFilter(new FileFilterAvrdude());
        m_fileChooserAvrdudeConfig.setFileFilter(new FileFilterAvrdudeConfig());
                
        initComponents();
        
        setIconImage(Toolkit.getDefaultToolkit().getImage("AVR8_Burn-O-Mat_Icon_16.png"));
        
        setPreferredSize(new Dimension(600,500));
        
        String os = System.getProperty("os.name").toLowerCase();
        
        if (os.contains("windows")) {
            jComboBoxPort.addItem("lpt1");
            jComboBoxPort.addItem("lpt2");
            jComboBoxPort.addItem("lpt3");
            jComboBoxPort.addItem("lpt4");
            jComboBoxPort.addItem("lpt5");
            jComboBoxPort.addItem("lpt6");
            jComboBoxPort.addItem("lpt7");
            jComboBoxPort.addItem("lpt8");
            jComboBoxPort.addItem("com1");
            jComboBoxPort.addItem("com2");
            jComboBoxPort.addItem("com3");
            jComboBoxPort.addItem("com4");
            jComboBoxPort.addItem("com5");
            jComboBoxPort.addItem("com6");
            jComboBoxPort.addItem("com7");
            jComboBoxPort.addItem("com8");
        } else {
            jComboBoxPort.addItem("/dev/parport0");
            jComboBoxPort.addItem("/dev/parport1");
            jComboBoxPort.addItem("/dev/parport2");
            jComboBoxPort.addItem("/dev/parport3");
            jComboBoxPort.addItem("/dev/parport4");
            jComboBoxPort.addItem("/dev/parport5");
            jComboBoxPort.addItem("/dev/parport6");
            jComboBoxPort.addItem("/dev/parport7");
            jComboBoxPort.addItem("/dev/ttyUSB0");
            jComboBoxPort.addItem("/dev/ttyS0");
            jComboBoxPort.addItem("/dev/ttyS1");
            jComboBoxPort.addItem("/dev/ttyS2");
            jComboBoxPort.addItem("/dev/ttyS3");
            jComboBoxPort.addItem("/dev/ttyS4");
            jComboBoxPort.addItem("/dev/ttyS5");
            jComboBoxPort.addItem("/dev/ttyS6");
            jComboBoxPort.addItem("/dev/ttyS7");
        }
        
        jComboBoxPort.addItem("usb");
        
        loadPreferences();
        
    }
    
    private void updateProgrammerList() throws IOException {
        
        jComboBoxProgrammer.removeAllItems();
        
        Vector <AvrdudeProgrammer> items = new Vector <AvrdudeProgrammer>();
        
        for (AvrdudeProgrammer p : m_avrdudeCtrl.getProgrammerList())
            items.add(p);
        
        Collections.sort(items);
        
        for (AvrdudeProgrammer p : items) {
            jComboBoxProgrammer.addItem(p);
        }
    }
    
    public void savePreferences() {
        
        try {
            Preferences prefs = Preferences.userNodeForPackage(this.getClass());
        
            prefs.putInt("FormAvrdudeSettings_Width",getWidth());
            prefs.putInt("FormAvrdudeSettings_Height",getHeight());
            prefs.putInt("FormAvrdudeSettings_PosX",getX());
            prefs.putInt("FormAvrdudeSettings_PosY",getY());
            
            prefs.flush();
        } catch (Exception e) {
            System.err.println("Error while saving preferences: " + e.getMessage());
        }
        
    }
    
    public void loadPreferences() {
        
        try {
            Preferences prefs = Preferences.userNodeForPackage(this.getClass());
            
            int w, h;
            
            w = prefs.getInt("FormAvrdudeSettings_Width",600);
            h = prefs.getInt("FormAvrdudeSettings_Height",500);
            setSize(w,h);
            setPreferredSize(new Dimension(w,h));
            
            setLocation(prefs.getInt("FormAvrdudeSettings_PosX",100),
                        prefs.getInt("FormAvrdudeSettings_PosY",100));
                        
        } catch (Exception e) {
            System.err.println("Error while loading preferences: " + e.getMessage());
        }
        
    }
    
    private void applyChanges() {
        
        try {
            
            AvrdudeProgrammer programmer = (AvrdudeProgrammer)jComboBoxProgrammer.getSelectedItem();
            String port = (String)jComboBoxPort.getSelectedItem();

            m_avrdudeCtrl.setAvrdude(jTextFieldAvrdude.getText());
            m_avrdudeCtrl.setAvrdudeConfig(jTextFieldAvrdudeConfig.getText());
            m_avrdudeCtrl.setProgrammer(programmer);
            m_avrdudeCtrl.setPort(port);
            m_avrdudeCtrl.setDisableAutoErase(jCheckBoxDisableAutoErase.isSelected());
            m_avrdudeCtrl.setDisableFuseCheck(jCheckBoxDisableFuseCheck.isSelected());
            m_avrdudeCtrl.setExitSpecActivated(jCheckBoxExitSpec.isSelected());
            m_avrdudeCtrl.setLeftResetActivated(jCheckBoxLeftResetActivated.isSelected());
            m_avrdudeCtrl.setLeftVccActivated(jCheckBoxLeftVccActivated.isSelected());
            m_avrdudeCtrl.setAdditionalOptions(jTextFieldAdditionalOptions.getText());
            
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error applying changes: " + e.getMessage());
        }
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        jScrollPane1 = new javax.swing.JScrollPane();
        jPanel4 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jTextFieldAvrdude = new javax.swing.JTextField();
        jButtonAvrdude = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        jTextFieldAvrdudeConfig = new javax.swing.JTextField();
        jButtonAvrdudeConfig = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        jComboBoxPort = new javax.swing.JComboBox();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jComboBoxProgrammer = new javax.swing.JComboBox();
        jCheckBoxDisableAutoErase = new javax.swing.JCheckBox();
        jLabel5 = new javax.swing.JLabel();
        jTextFieldAdditionalOptions = new javax.swing.JTextField();
        jLabel6 = new javax.swing.JLabel();
        jCheckBoxExitSpec = new javax.swing.JCheckBox();
        jCheckBoxLeftResetActivated = new javax.swing.JCheckBox();
        jCheckBoxLeftVccActivated = new javax.swing.JCheckBox();
        jPanel3 = new javax.swing.JPanel();
        jCheckBoxDisableFuseCheck = new javax.swing.JCheckBox();
        jPanel2 = new javax.swing.JPanel();
        jButtonOk = new javax.swing.JButton();
        jButtonApply = new javax.swing.JButton();
        jButtonCancel = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DO_NOTHING_ON_CLOSE);
        setTitle("AVRDUDE Settings");
        addComponentListener(new java.awt.event.ComponentAdapter() {
            public void componentShown(java.awt.event.ComponentEvent evt) {
                formComponentShown(evt);
            }
        });
        getContentPane().setLayout(new java.awt.GridLayout(1, 1));

        jPanel4.setLayout(new java.awt.GridBagLayout());

        jLabel1.setText("AVRDUDE location");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 0, 10);
        jPanel4.add(jLabel1, gridBagConstraints);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 0);
        jPanel4.add(jTextFieldAvrdude, gridBagConstraints);

        jButtonAvrdude.setText("File");
        jButtonAvrdude.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonAvrdudeActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.EAST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel4.add(jButtonAvrdude, gridBagConstraints);

        jLabel2.setText("alternative AVRDUDE configuration file");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 0, 10);
        jPanel4.add(jLabel2, gridBagConstraints);

        jTextFieldAvrdudeConfig.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextFieldAvrdudeConfigActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 0);
        jPanel4.add(jTextFieldAvrdudeConfig, gridBagConstraints);

        jButtonAvrdudeConfig.setText("File");
        jButtonAvrdudeConfig.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonAvrdudeConfigActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.EAST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel4.add(jButtonAvrdudeConfig, gridBagConstraints);

        jPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder("AVRDUDE Options"));
        jPanel1.setLayout(new java.awt.GridBagLayout());

        jComboBoxPort.setEditable(true);
        jComboBoxPort.setMinimumSize(new java.awt.Dimension(150, 23));
        jComboBoxPort.setPreferredSize(new java.awt.Dimension(150, 24));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 10, 10);
        jPanel1.add(jComboBoxPort, gridBagConstraints);

        jLabel3.setText("Programmer");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jLabel3, gridBagConstraints);

        jLabel4.setText("Port");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jLabel4, gridBagConstraints);

        jComboBoxProgrammer.setMinimumSize(new java.awt.Dimension(200, 23));
        jComboBoxProgrammer.setPreferredSize(new java.awt.Dimension(200, 24));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 10, 10);
        jPanel1.add(jComboBoxProgrammer, gridBagConstraints);

        jCheckBoxDisableAutoErase.setText("disable auto erase for flash (-D)");
        jCheckBoxDisableAutoErase.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        jPanel1.add(jCheckBoxDisableAutoErase, gridBagConstraints);

        jLabel5.setText("additional options");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 5, 10);
        jPanel1.add(jLabel5, gridBagConstraints);

        jTextFieldAdditionalOptions.setMinimumSize(new java.awt.Dimension(65, 25));
        jTextFieldAdditionalOptions.setPreferredSize(new java.awt.Dimension(65, 25));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jTextFieldAdditionalOptions, gridBagConstraints);

        jLabel6.setText("(port can be entered directly if not in list)");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 10, 5);
        jPanel1.add(jLabel6, gridBagConstraints);

        jCheckBoxExitSpec.setText("Exit specification (-E)");
        jCheckBoxExitSpec.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                jCheckBoxExitSpecStateChanged(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jCheckBoxExitSpec, gridBagConstraints);

        jCheckBoxLeftResetActivated.setText("reset will be left activated on program exit (-E reset)");
        jCheckBoxLeftResetActivated.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jCheckBoxLeftResetActivated, gridBagConstraints);

        jCheckBoxLeftVccActivated.setText("VCC will be left activated on exit (-E vcc)");
        jCheckBoxLeftVccActivated.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jCheckBoxLeftVccActivated, gridBagConstraints);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weighty = 1.0;
        jPanel1.add(jPanel3, gridBagConstraints);

        jCheckBoxDisableFuseCheck.setText("disable fuse check (-u)");
        jCheckBoxDisableFuseCheck.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 10, 10);
        jPanel1.add(jCheckBoxDisableFuseCheck, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        jPanel4.add(jPanel1, gridBagConstraints);

        jPanel2.setLayout(new java.awt.GridBagLayout());

        jButtonOk.setText("Ok");
        jButtonOk.setPreferredSize(new java.awt.Dimension(75, 25));
        jButtonOk.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonOkActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.weightx = 1.0;
        jPanel2.add(jButtonOk, gridBagConstraints);

        jButtonApply.setText("Apply");
        jButtonApply.setPreferredSize(new java.awt.Dimension(75, 25));
        jButtonApply.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonApplyActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.weightx = 1.0;
        jPanel2.add(jButtonApply, gridBagConstraints);

        jButtonCancel.setText("Cancel");
        jButtonCancel.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonCancelActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.EAST;
        gridBagConstraints.weightx = 1.0;
        jPanel2.add(jButtonCancel, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        jPanel4.add(jPanel2, gridBagConstraints);

        jScrollPane1.setViewportView(jPanel4);

        getContentPane().add(jScrollPane1);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jTextFieldAvrdudeConfigActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextFieldAvrdudeConfigActionPerformed
        
        try {
            updateProgrammerList();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error loading AVRDUDE config file: " + e.getMessage());
        }
        
    }//GEN-LAST:event_jTextFieldAvrdudeConfigActionPerformed

    private void jButtonOkActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonOkActionPerformed
        
        applyChanges();
        setVisible(false);

        
    }//GEN-LAST:event_jButtonOkActionPerformed

    private void jButtonApplyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonApplyActionPerformed
        
        applyChanges();
        
    }//GEN-LAST:event_jButtonApplyActionPerformed

    private void formComponentShown(java.awt.event.ComponentEvent evt) {//GEN-FIRST:event_formComponentShown
        
        try {
            updateProgrammerList();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error loading AVRDUDE config file: " + e.getMessage());
            e.printStackTrace();
        }
        
        try {
            jTextFieldAvrdude.setText(m_avrdudeCtrl.getAvrdude());
            jTextFieldAvrdudeConfig.setText(m_avrdudeCtrl.getAvrdudeConfig());

            jComboBoxProgrammer.setSelectedItem(m_avrdudeCtrl.getProgrammer());
            jComboBoxPort.setSelectedItem(m_avrdudeCtrl.getPort());

            jCheckBoxDisableAutoErase.setSelected(m_avrdudeCtrl.getDisableAutoErase());
            jCheckBoxDisableFuseCheck.setSelected(m_avrdudeCtrl.getDisableFuseCheck());
            jCheckBoxExitSpec.setSelected(m_avrdudeCtrl.getExitSpecActivated());
            jCheckBoxLeftResetActivated.setSelected(m_avrdudeCtrl.getLeftResetActivated());
            jCheckBoxLeftVccActivated.setSelected(m_avrdudeCtrl.getLeftVccActivated());
            
            jTextFieldAdditionalOptions.setText(m_avrdudeCtrl.getAdditionalOptions());
            
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,e.getMessage());
        }
        
    }//GEN-LAST:event_formComponentShown

    private void jButtonAvrdudeConfigActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonAvrdudeConfigActionPerformed
        
        int state = m_fileChooserAvrdudeConfig.showOpenDialog(null);
        if (state == JFileChooser.APPROVE_OPTION) {
            File file = m_fileChooserAvrdudeConfig.getSelectedFile();
            jTextFieldAvrdudeConfig.setText(file.getPath());
            
        }
        
        try {
            updateProgrammerList();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this,"Error loading AVRDUDE config file: " + e.getMessage());
        }
        
    }//GEN-LAST:event_jButtonAvrdudeConfigActionPerformed

    private void jButtonAvrdudeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonAvrdudeActionPerformed
        
        int state = m_fileChooserAvrdude.showOpenDialog(null);
        if (state == JFileChooser.APPROVE_OPTION) {
            File file = m_fileChooserAvrdude.getSelectedFile();
            jTextFieldAvrdude.setText(file.getPath());
        }

    }//GEN-LAST:event_jButtonAvrdudeActionPerformed

    private void jButtonCancelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonCancelActionPerformed
        
        setVisible(false);
        
    }//GEN-LAST:event_jButtonCancelActionPerformed

    private void jCheckBoxExitSpecStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_jCheckBoxExitSpecStateChanged

        boolean enabled = jCheckBoxExitSpec.isSelected();

        jCheckBoxLeftResetActivated.setEnabled(enabled);
        jCheckBoxLeftVccActivated.setEnabled(enabled);

    }//GEN-LAST:event_jCheckBoxExitSpecStateChanged
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButtonApply;
    private javax.swing.JButton jButtonAvrdude;
    private javax.swing.JButton jButtonAvrdudeConfig;
    private javax.swing.JButton jButtonCancel;
    private javax.swing.JButton jButtonOk;
    private javax.swing.JCheckBox jCheckBoxDisableAutoErase;
    private javax.swing.JCheckBox jCheckBoxDisableFuseCheck;
    private javax.swing.JCheckBox jCheckBoxExitSpec;
    private javax.swing.JCheckBox jCheckBoxLeftResetActivated;
    private javax.swing.JCheckBox jCheckBoxLeftVccActivated;
    private javax.swing.JComboBox jComboBoxPort;
    private javax.swing.JComboBox jComboBoxProgrammer;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextField jTextFieldAdditionalOptions;
    private javax.swing.JTextField jTextFieldAvrdude;
    private javax.swing.JTextField jTextFieldAvrdudeConfig;
    // End of variables declaration//GEN-END:variables
    
}
