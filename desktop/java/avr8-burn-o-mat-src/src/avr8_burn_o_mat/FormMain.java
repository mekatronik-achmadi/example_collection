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
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.Window;
import java.io.File;
import java.util.Collections;
import java.util.Vector;
import java.util.prefs.Preferences;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

public class FormMain extends javax.swing.JFrame implements InterfaceTextOutput, ActionThread.Observer {
    
    private final int    MAX_ITEMS_IN_HISTORY = 8;
    
    private Vector <AVR> m_avrList;
    
    private AVR          m_avr;
    
    private AvrdudeControl  m_avrdudeCtrl;
    
    private JFileChooser m_fileChooserFlash;
    
    private JFileChooser m_fileChooserEEPROM;
    
    private ActionThread m_actionThread;
    
    private FormAbout    m_formAbout;
    private FormFuses    m_formFuses;
    private FormAvrdudeSettings m_formAvrdudeSettings;
    
    private String       m_currentLookAndFeel = "";
    
    /** Creates new form FormMain */
    public FormMain() {
        initComponents();
        
        try {            
            m_avrdudeCtrl = new AvrdudeControl(this);

            m_actionThread = new ActionThread(m_avrdudeCtrl);
            m_actionThread.m_observable.addObserver(this);

            m_formFuses = new FormFuses(m_actionThread);

            m_formAbout = new FormAbout();

            m_formAvrdudeSettings = new FormAvrdudeSettings(m_avrdudeCtrl);

            readAVRConfig("./AVR8_Burn_O_Mat_Config.xml");

            setIconImage(Toolkit.getDefaultToolkit().getImage("AVR8_Burn-O-Mat_Icon_16.png"));

            loadPreferences();

            setState(ActionThread.Action.IDLE);
            
            UIManager.LookAndFeelInfo[ ] lafList = UIManager.getInstalledLookAndFeels();
            
            for (UIManager.LookAndFeelInfo laf : lafList) {
                JMenuItem item = new JMenuItem(laf.getName());
                
                item.addActionListener(new java.awt.event.ActionListener() {
                    public void actionPerformed(java.awt.event.ActionEvent evt) {
                        jMenuItemLookAndFeelActionPerformed(evt);
                    }
                });
                
                jMenuLookAndFeel.add(item);
            }
            
            m_fileChooserFlash = new JFileChooser();
            m_fileChooserEEPROM = new JFileChooser();
            
            m_fileChooserFlash.setFileFilter(new FileFilterHex());
            m_fileChooserEEPROM.setFileFilter(new FileFilterHex());

        } catch (Exception e) {
            showError("Error while loading program: " + e.getMessage());
            System.exit(1);
        }
        
    }
    
    public static boolean setLookAndFeel(String lookAndFeelName) {
        
        try {
            UIManager.LookAndFeelInfo[ ] lafList = UIManager.getInstalledLookAndFeels();
            
            String lafClass = null;
            
            for (UIManager.LookAndFeelInfo laf : lafList) {
                if (lookAndFeelName.equals(laf.getName())) {
                    lafClass = laf.getClassName();
                    break;
                }
            }
            
            if (lafClass == null)
                throw new Exception("Look And Feel " + lookAndFeelName + " not available");
            
            for (Frame f : Frame.getFrames())
                f.setPreferredSize(f.getSize());
            
            UIManager.setLookAndFeel(lafClass);
            
            for (Frame f : Frame.getFrames())
            {
                SwingUtilities.updateComponentTreeUI(f);
                f.pack();
                
                for (Window w : f.getOwnedWindows()) {
                    SwingUtilities.updateComponentTreeUI(w);
                    w.pack();
                }
            }

        } catch (Exception e) {
            return false;
        }

        return true;
    }
    
    private void jMenuItemLookAndFeelActionPerformed(java.awt.event.ActionEvent evt) {                                                 
        setLookAndFeel(evt.getActionCommand());
        m_currentLookAndFeel = evt.getActionCommand();
    }
    
