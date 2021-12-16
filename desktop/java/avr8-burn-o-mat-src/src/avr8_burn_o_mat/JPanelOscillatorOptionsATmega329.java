/*
    AVR8 Burn-O-Mat
 
    Copyright (C) 2009  Torsten Brischalle

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

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.AbstractButton;
import javax.swing.JOptionPane;

public class JPanelOscillatorOptionsATmega329 extends JPanelOscillatorOptions {
    
    private Fuse.FuseState CKDIV8;
    private Fuse.FuseState CKOUT;
    private Fuse.FuseState[] CKSEL = new Fuse.FuseState[4];
    private Fuse.FuseState[] SUT = new Fuse.FuseState[2];
    
    private boolean m_fusesAreValid = false;
    private boolean m_preventUpdateFuses = false;
    
    /** Creates new form JPanelOscillatorOptionsATmega8 */
    public JPanelOscillatorOptionsATmega329(FusesEditor fusesEditor) {
        super(fusesEditor);
        
        initComponents();
        
        addSettingsChangedListener(jRadioButtonExtClockStartBod);
        addSettingsChangedListener(jRadioButtonExtClockStartFast);
        addSettingsChangedListener(jRadioButtonExtClockStartSlowly);
        
        addSettingsChangedListener(jRadioButtonExtLowXtalStartFast);
        addSettingsChangedListener(jRadioButtonExtLowXtalStartSlowly);
        addSettingsChangedListener(jRadioButtonExtLowXtalStartStable);
        
        addSettingsChangedListener(jRadioButtonExtXtalFreq04);
        addSettingsChangedListener(jRadioButtonExtXtalFreq09);
        addSettingsChangedListener(jRadioButtonExtXtalFreq30);
        addSettingsChangedListener(jRadioButtonExtXtalFreq80);
        addSettingsChangedListener(jRadioButtonExtXtalStartBod);
        addSettingsChangedListener(jRadioButtonExtXtalStartFast);
        addSettingsChangedListener(jRadioButtonExtXtalStartSlowly);
        addSettingsChangedListener(jRadioButtonExtXtalTypeCeramic);
        addSettingsChangedListener(jRadioButtonExtXtalTypeCrystal);

        addSettingsChangedListener(jRadioButtonIntRcOsciStartBod);
        addSettingsChangedListener(jRadioButtonIntRcOsciStartFast);
        addSettingsChangedListener(jRadioButtonIntRcOsciStartSlowly);
    
        fusesChanged();
    }
    
    public void fusesChanged() {
        
        try {
            updateGuiFromFuses();
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null,"Error fuses changed: " + ex.getMessage());
        }
        
        ensureValidSettings();
    }    

    private void loadFuses() throws Exception {
        
        CKDIV8 = m_fusesEditor.getFuse("CKDIV8");
        CKOUT = m_fusesEditor.getFuse("CKOUT");

        CKSEL[0] = m_fusesEditor.getFuse("CKSEL0");
        CKSEL[1] = m_fusesEditor.getFuse("CKSEL1");
        CKSEL[2] = m_fusesEditor.getFuse("CKSEL2");
        CKSEL[3] = m_fusesEditor.getFuse("CKSEL3");

        SUT[0] = m_fusesEditor.getFuse("SUT0");
        SUT[1] = m_fusesEditor.getFuse("SUT1");

        m_fusesAreValid = true;
    }
    
    private void storeFuses() throws Exception {
        
        if (!m_fusesAreValid)
            return;
        
        m_fusesEditor.setFuse("CKDIV8", CKDIV8);
        m_fusesEditor.setFuse("CKOUT", CKOUT);

        m_fusesEditor.setFuse("CKSEL0", CKSEL[0]);
        m_fusesEditor.setFuse("CKSEL1", CKSEL[1]);
        m_fusesEditor.setFuse("CKSEL2", CKSEL[2]);
        m_fusesEditor.setFuse("CKSEL3", CKSEL[3]);

        m_fusesEditor.setFuse("SUT0", SUT[0]);
        m_fusesEditor.setFuse("SUT1", SUT[1]);

        m_fusesEditor.getFusesObservable().fusesChanged(this);
    }
    
    private void ensureValidSettings() {
        
        if (jRadioButtonExtXtalTypeCrystal.isSelected()) {
            
            if (jRadioButtonExtXtalFreq04.isSelected())
                jRadioButtonExtXtalFreq09.setSelected(true);
            
            jRadioButtonExtXtalFreq04.setEnabled(false);
            
        } else
            jRadioButtonExtXtalFreq04.setEnabled(true);
        
    }
    
    private void updateFusesFromGui() throws Exception {
        
        if (!m_fusesAreValid || m_preventUpdateFuses)
            return;
        
        ensureValidSettings();
        
        Component c = jTabbedPaneClockSource.getSelectedComponent();
        
        if (c == jPanelIntRcOsci)
            updateFusesFromGuiIntRcOsci();
        else if (c == jPanelExtClock)
            updateFusesFromGuiExtClock();
        else if (c == jPanelExtLowXtal)
            updateFusesFromGuiExtLowXtal();
        else if (c == jPanelExtXtal)
            updateFusesFromGuiExtXtal();
        else
            throw new Exception("Internal error: updateFusesFromGui()");
        
        storeFuses();
    }

    private void updateFusesFromGuiIntRcOsci() throws Exception {
        
        CKSEL[3] = PROG;
        CKSEL[2] = PROG;
        CKSEL[1] = UNPROG;
        CKSEL[0] = PROG;
        
        if (jRadioButtonIntRcOsciStartBod.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = PROG;
        } else if (jRadioButtonIntRcOsciStartFast.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = UNPROG;
        } else if (jRadioButtonIntRcOsciStartSlowly.isSelected()) {
            SUT[1] = UNPROG;
            SUT[0] = PROG;
        } else
            throw new Exception("Internal error: updateFusesFromGuiIntRcOsci()");
    }
    
    private void updateFusesFromGuiExtClock() throws Exception {
        
        CKSEL[3] = PROG;
        CKSEL[2] = PROG;
        CKSEL[1] = PROG;
        CKSEL[0] = PROG;
        
        if (jRadioButtonExtClockStartBod.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = PROG;
        } else if (jRadioButtonExtClockStartFast.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = UNPROG;
        } else if (jRadioButtonExtClockStartSlowly.isSelected()) {
            SUT[1] = UNPROG;
            SUT[0] = PROG;
        } else
            throw new Exception("Internal error: updateFusesFromGuiExtClock()");
    }
    
    private void updateFusesFromGuiExtLowXtal() throws Exception {
        
        CKSEL[3] = PROG;
        CKSEL[2] = UNPROG;
        CKSEL[1] = UNPROG;
        CKSEL[0] = PROG;
        
        if (jRadioButtonExtLowXtalStartFast.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = PROG;
        } else if (jRadioButtonExtLowXtalStartSlowly.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = UNPROG;
        } else if (jRadioButtonExtLowXtalStartStable.isSelected()) {
            SUT[1] = UNPROG;
            SUT[0] = PROG;
        } else
            throw new Exception("Internal error: updateFusesFromGuiExtLowXtal()");
    }
    
    private void updateFusesFromGuiExtXtal() throws Exception {
        
        if (jRadioButtonExtXtalFreq04.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = PROG;
            CKSEL[1] = PROG;
        } else if (jRadioButtonExtXtalFreq09.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = PROG;
            CKSEL[1] = UNPROG;
        } else if (jRadioButtonExtXtalFreq30.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = UNPROG;
            CKSEL[1] = PROG;
        } else if (jRadioButtonExtXtalFreq80.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = UNPROG;
            CKSEL[1] = UNPROG;
        } else
            throw new Exception("Internal error: updateFusesFromGuiExtXtal()");
        
        if (jRadioButtonExtXtalTypeCrystal.isSelected()) {
            
            if (jRadioButtonExtXtalStartFast.isSelected()) {
                CKSEL[0] = UNPROG;
                SUT[1] = UNPROG;
                SUT[0] = PROG;
            } else if (jRadioButtonExtXtalStartSlowly.isSelected()) {
                CKSEL[0] = UNPROG;
                SUT[1] = UNPROG;
                SUT[0] = UNPROG;
            } else if (jRadioButtonExtXtalStartBod.isSelected()) {
                CKSEL[0] = UNPROG;
                SUT[1] = PROG;
                SUT[0] = UNPROG;
            } else
                throw new Exception("Internal error: updateFusesFromGuiExtXtal()");
            
        } else if (jRadioButtonExtXtalTypeCeramic.isSelected()) {
            
            if (jRadioButtonExtXtalStartFast.isSelected()) {
                CKSEL[0] = PROG;
                SUT[1] = UNPROG;
                SUT[0] = UNPROG;
            } else if (jRadioButtonExtXtalStartSlowly.isSelected()) {
                CKSEL[0] = UNPROG;
                SUT[1] = PROG;
                SUT[0] = PROG;
            } else if (jRadioButtonExtXtalStartBod.isSelected()) {
                CKSEL[0] = PROG;
                SUT[1] = UNPROG;
                SUT[0] = PROG;
            } else
                throw new Exception("Internal error: updateFusesFromGuiExtXtal()");
            
        } else
            throw new Exception("Internal error: updateFusesFromGuiExtXtal()");
    }
    
    private void updateGuiFromFuses() throws Exception {
        
        m_preventUpdateFuses = true;
        
        try {
            
            loadFuses();

            switch (getFusesInt(CKSEL)) {
                case 0:
                    updateGuiFromFusesExtClock();
                    break;

                case 1: // reserved
                case 3: // reserved
                case 4: // reserved
                case 5: // reserved
                    
                case 2:    
                    updateGuiFromFusesIntRcOsci();
                    break;

                case 6:    
                case 7:    
                    updateGuiFromFusesExtLowXtal();
                    break;

                case 8:    
                case 9:    
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    updateGuiFromFusesExtXtal();
                    break;
                    
                default:
                    throw new Exception("Internal error: updateGuiFromFuses()");
            }
            
        } finally {
            m_preventUpdateFuses = false;
        }
        
        ensureValidSettings();
    }
    
    private void updateGuiFromFusesExtClock() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jPanelExtClock);
        
        switch (getFusesInt(SUT)) {
            case 0:
                jRadioButtonExtClockStartBod.setSelected(true);
                break;
                
            case 1:
                jRadioButtonExtClockStartFast.setSelected(true);
                break;
                
            case 2:
            default:
                jRadioButtonExtClockStartSlowly.setSelected(true);
                break;
        }
    }
    
    private void updateGuiFromFusesIntRcOsci() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jPanelIntRcOsci);
        
        switch (getFusesInt(SUT)) {
            case 0:
                jRadioButtonIntRcOsciStartBod.setSelected(true);
                break;
                
            case 1:
                jRadioButtonIntRcOsciStartFast.setSelected(true);
                break;
                
            case 2:
            default:
                jRadioButtonIntRcOsciStartSlowly.setSelected(true);
                break;
        }
    }
    
    private void updateGuiFromFusesExtLowXtal() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jPanelExtLowXtal);
        
        switch (getFusesInt(SUT)) {
            case 0:
                jRadioButtonExtLowXtalStartFast.setSelected(true);
                break;
                
            case 1:
                jRadioButtonExtLowXtalStartSlowly.setSelected(true);
                break;
                
            case 2:
            default:
                jRadioButtonExtLowXtalStartStable.setSelected(true);
                break;
        }
    }
    
    private void updateGuiFromFusesExtXtal() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jPanelExtXtal);
        
        switch (getFusesInt(CKSEL) >> 1) {
            case 4:
                jRadioButtonExtXtalFreq04.setSelected(true);
                break;
            case 5:
                jRadioButtonExtXtalFreq09.setSelected(true);
                break;
            case 6:
                jRadioButtonExtXtalFreq30.setSelected(true);
                break;
            case 7:
                jRadioButtonExtXtalFreq80.setSelected(true);
                break;
        }
        
        int i = getFusesInt(SUT) | ((getFusesInt(CKSEL) & 1) << 2);
        
        if ((i >= 0) && (i <= 4))
            jRadioButtonExtXtalTypeCeramic.setSelected(true);
        else if ((i >= 5) && (i <= 7))
            jRadioButtonExtXtalTypeCrystal.setSelected(true);
        else
            throw new Exception("Internal error: updateGuiFromFusesExtXtal()");

        switch (i) {
            case 2:
            case 5:
                jRadioButtonExtXtalStartBod.setSelected(true);
                break;
                
            case 0:
            case 3:
            case 6:
                jRadioButtonExtXtalStartFast.setSelected(true);
                break;
                
            case 1:
            case 4:
            case 7:
                jRadioButtonExtXtalStartSlowly.setSelected(true);
                break;
                
            default:
                throw new Exception("Internal error: updateGuiFromFusesExtXtal()");
        }
    }
    
    private void settingsChanged() {
        
        try {
            updateFusesFromGui();
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null,"Error update fuses: " + ex.getMessage());
        }
    }
    
    private void addSettingsChangedListener(AbstractButton bttn) {
        
        bttn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                settingsChanged();
            }
        });
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroupExtRcOsciFreqRange = new javax.swing.ButtonGroup();
        buttonGroupExtRcOsciStartTime = new javax.swing.ButtonGroup();
        buttonGroupIntRcOsciNomFreq = new javax.swing.ButtonGroup();
        buttonGroupIntRcOsciStartTime = new javax.swing.ButtonGroup();
        buttonGroupExtClockStartTime = new javax.swing.ButtonGroup();
        buttonGroupExtLowXtalStartTime = new javax.swing.ButtonGroup();
        buttonGroupExtXtalType = new javax.swing.ButtonGroup();
        buttonGroupExtXtalFreqRange = new javax.swing.ButtonGroup();
        buttonGroupExtXtalAmpMode = new javax.swing.ButtonGroup();
        buttonGroupExtXtalStartTime = new javax.swing.ButtonGroup();
        jTabbedPaneClockSource = new javax.swing.JTabbedPane();
        jPanelIntRcOsci = new javax.swing.JPanel();
        jPanel5 = new javax.swing.JPanel();
        jRadioButtonIntRcOsciStartFast = new javax.swing.JRadioButton();
        jRadioButtonIntRcOsciStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonIntRcOsciStartBod = new javax.swing.JRadioButton();
        jLabel2 = new javax.swing.JLabel();
        jPanelExtClock = new javax.swing.JPanel();
        jPanel6 = new javax.swing.JPanel();
        jRadioButtonExtClockStartFast = new javax.swing.JRadioButton();
        jRadioButtonExtClockStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonExtClockStartBod = new javax.swing.JRadioButton();
        jLabel6 = new javax.swing.JLabel();
        jPanelExtLowXtal = new javax.swing.JPanel();
        jPanel7 = new javax.swing.JPanel();
        jRadioButtonExtLowXtalStartFast = new javax.swing.JRadioButton();
        jRadioButtonExtLowXtalStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonExtLowXtalStartStable = new javax.swing.JRadioButton();
        jLabel1 = new javax.swing.JLabel();
        jPanelExtXtal = new javax.swing.JPanel();
        jPanel8 = new javax.swing.JPanel();
        jRadioButtonExtXtalTypeCrystal = new javax.swing.JRadioButton();
        jRadioButtonExtXtalTypeCeramic = new javax.swing.JRadioButton();
        jPanel9 = new javax.swing.JPanel();
        jRadioButtonExtXtalFreq04 = new javax.swing.JRadioButton();
        jRadioButtonExtXtalFreq09 = new javax.swing.JRadioButton();
        jRadioButtonExtXtalFreq30 = new javax.swing.JRadioButton();
        jRadioButtonExtXtalFreq80 = new javax.swing.JRadioButton();
        jPanel10 = new javax.swing.JPanel();
        jRadioButtonExtXtalStartFast = new javax.swing.JRadioButton();
        jRadioButtonExtXtalStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonExtXtalStartBod = new javax.swing.JRadioButton();
        jPanel1 = new javax.swing.JPanel();
        jCheckBoxDivClockBy8 = new javax.swing.JCheckBox();
        jCheckBoxOutputClock = new javax.swing.JCheckBox();

        setLayout(new java.awt.BorderLayout());

        jTabbedPaneClockSource.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                jTabbedPaneClockSourceStateChanged(evt);
            }
        });

        jPanel5.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupIntRcOsciStartTime.add(jRadioButtonIntRcOsciStartFast);
        jRadioButtonIntRcOsciStartFast.setText("fast rising power");

        buttonGroupIntRcOsciStartTime.add(jRadioButtonIntRcOsciStartSlowly);
        jRadioButtonIntRcOsciStartSlowly.setSelected(true);
        jRadioButtonIntRcOsciStartSlowly.setText("slowly rising power");

        buttonGroupIntRcOsciStartTime.add(jRadioButtonIntRcOsciStartBod);
        jRadioButtonIntRcOsciStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel5Layout = new javax.swing.GroupLayout(jPanel5);
        jPanel5.setLayout(jPanel5Layout);
        jPanel5Layout.setHorizontalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel5Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonIntRcOsciStartFast)
                    .addComponent(jRadioButtonIntRcOsciStartSlowly)
                    .addComponent(jRadioButtonIntRcOsciStartBod))
                .addContainerGap(374, Short.MAX_VALUE))
        );
        jPanel5Layout.setVerticalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel5Layout.createSequentialGroup()
                .addComponent(jRadioButtonIntRcOsciStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonIntRcOsciStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonIntRcOsciStartBod))
        );

        jLabel2.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel2.setText("8.0MHz calibrated internal RC oscillator");

        javax.swing.GroupLayout jPanelIntRcOsciLayout = new javax.swing.GroupLayout(jPanelIntRcOsci);
        jPanelIntRcOsci.setLayout(jPanelIntRcOsciLayout);
        jPanelIntRcOsciLayout.setHorizontalGroup(
            jPanelIntRcOsciLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelIntRcOsciLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelIntRcOsciLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel2)
                    .addComponent(jPanel5, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelIntRcOsciLayout.setVerticalGroup(
            jPanelIntRcOsciLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelIntRcOsciLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel2)
                .addGap(18, 18, 18)
                .addComponent(jPanel5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(264, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("Calibrated internal RC oscillator", jPanelIntRcOsci);

        jPanel6.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupExtClockStartTime.add(jRadioButtonExtClockStartFast);
        jRadioButtonExtClockStartFast.setText("fast rising power");

        buttonGroupExtClockStartTime.add(jRadioButtonExtClockStartSlowly);
        jRadioButtonExtClockStartSlowly.setSelected(true);
        jRadioButtonExtClockStartSlowly.setText("slowly rising power");

        buttonGroupExtClockStartTime.add(jRadioButtonExtClockStartBod);
        jRadioButtonExtClockStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel6Layout = new javax.swing.GroupLayout(jPanel6);
        jPanel6.setLayout(jPanel6Layout);
        jPanel6Layout.setHorizontalGroup(
            jPanel6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel6Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonExtClockStartFast)
                    .addComponent(jRadioButtonExtClockStartSlowly)
                    .addComponent(jRadioButtonExtClockStartBod))
                .addContainerGap(374, Short.MAX_VALUE))
        );
        jPanel6Layout.setVerticalGroup(
            jPanel6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel6Layout.createSequentialGroup()
                .addComponent(jRadioButtonExtClockStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtClockStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtClockStartBod))
        );

        jLabel6.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel6.setText("0MHz - 20MHz external clock");

        javax.swing.GroupLayout jPanelExtClockLayout = new javax.swing.GroupLayout(jPanelExtClock);
        jPanelExtClock.setLayout(jPanelExtClockLayout);
        jPanelExtClockLayout.setHorizontalGroup(
            jPanelExtClockLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtClockLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelExtClockLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel6)
                    .addComponent(jPanel6, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelExtClockLayout.setVerticalGroup(
            jPanelExtClockLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtClockLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel6)
                .addGap(18, 18, 18)
                .addComponent(jPanel6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(264, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("External clock", jPanelExtClock);

        jPanel7.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupExtLowXtalStartTime.add(jRadioButtonExtLowXtalStartFast);
        jRadioButtonExtLowXtalStartFast.setText("fast rising power or brown out detection enabled");

        buttonGroupExtLowXtalStartTime.add(jRadioButtonExtLowXtalStartSlowly);
        jRadioButtonExtLowXtalStartSlowly.setSelected(true);
        jRadioButtonExtLowXtalStartSlowly.setText("slowly rising power");

        buttonGroupExtLowXtalStartTime.add(jRadioButtonExtLowXtalStartStable);
        jRadioButtonExtLowXtalStartStable.setText("stable frequency at start-up");

        javax.swing.GroupLayout jPanel7Layout = new javax.swing.GroupLayout(jPanel7);
        jPanel7.setLayout(jPanel7Layout);
        jPanel7Layout.setHorizontalGroup(
            jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel7Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonExtLowXtalStartFast)
                    .addComponent(jRadioButtonExtLowXtalStartSlowly)
                    .addComponent(jRadioButtonExtLowXtalStartStable))
                .addContainerGap(249, Short.MAX_VALUE))
        );
        jPanel7Layout.setVerticalGroup(
            jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel7Layout.createSequentialGroup()
                .addComponent(jRadioButtonExtLowXtalStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtLowXtalStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtLowXtalStartStable))
        );

        jLabel1.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel1.setText("32.768kHz watch crystal");

        javax.swing.GroupLayout jPanelExtLowXtalLayout = new javax.swing.GroupLayout(jPanelExtLowXtal);
        jPanelExtLowXtal.setLayout(jPanelExtLowXtalLayout);
        jPanelExtLowXtalLayout.setHorizontalGroup(
            jPanelExtLowXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtLowXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelExtLowXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel7, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jLabel1))
                .addContainerGap())
        );
        jPanelExtLowXtalLayout.setVerticalGroup(
            jPanelExtLowXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtLowXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addGap(18, 18, 18)
                .addComponent(jPanel7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(264, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("External low-frequency crystal", jPanelExtLowXtal);

        jPanel8.setBorder(javax.swing.BorderFactory.createTitledBorder("Type"));

        buttonGroupExtXtalType.add(jRadioButtonExtXtalTypeCrystal);
        jRadioButtonExtXtalTypeCrystal.setSelected(true);
        jRadioButtonExtXtalTypeCrystal.setText("crystal");

        buttonGroupExtXtalType.add(jRadioButtonExtXtalTypeCeramic);
        jRadioButtonExtXtalTypeCeramic.setText("ceramic resonator");

        javax.swing.GroupLayout jPanel8Layout = new javax.swing.GroupLayout(jPanel8);
        jPanel8.setLayout(jPanel8Layout);
        jPanel8Layout.setHorizontalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel8Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonExtXtalTypeCrystal)
                    .addComponent(jRadioButtonExtXtalTypeCeramic))
                .addContainerGap(439, Short.MAX_VALUE))
        );
        jPanel8Layout.setVerticalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel8Layout.createSequentialGroup()
                .addComponent(jRadioButtonExtXtalTypeCrystal)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtXtalTypeCeramic))
        );

        jPanel9.setBorder(javax.swing.BorderFactory.createTitledBorder("Frequency range"));

        buttonGroupExtXtalFreqRange.add(jRadioButtonExtXtalFreq04);
        jRadioButtonExtXtalFreq04.setText("0.4MHz - 0.9MHz (for ceramic resonators only!)");

        buttonGroupExtXtalFreqRange.add(jRadioButtonExtXtalFreq09);
        jRadioButtonExtXtalFreq09.setText("0.9MHz - 3.0MHz");

        buttonGroupExtXtalFreqRange.add(jRadioButtonExtXtalFreq30);
        jRadioButtonExtXtalFreq30.setSelected(true);
        jRadioButtonExtXtalFreq30.setText("3.0MHz - 8.0MHz");

        buttonGroupExtXtalFreqRange.add(jRadioButtonExtXtalFreq80);
        jRadioButtonExtXtalFreq80.setText(">= 8.0MHz");

        javax.swing.GroupLayout jPanel9Layout = new javax.swing.GroupLayout(jPanel9);
        jPanel9.setLayout(jPanel9Layout);
        jPanel9Layout.setHorizontalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonExtXtalFreq04)
                    .addComponent(jRadioButtonExtXtalFreq09)
                    .addComponent(jRadioButtonExtXtalFreq30)
                    .addComponent(jRadioButtonExtXtalFreq80))
                .addContainerGap(253, Short.MAX_VALUE))
        );
        jPanel9Layout.setVerticalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addComponent(jRadioButtonExtXtalFreq04)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtXtalFreq09)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtXtalFreq30)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtXtalFreq80))
        );

        jPanel10.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupExtXtalStartTime.add(jRadioButtonExtXtalStartFast);
        jRadioButtonExtXtalStartFast.setText("fast rising power");

        buttonGroupExtXtalStartTime.add(jRadioButtonExtXtalStartSlowly);
        jRadioButtonExtXtalStartSlowly.setSelected(true);
        jRadioButtonExtXtalStartSlowly.setText("slowly rising power");

        buttonGroupExtXtalStartTime.add(jRadioButtonExtXtalStartBod);
        jRadioButtonExtXtalStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel10Layout = new javax.swing.GroupLayout(jPanel10);
        jPanel10.setLayout(jPanel10Layout);
        jPanel10Layout.setHorizontalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonExtXtalStartFast)
                    .addComponent(jRadioButtonExtXtalStartSlowly)
                    .addComponent(jRadioButtonExtXtalStartBod))
                .addContainerGap(374, Short.MAX_VALUE))
        );
        jPanel10Layout.setVerticalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addComponent(jRadioButtonExtXtalStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtXtalStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonExtXtalStartBod)
                .addContainerGap())
        );

        javax.swing.GroupLayout jPanelExtXtalLayout = new javax.swing.GroupLayout(jPanelExtXtal);
        jPanelExtXtal.setLayout(jPanelExtXtalLayout);
        jPanelExtXtalLayout.setHorizontalGroup(
            jPanelExtXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelExtXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel8, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel9, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel10, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelExtXtalLayout.setVerticalGroup(
            jPanelExtXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jPanel10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(37, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("External crystal or ceramic resonator", jPanelExtXtal);

        add(jTabbedPaneClockSource, java.awt.BorderLayout.CENTER);

        jPanel1.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        jPanel1.setPreferredSize(new java.awt.Dimension(100, 80));

        jCheckBoxDivClockBy8.setText("divide system clock by 8");

        jCheckBoxOutputClock.setText("output system clock on pin CLKO (pin PE7)");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jCheckBoxDivClockBy8)
                    .addComponent(jCheckBoxOutputClock))
                .addContainerGap(325, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jCheckBoxDivClockBy8)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jCheckBoxOutputClock)
                .addContainerGap(14, Short.MAX_VALUE))
        );

        add(jPanel1, java.awt.BorderLayout.NORTH);
    }// </editor-fold>//GEN-END:initComponents

private void jTabbedPaneClockSourceStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_jTabbedPaneClockSourceStateChanged
    settingsChanged();
}//GEN-LAST:event_jTabbedPaneClockSourceStateChanged


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.ButtonGroup buttonGroupExtClockStartTime;
    private javax.swing.ButtonGroup buttonGroupExtLowXtalStartTime;
    private javax.swing.ButtonGroup buttonGroupExtRcOsciFreqRange;
    private javax.swing.ButtonGroup buttonGroupExtRcOsciStartTime;
    private javax.swing.ButtonGroup buttonGroupExtXtalAmpMode;
    private javax.swing.ButtonGroup buttonGroupExtXtalFreqRange;
    private javax.swing.ButtonGroup buttonGroupExtXtalStartTime;
    private javax.swing.ButtonGroup buttonGroupExtXtalType;
    private javax.swing.ButtonGroup buttonGroupIntRcOsciNomFreq;
    private javax.swing.ButtonGroup buttonGroupIntRcOsciStartTime;
    private javax.swing.JCheckBox jCheckBoxDivClockBy8;
    private javax.swing.JCheckBox jCheckBoxOutputClock;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel10;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel6;
    private javax.swing.JPanel jPanel7;
    private javax.swing.JPanel jPanel8;
    private javax.swing.JPanel jPanel9;
    private javax.swing.JPanel jPanelExtClock;
    private javax.swing.JPanel jPanelExtLowXtal;
    private javax.swing.JPanel jPanelExtXtal;
    private javax.swing.JPanel jPanelIntRcOsci;
    private javax.swing.JRadioButton jRadioButtonExtClockStartBod;
    private javax.swing.JRadioButton jRadioButtonExtClockStartFast;
    private javax.swing.JRadioButton jRadioButtonExtClockStartSlowly;
    private javax.swing.JRadioButton jRadioButtonExtLowXtalStartFast;
    private javax.swing.JRadioButton jRadioButtonExtLowXtalStartSlowly;
    private javax.swing.JRadioButton jRadioButtonExtLowXtalStartStable;
    private javax.swing.JRadioButton jRadioButtonExtXtalFreq04;
    private javax.swing.JRadioButton jRadioButtonExtXtalFreq09;
    private javax.swing.JRadioButton jRadioButtonExtXtalFreq30;
    private javax.swing.JRadioButton jRadioButtonExtXtalFreq80;
    private javax.swing.JRadioButton jRadioButtonExtXtalStartBod;
    private javax.swing.JRadioButton jRadioButtonExtXtalStartFast;
    private javax.swing.JRadioButton jRadioButtonExtXtalStartSlowly;
    private javax.swing.JRadioButton jRadioButtonExtXtalTypeCeramic;
    private javax.swing.JRadioButton jRadioButtonExtXtalTypeCrystal;
    private javax.swing.JRadioButton jRadioButtonIntRcOsciStartBod;
    private javax.swing.JRadioButton jRadioButtonIntRcOsciStartFast;
    private javax.swing.JRadioButton jRadioButtonIntRcOsciStartSlowly;
    private javax.swing.JTabbedPane jTabbedPaneClockSource;
    // End of variables declaration//GEN-END:variables

}