    private void addToHistory(JComboBox comboBox, String item) {
        
        // wenn das Element schon existiert, dann aus der Liste löschen
        int     idx;
        boolean removed;
        
        do {
            removed = false;
            for (idx = 0; idx < comboBox.getItemCount(); idx++) {

                String s = (String)comboBox.getItemAt(idx);
                assert s != null;

                if (s.equals(item)) {
                    comboBox.removeItemAt(idx);
                    removed = true;
                    break;
                }
            }
        } while (removed == true);
        
        // vorne anfügen
        comboBox.insertItemAt(item,0);
        
        // Liste begrenzen
        while (comboBox.getItemCount() > MAX_ITEMS_IN_HISTORY)
            comboBox.removeItemAt(comboBox.getItemCount() - 1);
        
        // Item auswählen
        comboBox.setSelectedItem(item);
    }
    
    public void actionThreadStateChanged(ActionThread.Action newState) {
        
        final ActionThread.Action newStateTmp = newState;
        
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                setState(newStateTmp);
            }
        });
        
        String msg = null;
        boolean error = false;

        switch (newState) {
            case READ_FLASH_DONE:       msg = "Flash successfully read.";       break;
            case WRITE_FLASH_DONE:      msg = "Flash successfully written.";    break;
            case VERIFY_FLASH_DONE:     msg = "Flash successfully verified.";   break;
            case READ_EEPROM_DONE:      msg = "EEPROM successfully read.";      break;
            case WRITE_EEPROM_DONE:     msg = "EEPROM successfully written.";   break;
            case VERIFY_EEPROM_DONE:    msg = "EEPROM successfully verified.";  break;
            case READ_FUSES_DONE:       msg = "Fuses successfully read.";       break;
            case WRITE_FUSES_DONE:      msg = "Fuses successfully written.";    break;
            case VERIFY_FUSES_DONE:     msg = "Fuses successfully verified.";   break;
            
            case READ_FLASH_ERROR:
            case WRITE_FLASH_ERROR:
            case VERIFY_FLASH_ERROR:
            case READ_EEPROM_ERROR:
            case WRITE_EEPROM_ERROR:
            case VERIFY_EEPROM_ERROR:
            case READ_FUSES_ERROR:
            case WRITE_FUSES_ERROR:
            case VERIFY_FUSES_ERROR:
                msg = m_actionThread.getLastErrorMsg();
                error = true;
                break;
        }
        
        if (msg != null) {
            
            final String s = msg;
            final boolean err = error;
            
            SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                    if (err)
                        showError(s);
                    else
                        JOptionPane.showMessageDialog(null, s);
                }
            });
        }
    }
    
    private void setState(ActionThread.Action state) {
        
        switch (state) {
            
            case IDLE:
                jComboBoxAvr.setEnabled(true);
                jButtonFuses.setEnabled(true);
                jComboBoxFileFlash.setEnabled(true);
                jComboBoxFileEEPROM.setEnabled(true);
                jButtonFileFlash.setEnabled(true);
                jButtonFileEEPROM.setEnabled(true);
                jComboBoxFlashFileType.setEnabled(true);
                jComboBoxEEPROMFileType.setEnabled(true);
                jButtonReadFlash.setEnabled(true);
                jButtonWriteFlash.setEnabled(true);
                jButtonVerifyFlash.setEnabled(true);
                jButtonReadEEPROM.setEnabled(true);
                jButtonWriteEEPROM.setEnabled(true);
                jButtonVerifyEEPROM.setEnabled(true);
                break;
                
            default:
                jComboBoxAvr.setEnabled(false);
                jButtonFuses.setEnabled(false);
                jComboBoxFileFlash.setEnabled(false);
                jComboBoxFileEEPROM.setEnabled(false);
                jButtonFileFlash.setEnabled(false);
                jButtonFileEEPROM.setEnabled(false);
                jComboBoxFlashFileType.setEnabled(false);
                jComboBoxEEPROMFileType.setEnabled(false);
                jButtonReadFlash.setEnabled(false);
                jButtonWriteFlash.setEnabled(false);
                jButtonVerifyFlash.setEnabled(false);
                jButtonReadEEPROM.setEnabled(false);
                jButtonWriteEEPROM.setEnabled(false);
                jButtonVerifyEEPROM.setEnabled(false);
                break;
        }
    }
    
    public void savePreferences() {
        
        try {
            Preferences prefs = Preferences.userNodeForPackage(this.getClass());
            
            System.out.println("preferences saved to: " + prefs.absolutePath());
            
            prefs.putInt("FormMain_Width",getWidth());
            prefs.putInt("FormMain_Height",getHeight());
            prefs.putInt("FormMain_PosX",getX());
            prefs.putInt("FormMain_PosY",getY());
            
            prefs.putInt("FormMain_DividerPos",jSplitPane1.getDividerLocation());
            
            String file;
            
            file = (String)jComboBoxFileFlash.getSelectedItem();
            if (file != null) 
                prefs.put("FileFlash",file);
            
            file = (String)jComboBoxFileEEPROM.getSelectedItem();
            if (file != null) 
                prefs.put("FileEEPROM",file);
            
            prefs.put("ComboBoxAvr",(String)jComboBoxAvr.getSelectedItem());
            prefs.put("ComboBoxFlashFileType",(String)jComboBoxFlashFileType.getSelectedItem());
            prefs.put("ComboBoxEEPROMFileType",(String)jComboBoxEEPROMFileType.getSelectedItem());
            
            prefs.put("FileDialogLastDirFlash",m_fileChooserFlash.getCurrentDirectory().getPath());
            prefs.put("FileDialogLastDirEEPROM",m_fileChooserEEPROM.getCurrentDirectory().getPath());
            
            prefs.put("LookAndFeel",m_currentLookAndFeel);
            
            int idx;
            
            for (idx = 0; idx < jComboBoxFileFlash.getItemCount(); idx++) {
                file = (String)jComboBoxFileFlash.getItemAt(idx);
                assert file != null;
                prefs.put("FileFlashHistory" + idx,file);
            }
            
            for (idx = 0; idx < jComboBoxFileEEPROM.getItemCount(); idx++) {
                file = (String)jComboBoxFileEEPROM.getItemAt(idx);
                assert file != null;
                prefs.put("FileEEPROMHistory" + idx,file);
            }
            
            prefs.flush();
        } catch (Exception e) {
            System.err.println("Error while saving preferences: " + e.getMessage());
        }
        
    }
    
    public void loadPreferences() {
        
        try {
            Preferences prefs = Preferences.userNodeForPackage(this.getClass());
            String s;
            
            s = prefs.get("LookAndFeel","Substance");
            if (s.length() > 0) {
                setLookAndFeel(s);
                m_currentLookAndFeel = s;
            }

            int w, h;
            
            w = prefs.getInt("FormMain_Width",600);
            h = prefs.getInt("FormMain_Height",500);
            setSize(w,h);
            setPreferredSize(new Dimension(w,h));
            
            setLocation(prefs.getInt("FormMain_PosX",100),
                        prefs.getInt("FormMain_PosY",100));
            
            jSplitPane1.setDividerLocation(
                    prefs.getInt("FormMain_DividerPos",jSplitPane1.getDividerLocation()));

            int idx;
            
            jComboBoxFileFlash.removeAllItems();
            for (idx = 0; idx < MAX_ITEMS_IN_HISTORY; idx++) {
                s = prefs.get("FileFlashHistory" + idx,"");
                if (s.length() > 0)
                    jComboBoxFileFlash.addItem(s);
            }
            
            jComboBoxFileEEPROM.removeAllItems();
            for (idx = 0; idx < MAX_ITEMS_IN_HISTORY; idx++) {
                s = prefs.get("FileEEPROMHistory" + idx,"");
                if (s.length() > 0)
                    jComboBoxFileEEPROM.addItem(s);
            }
            
            jComboBoxFileFlash.setSelectedItem(prefs.get("FileFlash",""));
            jComboBoxFileEEPROM.setSelectedItem(prefs.get("FileEEPROM",""));
            
            s = prefs.get("ComboBoxAvr","");
            if (s.length() > 0)
                jComboBoxAvr.setSelectedItem(s);
            
            s = prefs.get("ComboBoxFlashFileType","");
            if (s.length() > 0)
                jComboBoxFlashFileType.setSelectedItem(s);
            
            s = prefs.get("ComboBoxEEPROMFileType","");
            if (s.length() > 0)
                jComboBoxEEPROMFileType.setSelectedItem(s);
            
            s = prefs.get("FileDialogLastDirFlash","");
            if (s.length() > 0)
                m_fileChooserFlash.setCurrentDirectory(new File(s));
            
            s = prefs.get("FileDialogLastDirEEPROM","");
            if (s.length() > 0)
                m_fileChooserEEPROM.setCurrentDirectory(new File(s));
            
        } catch (Exception e) {
            System.err.println("Error while loading preferences: " + e.getMessage());
        }
        
    }
    
    public void print(final String line) {

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                jTextAreaOutput.append(line);
            }
        });
    }
    
    public void println(final String line) {

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                jTextAreaOutput.append(line);
                jTextAreaOutput.append("\n");
            }
        });
    }
    
    public void clearText() {
        
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                jTextAreaOutput.setText("");
            }
        });
    }
    
    public void readAVRConfig(String uri) {
        
        m_avr = null;
        
        try {
            
            XmlReaderAvrConfig cfg = new XmlReaderAvrConfig();
            cfg.readXmlFile(uri);
            
            m_avrList = cfg.getAVRList();
            
        } catch (Exception e) {
            showError("Error while reading config: " + e.getMessage());
        }
        
        UpdateComboBoxAvr();
    }
    
    private void UpdateComboBoxAvr() {
        
        Vector <String> items = new Vector <String>();
        
        for (AVR avr : m_avrList) {
            items.add(avr.getCaption());
        }
        
        Collections.sort(items);
        
        jComboBoxAvr.removeAllItems();
        
        for (String item : items) {
            jComboBoxAvr.addItem(item);
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

        jPopupMenuCopyToClipboard = new javax.swing.JPopupMenu();
        jMenuItemCopySelectedToClipboard = new javax.swing.JMenuItem();
        jMenuItemAllToClipboard = new javax.swing.JMenuItem();
        jMenuItemClearOutput = new javax.swing.JMenuItem();
        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jComboBoxAvr = new javax.swing.JComboBox();
        jButtonFuses = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        jSplitPane1 = new javax.swing.JSplitPane();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTextAreaOutput = new javax.swing.JTextArea();
        jPanel3 = new javax.swing.JPanel();
        jPanel4 = new javax.swing.JPanel();
        jButtonFileFlash = new javax.swing.JButton();
        jComboBoxFlashFileType = new javax.swing.JComboBox();
        jPanel6 = new javax.swing.JPanel();
        jButtonWriteFlash = new javax.swing.JButton();
        jButtonReadFlash = new javax.swing.JButton();
        jButtonVerifyFlash = new javax.swing.JButton();
        jComboBoxFileFlash = new javax.swing.JComboBox();
        jPanel5 = new javax.swing.JPanel();
        jComboBoxEEPROMFileType = new javax.swing.JComboBox();
        jButtonFileEEPROM = new javax.swing.JButton();
        jComboBoxFileEEPROM = new javax.swing.JComboBox();
        jPanel7 = new javax.swing.JPanel();
        jButtonWriteEEPROM = new javax.swing.JButton();
        jButtonReadEEPROM = new javax.swing.JButton();
        jButtonVerifyEEPROM = new javax.swing.JButton();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenu2 = new javax.swing.JMenu();
        jMenuItem3 = new javax.swing.JMenuItem();
        jMenuLookAndFeel = new javax.swing.JMenu();
        jMenu3 = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();

        jMenuItemCopySelectedToClipboard.setText("Copy selected  to clipboard");
        jMenuItemCopySelectedToClipboard.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItemCopySelectedToClipboardActionPerformed(evt);
            }
        });
        jPopupMenuCopyToClipboard.add(jMenuItemCopySelectedToClipboard);

        jMenuItemAllToClipboard.setText("Copy all to clipboard");
        jMenuItemAllToClipboard.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItemAllToClipboardActionPerformed(evt);
            }
        });
        jPopupMenuCopyToClipboard.add(jMenuItemAllToClipboard);

        jMenuItemClearOutput.setText("Clear output");
        jMenuItemClearOutput.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItemClearOutputActionPerformed(evt);
            }
        });
        jPopupMenuCopyToClipboard.add(jMenuItemClearOutput);

        setTitle("AVR8 Burn-O-Mat v2");
        setMinimumSize(new java.awt.Dimension(600, 500));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });
        getContentPane().setLayout(new java.awt.BorderLayout(10, 10));

        jPanel1.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT, 10, 10));

        jLabel1.setText("AVR type");
        jPanel1.add(jLabel1);

        jComboBoxAvr.setMaximumRowCount(10);
        jComboBoxAvr.setMinimumSize(new java.awt.Dimension(150, 24));
        jComboBoxAvr.setPreferredSize(new java.awt.Dimension(150, 24));
        jComboBoxAvr.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                jComboBoxAvrItemStateChanged(evt);
            }
        });
        jPanel1.add(jComboBoxAvr);

        jButtonFuses.setText("Fuses");
        jButtonFuses.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonFuses.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonFusesActionPerformed(evt);
            }
        });
        jPanel1.add(jButtonFuses);

        getContentPane().add(jPanel1, java.awt.BorderLayout.NORTH);

        jPanel2.setPreferredSize(new java.awt.Dimension(400, 300));
        jPanel2.setLayout(new javax.swing.BoxLayout(jPanel2, javax.swing.BoxLayout.LINE_AXIS));

        jSplitPane1.setDividerLocation(200);
        jSplitPane1.setOrientation(javax.swing.JSplitPane.VERTICAL_SPLIT);

        jTextAreaOutput.setColumns(20);
        jTextAreaOutput.setEditable(false);
        jTextAreaOutput.setRows(5);
        jTextAreaOutput.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jTextAreaOutputMouseReleased(evt);
            }
        });
        jScrollPane1.setViewportView(jTextAreaOutput);

        jSplitPane1.setRightComponent(jScrollPane1);

        jPanel3.setLayout(new javax.swing.BoxLayout(jPanel3, javax.swing.BoxLayout.Y_AXIS));

        jPanel4.setBorder(javax.swing.BorderFactory.createTitledBorder("Flash"));
        jPanel4.setLayout(new java.awt.GridBagLayout());

        jButtonFileFlash.setText("File");
        jButtonFileFlash.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonFileFlashActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel4.add(jButtonFileFlash, gridBagConstraints);

        jComboBoxFlashFileType.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "auto", "Intel Hex", "Motorola S-record", "raw" }));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel4.add(jComboBoxFlashFileType, gridBagConstraints);

        jPanel6.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT));

        jButtonWriteFlash.setText("Write");
        jButtonWriteFlash.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonWriteFlash.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonWriteFlashActionPerformed(evt);
            }
        });
        jPanel6.add(jButtonWriteFlash);

        jButtonReadFlash.setText("Read");
        jButtonReadFlash.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonReadFlash.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonReadFlashActionPerformed(evt);
            }
        });
        jPanel6.add(jButtonReadFlash);

        jButtonVerifyFlash.setText("Verify");
        jButtonVerifyFlash.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonVerifyFlash.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonVerifyFlashActionPerformed(evt);
            }
        });
        jPanel6.add(jButtonVerifyFlash);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weighty = 1.0;
        jPanel4.add(jPanel6, gridBagConstraints);

        jComboBoxFileFlash.setEditable(true);
        jComboBoxFileFlash.setMinimumSize(new java.awt.Dimension(100, 24));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel4.add(jComboBoxFileFlash, gridBagConstraints);

        jPanel3.add(jPanel4);

        jPanel5.setBorder(javax.swing.BorderFactory.createTitledBorder("EEPROM"));
        jPanel5.setLayout(new java.awt.GridBagLayout());

        jComboBoxEEPROMFileType.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "auto", "Intel Hex", "Motorola S-record", "raw" }));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel5.add(jComboBoxEEPROMFileType, gridBagConstraints);

        jButtonFileEEPROM.setText("File");
        jButtonFileEEPROM.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonFileEEPROMActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel5.add(jButtonFileEEPROM, gridBagConstraints);

        jComboBoxFileEEPROM.setEditable(true);
        jComboBoxFileEEPROM.setMinimumSize(new java.awt.Dimension(100, 24));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel5.add(jComboBoxFileEEPROM, gridBagConstraints);

        jPanel7.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT));

        jButtonWriteEEPROM.setText("Write");
        jButtonWriteEEPROM.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonWriteEEPROM.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonWriteEEPROMActionPerformed(evt);
            }
        });
        jPanel7.add(jButtonWriteEEPROM);

        jButtonReadEEPROM.setText("Read");
        jButtonReadEEPROM.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonReadEEPROM.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonReadEEPROMActionPerformed(evt);
            }
        });
        jPanel7.add(jButtonReadEEPROM);

        jButtonVerifyEEPROM.setText("Verify");
        jButtonVerifyEEPROM.setPreferredSize(new java.awt.Dimension(80, 25));
        jButtonVerifyEEPROM.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonVerifyEEPROMActionPerformed(evt);
            }
        });
        jPanel7.add(jButtonVerifyEEPROM);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weighty = 1.0;
        jPanel5.add(jPanel7, gridBagConstraints);

        jPanel3.add(jPanel5);

        jSplitPane1.setTopComponent(jPanel3);

        jPanel2.add(jSplitPane1);

        getContentPane().add(jPanel2, java.awt.BorderLayout.CENTER);

        jMenu1.setText("File");

        jMenuItem1.setText("Exit");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem1);

        jMenuBar1.add(jMenu1);

        jMenu2.setText("Settings");

        jMenuItem3.setText("AVRDUDE");
        jMenuItem3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem3ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem3);

        jMenuLookAndFeel.setText("Look and feel");
        jMenu2.add(jMenuLookAndFeel);

        jMenuBar1.add(jMenu2);

        jMenu3.setText("Help");

        jMenuItem2.setText("About");
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        jMenu3.add(jMenuItem2);

        jMenuBar1.add(jMenu3);

        setJMenuBar(jMenuBar1);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jMenuItemAllToClipboardActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItemAllToClipboardActionPerformed

        jTextAreaOutput.selectAll();
        jTextAreaOutput.copy();

    }//GEN-LAST:event_jMenuItemAllToClipboardActionPerformed

    private void jMenuItemClearOutputActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItemClearOutputActionPerformed
        
        jTextAreaOutput.setText("");
        
    }//GEN-LAST:event_jMenuItemClearOutputActionPerformed

    private void jMenuItemCopySelectedToClipboardActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItemCopySelectedToClipboardActionPerformed
        
        jTextAreaOutput.copy();
        
    }//GEN-LAST:event_jMenuItemCopySelectedToClipboardActionPerformed

    private void jTextAreaOutputMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTextAreaOutputMouseReleased
        
        if (evt.getButton() == evt.BUTTON3) {
            
            jMenuItemCopySelectedToClipboard.setEnabled(jTextAreaOutput.getSelectedText() != null);
            
            jPopupMenuCopyToClipboard.show(evt.getComponent(),evt.getX(),evt.getY());
        }
        
    }//GEN-LAST:event_jTextAreaOutputMouseReleased

    private void jButtonVerifyEEPROMActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonVerifyEEPROMActionPerformed
        
        try {
            String fileType = (String)jComboBoxEEPROMFileType.getSelectedItem();

            String file = (String)jComboBoxFileEEPROM.getSelectedItem();
            if ((file == null) || (file.length() == 0))
                return;

            addToHistory(jComboBoxFileEEPROM,file);
            
            m_actionThread.verifyEEPROM(m_avr,file,AvrdudeControl.String2FileFormat(fileType));
            
        } catch (Exception e) {
            showError("Error verifying EEPROM: " + e.getMessage());
        }
        
    }//GEN-LAST:event_jButtonVerifyEEPROMActionPerformed

    private void jButtonVerifyFlashActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonVerifyFlashActionPerformed

        try {
            String fileType = (String)jComboBoxFlashFileType.getSelectedItem();

            String file = (String)jComboBoxFileFlash.getSelectedItem();
            if ((file == null) || (file.length() == 0))
                return;

            addToHistory(jComboBoxFileFlash,file);
            
            m_actionThread.verifyFlash(m_avr,file,AvrdudeControl.String2FileFormat(fileType));

        } catch (Exception e) {
            showError("Error verifying Flash: " + e.getMessage());
        }

    }//GEN-LAST:event_jButtonVerifyFlashActionPerformed

    private void jMenuItem3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem3ActionPerformed

        m_formAvrdudeSettings.setVisible(true);

    }//GEN-LAST:event_jMenuItem3ActionPerformed

    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        
        m_formAbout.setVisible(true);
        
    }//GEN-LAST:event_jMenuItem2ActionPerformed

    private void jButtonWriteEEPROMActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonWriteEEPROMActionPerformed
        
        try {
            String fileType = (String)jComboBoxEEPROMFileType.getSelectedItem();
            
            String file = (String)jComboBoxFileEEPROM.getSelectedItem();
            if ((file == null) || (file.length() == 0))
                return;
            
            addToHistory(jComboBoxFileEEPROM,file);
            
            m_actionThread.writeEEPROM(m_avr,file,AvrdudeControl.String2FileFormat(fileType));

        } catch (Exception e) {
            showError("Error writing EEPROM: " + e.getMessage());
        }

    }//GEN-LAST:event_jButtonWriteEEPROMActionPerformed

    private void jButtonReadEEPROMActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonReadEEPROMActionPerformed
        
        try {
            String fileType = (String)jComboBoxEEPROMFileType.getSelectedItem();

            String file = (String)jComboBoxFileEEPROM.getSelectedItem();
            if ((file == null) || (file.length() == 0))
                return;
            
            addToHistory(jComboBoxFileEEPROM,file);
            
            if ((new File(file)).exists()) {
                int r = JOptionPane.showConfirmDialog(this,"File already exists! Do you want to overwrite the existing file?");

                if (r != 0)
                    return;
            }

            m_actionThread.readEEPROM(m_avr,file,AvrdudeControl.String2FileFormat(fileType));

        } catch (Exception e) {
            showError("Error reading EEPROM: " + e.getMessage());
        }
        
    }//GEN-LAST:event_jButtonReadEEPROMActionPerformed

    private void jButtonWriteFlashActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonWriteFlashActionPerformed
        
        try {
            String fileType = (String)jComboBoxFlashFileType.getSelectedItem();
            
            String file = (String)jComboBoxFileFlash.getSelectedItem();
            if ((file == null) || (file.length() == 0))
                return;
            
            addToHistory(jComboBoxFileFlash,file);
            
            m_actionThread.writeFlash(m_avr,file,AvrdudeControl.String2FileFormat(fileType));
            
        } catch (Exception e) {
            showError("Error writing Flash: " + e.getMessage());
        }
        
    }//GEN-LAST:event_jButtonWriteFlashActionPerformed

    private void jButtonReadFlashActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonReadFlashActionPerformed
        
        try {
            String fileType = (String)jComboBoxFlashFileType.getSelectedItem();

            String file = (String)jComboBoxFileFlash.getSelectedItem();
            if ((file == null) || (file.length() == 0))
                return;

            addToHistory(jComboBoxFileFlash,file);
            
            if ((new File(file)).exists()) {
                int r = JOptionPane.showConfirmDialog(this,"File already exists! Do you want to overwrite the existing file?");

                if (r != 0)
                    return;
            }

            m_actionThread.readFlash(m_avr,file,AvrdudeControl.String2FileFormat(fileType));
            
        } catch (Exception e) {
            showError("Error reading Flash: " + e.getMessage());
        }
        
    }//GEN-LAST:event_jButtonReadFlashActionPerformed
  
    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        
        ExitProgram();
        
    }//GEN-LAST:event_formWindowClosing
    
    private void jButtonFileEEPROMActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonFileEEPROMActionPerformed
        
        int state = m_fileChooserEEPROM.showOpenDialog(null);
        if (state == JFileChooser.APPROVE_OPTION) {
            File file = m_fileChooserEEPROM.getSelectedFile();
            jComboBoxFileEEPROM.setSelectedItem(file.getPath());
            
            addToHistory(jComboBoxFileEEPROM,file.getPath());
        }
        
    }//GEN-LAST:event_jButtonFileEEPROMActionPerformed
    
    private void jButtonFileFlashActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonFileFlashActionPerformed
        
        int state = m_fileChooserFlash.showOpenDialog(null);
        if (state == JFileChooser.APPROVE_OPTION) {
            File file = m_fileChooserFlash.getSelectedFile();
            jComboBoxFileFlash.setSelectedItem(file.getPath());
            
            addToHistory(jComboBoxFileFlash,file.getPath());
        }
        
    }//GEN-LAST:event_jButtonFileFlashActionPerformed
    
    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        
        ExitProgram();
        
    }//GEN-LAST:event_jMenuItem1ActionPerformed
    
    private void jComboBoxAvrItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_jComboBoxAvrItemStateChanged
        
        String s = (String)jComboBoxAvr.getSelectedItem();
        
        for (AVR avr : m_avrList) {
            if (avr.getCaption().equals(s)) {
                m_avr = avr;
                m_formFuses.setAVR(avr);
                break;
            }
        }
        
    }//GEN-LAST:event_jComboBoxAvrItemStateChanged
    
    private void jButtonFusesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonFusesActionPerformed
        
        if (m_avr == null)
            showError("Please select an AVR type first!");
        else
            m_formFuses.setVisible(true);
        
    }//GEN-LAST:event_jButtonFusesActionPerformed

    public void ExitProgram() {
        
        savePreferences();
        m_formFuses.savePreferences();
        m_formAvrdudeSettings.savePreferences();
        m_avrdudeCtrl.savePreferences();
        
        System.exit(0);
    }

    private void showError(String s) {
        JOptionPane.showMessageDialog(this, s, getTitle(), JOptionPane.ERROR_MESSAGE);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String args[ ]) {
        
        UIManager.installLookAndFeel("Substance","org.jvnet.substance.SubstanceLookAndFeel");
        
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                
                FormMain formMain = new FormMain();
                formMain.setVisible(true);
            }
        });
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButtonFileEEPROM;
    private javax.swing.JButton jButtonFileFlash;
    private javax.swing.JButton jButtonFuses;
    private javax.swing.JButton jButtonReadEEPROM;
    private javax.swing.JButton jButtonReadFlash;
    private javax.swing.JButton jButtonVerifyEEPROM;
    private javax.swing.JButton jButtonVerifyFlash;
    private javax.swing.JButton jButtonWriteEEPROM;
    private javax.swing.JButton jButtonWriteFlash;
    private javax.swing.JComboBox jComboBoxAvr;
    private javax.swing.JComboBox jComboBoxEEPROMFileType;
    private javax.swing.JComboBox jComboBoxFileEEPROM;
    private javax.swing.JComboBox jComboBoxFileFlash;
    private javax.swing.JComboBox jComboBoxFlashFileType;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenu jMenu3;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JMenuItem jMenuItem3;
    private javax.swing.JMenuItem jMenuItemAllToClipboard;
    private javax.swing.JMenuItem jMenuItemClearOutput;
    private javax.swing.JMenuItem jMenuItemCopySelectedToClipboard;
    private javax.swing.JMenu jMenuLookAndFeel;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel6;
    private javax.swing.JPanel jPanel7;
    private javax.swing.JPopupMenu jPopupMenuCopyToClipboard;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JSplitPane jSplitPane1;
    private javax.swing.JTextArea jTextAreaOutput;
    // End of variables declaration//GEN-END:variables
    
}
