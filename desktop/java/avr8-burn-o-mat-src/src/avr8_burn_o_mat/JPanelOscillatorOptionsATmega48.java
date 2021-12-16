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

public class JPanelOscillatorOptionsATmega48 extends JPanelOscillatorOptions {
    
    private Fuse.FuseState CKDIV8;
    private Fuse.FuseState CKOUT;
    private Fuse.FuseState[] CKSEL = new Fuse.FuseState[4];
    private Fuse.FuseState[] SUT = new Fuse.FuseState[2];
    
    private boolean m_fusesAreValid = false;
    private boolean m_preventUpdateFuses = false;
    
    /** Creates new form JPanelOscillatorOptionsATmega8 */
    public JPanelOscillatorOptionsATmega48(FusesEditor fusesEditor) {
        super(fusesEditor);
        
        initComponents();

        addSettingsChangedListener(jCheckBoxDivClockBy8);
        addSettingsChangedListener(jCheckBoxOutputClock);
        addSettingsChangedListener(jRadioButtonExtClockStartBod);
        addSettingsChangedListener(jRadioButtonExtClockStartFast);
        addSettingsChangedListener(jRadioButtonExtClockStartSlowly);
        addSettingsChangedListener(jRadioButtonFullSwingStartBod);
        addSettingsChangedListener(jRadioButtonFullSwingStartFast);
        addSettingsChangedListener(jRadioButtonFullSwingStartSlowly);
        addSettingsChangedListener(jRadioButtonFullSwingTypeCeramic);
        addSettingsChangedListener(jRadioButtonFullSwingTypeCrystal);
        addSettingsChangedListener(jRadioButtonIntRc128OsciStartBod);
        addSettingsChangedListener(jRadioButtonIntRc128OsciStartFast);
        addSettingsChangedListener(jRadioButtonIntRc128OsciStartSlowly);
        addSettingsChangedListener(jRadioButtonIntRcOsciStartBod);
        addSettingsChangedListener(jRadioButtonIntRcOsciStartFast);
        addSettingsChangedListener(jRadioButtonIntRcOsciStartSlowly);
        addSettingsChangedListener(jRadioButtonLowFreqStartBod);
        addSettingsChangedListener(jRadioButtonLowFreqStartFast);
        addSettingsChangedListener(jRadioButtonLowFreqStartSlowly);
        addSettingsChangedListener(jRadioButtonLowPwrFreq04);
        addSettingsChangedListener(jRadioButtonLowPwrFreq09);
        addSettingsChangedListener(jRadioButtonLowPwrFreq30);
        addSettingsChangedListener(jRadioButtonLowPwrFreq80);
        addSettingsChangedListener(jRadioButtonLowPwrStartBod);
        addSettingsChangedListener(jRadioButtonLowPwrStartFast);
        addSettingsChangedListener(jRadioButtonLowPwrStartSlowly);
        addSettingsChangedListener(jRadioButtonLowPwrTypeCeramic);
        addSettingsChangedListener(jRadioButtonLowPwrTypeCrystal);
        
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

    private void ensureValidSettings() {
        
        if (jRadioButtonLowPwrTypeCrystal.isSelected()) {
            
            if (jRadioButtonLowPwrFreq04.isSelected())
                jRadioButtonLowPwrFreq09.setSelected(true);
            
            jRadioButtonLowPwrFreq04.setEnabled(false);
            
        } else
            jRadioButtonLowPwrFreq04.setEnabled(true);
        
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
    
    private void updateFusesFromGui() throws Exception {
        
        if (!m_fusesAreValid || m_preventUpdateFuses)
            return;
        
        ensureValidSettings();
        
        Component c = jTabbedPaneClockSource.getSelectedComponent();
        
        if (c == jPanelIntRcOsci128kHz)
            updateFusesFromGuiIntRcOsci128kHz();
        else if (c == jPanelIntRcOsci)
            updateFusesFromGuiIntRcOsci();
        else if (c == jPanelExtClock)
            updateFusesFromGuiExtClock();
        else if (c == jPanelLowFreqXtal)
            updateFusesFromGuiLowFreqXtal();
        else if (c == jScrollPaneFullSwingXtal)
            updateFusesFromGuiFullSwingXtal();
        else if (c == jScrollPaneLowPwrXtal)
            updateFusesFromGuiLowPwrXtal();
        else
            throw new Exception("Internal error: updateFusesFromGui()");
        
        CKDIV8 = jCheckBoxDivClockBy8.isSelected() ? PROG : UNPROG;
        CKOUT = jCheckBoxOutputClock.isSelected() ? PROG : UNPROG;
            
        storeFuses();
    }

    private void updateFusesFromGuiIntRcOsci128kHz() throws Exception {
        
        CKSEL[3] = PROG;
        CKSEL[2] = PROG;
        CKSEL[1] = UNPROG;
        CKSEL[0] = UNPROG;
        
        if (jRadioButtonIntRc128OsciStartBod.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = PROG;
        } else if (jRadioButtonIntRc128OsciStartFast.isSelected()) {
            SUT[1] = PROG;
            SUT[0] = UNPROG;
        } else if (jRadioButtonIntRc128OsciStartSlowly.isSelected()) {
            SUT[1] = UNPROG;
            SUT[0] = PROG;
        } else
            throw new Exception("Internal error: updateFusesFromGuiIntRcOsci128kHz()");
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
            throw new Exception("Internal error: updateFusesFromGuiExtClock()");
    }
    
    private void updateFusesFromGuiLowFreqXtal() throws Exception {
        
        CKSEL[3] = PROG;
        CKSEL[2] = UNPROG;
        CKSEL[1] = PROG;
        CKSEL[0] = UNPROG;
        
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
            throw new Exception("Internal error: updateFusesFromGuiLowFreqXtal()");
    }
    
    private void updateFusesFromGuiFullSwingXtal() throws Exception {
        
        CKSEL[3] = PROG;
        CKSEL[2] = UNPROG;
        CKSEL[1] = UNPROG;
        
        if (jRadioButtonFullSwingTypeCrystal.isSelected()) {
            
            CKSEL[0] = UNPROG;

            if (jRadioButtonFullSwingStartBod.isSelected()) {
                SUT[1] = PROG;
                SUT[0] = UNPROG;
            } else if (jRadioButtonFullSwingStartFast.isSelected()) {
                SUT[1] = UNPROG;
                SUT[0] = PROG;
            } else if (jRadioButtonFullSwingStartSlowly.isSelected()) {
                SUT[1] = UNPROG;
                SUT[0] = UNPROG;
            } else
                throw new Exception("Internal error: updateFusesFromGuiFullSwingXtal()");
            
        } else if (jRadioButtonFullSwingTypeCeramic.isSelected()) {

            if (jRadioButtonFullSwingStartBod.isSelected()) {
                CKSEL[0] = PROG;
                SUT[1] = UNPROG;
                SUT[0] = PROG;
            } else if (jRadioButtonFullSwingStartFast.isSelected()) {
                CKSEL[0] = PROG;
                SUT[1] = UNPROG;
                SUT[0] = UNPROG;
            } else if (jRadioButtonFullSwingStartSlowly.isSelected()) {
                CKSEL[0] = UNPROG;
                SUT[1] = PROG;
                SUT[0] = PROG;
            } else
                throw new Exception("Internal error: updateFusesFromGuiFullSwingXtal()");

        } else
            throw new Exception("Internal error: updateFusesFromGuiFullSwingXtal()");
    }
    
    private void updateFusesFromGuiLowPwrXtal() throws Exception {
        
        if (jRadioButtonLowPwrFreq04.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = PROG;
            CKSEL[1] = PROG;
        } else if (jRadioButtonLowPwrFreq09.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = PROG;
            CKSEL[1] = UNPROG;
        } else if (jRadioButtonLowPwrFreq30.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = UNPROG;
            CKSEL[1] = PROG;
        } else if (jRadioButtonLowPwrFreq80.isSelected()) {
            CKSEL[3] = UNPROG;
            CKSEL[2] = UNPROG;
            CKSEL[1] = UNPROG;
        } else
            throw new Exception("Internal error: updateFusesFromGuiLowPwrXtal()");
        
        if (jRadioButtonLowPwrTypeCrystal.isSelected()) {
            
            CKSEL[0] = UNPROG;

            if (jRadioButtonLowPwrStartBod.isSelected()) {
                SUT[1] = PROG;
                SUT[0] = UNPROG;
            } else if (jRadioButtonLowPwrStartFast.isSelected()) {
                SUT[1] = UNPROG;
                SUT[0] = PROG;
            } else if (jRadioButtonLowPwrStartSlowly.isSelected()) {
                SUT[1] = UNPROG;
                SUT[0] = UNPROG;
            } else
                throw new Exception("Internal error: updateFusesFromGuiLowPwrXtal()");
            
        } else if (jRadioButtonLowPwrTypeCeramic.isSelected()) {

            if (jRadioButtonLowPwrStartBod.isSelected()) {
                CKSEL[0] = PROG;
                SUT[1] = UNPROG;
                SUT[0] = PROG;
            } else if (jRadioButtonLowPwrStartFast.isSelected()) {
                CKSEL[0] = PROG;
                SUT[1] = UNPROG;
                SUT[0] = UNPROG;
            } else if (jRadioButtonLowPwrStartSlowly.isSelected()) {
                CKSEL[0] = UNPROG;
                SUT[1] = PROG;
                SUT[0] = PROG;
            } else
                throw new Exception("Internal error: updateFusesFromGuiLowPwrXtal()");

        } else
            throw new Exception("Internal error: updateFusesFromGuiLowPwrXtal()");
    }
    
    private void updateGuiFromFuses() throws Exception {
        
        m_preventUpdateFuses = true;
        
        try {
            
            loadFuses();

            switch (getFusesInt(CKSEL)) {
                case 0:
                    updateGuiFromFusesExtClock();
                    break;

                case 1:    // reserved
                case 2:    
                    updateGuiFromFusesIntRcOsci();
                    break;
                    
                case 3:    
                    updateGuiFromFusesIntRcOsci128kHz();
                    break;
                    
                case 4:    
                case 5:    
                    updateGuiFromFusesLowFreqXtal();
                    break;

                case 6:    
                case 7:    
                    updateGuiFromFusesFullSwingXtal();
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    updateGuiFromFusesLowPwrXtal();
                    break;
                    
                default:
                    throw new Exception("Internal error: updateGuiFromFuses()");
            }
            
        } finally {
            m_preventUpdateFuses = false;
        }
        
        jCheckBoxDivClockBy8.setSelected(CKDIV8 == PROG);
        jCheckBoxOutputClock.setSelected(CKOUT == PROG);
        
        ensureValidSettings();
    }

    private void updateGuiFromFusesIntRcOsci128kHz() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jPanelIntRcOsci128kHz);
        
        switch (getFusesInt(SUT)) {
            case 0:
                jRadioButtonIntRc128OsciStartBod.setSelected(true);
                break;
                
            case 1:
                jRadioButtonIntRc128OsciStartFast.setSelected(true);
                break;
                
            case 2:
            default:
                jRadioButtonIntRc128OsciStartSlowly.setSelected(true);
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
    
    private void updateGuiFromFusesLowFreqXtal() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jPanelLowFreqXtal);
        
        switch (getFusesInt(SUT)) {
            case 0:
                jRadioButtonLowFreqStartBod.setSelected(true);
                break;
                
            case 1:
                jRadioButtonLowFreqStartFast.setSelected(true);
                break;
                
            case 2:
            default:
                jRadioButtonLowFreqStartSlowly.setSelected(true);
                break;
        }
    }
    
    private void updateGuiFromFusesFullSwingXtal() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jScrollPaneFullSwingXtal);
        
        int i = getFusesInt(SUT) | ((getFusesInt(CKSEL) & 1) << 2);
        
        if ((i >= 0) && (i <= 4))
            jRadioButtonFullSwingTypeCeramic.setSelected(true);
        else if ((i >= 5) && (i <= 7))
            jRadioButtonFullSwingTypeCrystal.setSelected(true);
        else
            throw new Exception("Internal error: updateGuiFromFusesFullSwingXtal()");
        
        switch (i) {
            case 2:
            case 5:
                jRadioButtonFullSwingStartBod.setSelected(true);
                break;
                
            case 0:
            case 3:
            case 6:
                jRadioButtonFullSwingStartFast.setSelected(true);
                break;
                
            case 1:
            case 4:
            case 7:
                jRadioButtonFullSwingStartSlowly.setSelected(true);
                break;
                
            default:
                throw new Exception("Internal error: updateGuiFromFusesFullSwingXtal()");
        }
    }
    
    private void updateGuiFromFusesLowPwrXtal() throws Exception {
        
        jTabbedPaneClockSource.setSelectedComponent(jScrollPaneLowPwrXtal);
        
        int i = getFusesInt(SUT) | ((getFusesInt(CKSEL) & 1) << 2);
        
        if ((i >= 0) && (i <= 4))
            jRadioButtonLowPwrTypeCeramic.setSelected(true);
        else if ((i >= 5) && (i <= 7))
            jRadioButtonLowPwrTypeCrystal.setSelected(true);
        else
            throw new Exception("Internal error: updateGuiFromFusesLowPwrXtal()");
        
        switch (i) {
            case 2:
            case 5:
                jRadioButtonLowPwrStartBod.setSelected(true);
                break;
                
            case 0:
            case 3:
            case 6:
                jRadioButtonLowPwrStartFast.setSelected(true);
                break;
                
            case 1:
            case 4:
            case 7:
                jRadioButtonLowPwrStartSlowly.setSelected(true);
                break;
                
            default:
                throw new Exception("Internal error: updateGuiFromFusesLowPwrXtal()");
        }
        
        i = getFusesInt(CKSEL) >> 1;
        
        switch (i) {
            case 4:
                jRadioButtonLowPwrFreq04.setSelected(true);
                break;
                
            case 5:
                jRadioButtonLowPwrFreq09.setSelected(true);
                break;
                
            case 6:
                jRadioButtonLowPwrFreq30.setSelected(true);
                break;
                
            case 7:
                jRadioButtonLowPwrFreq80.setSelected(true);
                break;
                
            default:
                throw new Exception("Internal error: updateGuiFromFusesLowPwrXtal()");
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

        buttonGroupIntRc128Osci = new javax.swing.ButtonGroup();
        buttonGroupIntRcOsci = new javax.swing.ButtonGroup();
        buttonGroupExtClock = new javax.swing.ButtonGroup();
        buttonGroupLowFreq = new javax.swing.ButtonGroup();
        buttonGroupFullSwingType = new javax.swing.ButtonGroup();
        buttonGroupFullSwingStart = new javax.swing.ButtonGroup();
        buttonGroupLowPwrType = new javax.swing.ButtonGroup();
        buttonGroupLowPwrFreq = new javax.swing.ButtonGroup();
        buttonGroupLowPwrStart = new javax.swing.ButtonGroup();
        jTabbedPaneClockSource = new javax.swing.JTabbedPane();
        jPanelIntRcOsci128kHz = new javax.swing.JPanel();
        jPanel3 = new javax.swing.JPanel();
        jRadioButtonIntRc128OsciStartFast = new javax.swing.JRadioButton();
        jRadioButtonIntRc128OsciStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonIntRc128OsciStartBod = new javax.swing.JRadioButton();
        jLabel3 = new javax.swing.JLabel();
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
        jPanelLowFreqXtal = new javax.swing.JPanel();
        jPanel13 = new javax.swing.JPanel();
        jRadioButtonLowFreqStartFast = new javax.swing.JRadioButton();
        jRadioButtonLowFreqStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonLowFreqStartBod = new javax.swing.JRadioButton();
        jLabel1 = new javax.swing.JLabel();
        jScrollPaneFullSwingXtal = new javax.swing.JScrollPane();
        jPanelFullSwingXtal = new javax.swing.JPanel();
        jPanel11 = new javax.swing.JPanel();
        jRadioButtonFullSwingTypeCrystal = new javax.swing.JRadioButton();
        jRadioButtonFullSwingTypeCeramic = new javax.swing.JRadioButton();
        jPanel12 = new javax.swing.JPanel();
        jRadioButtonFullSwingStartFast = new javax.swing.JRadioButton();
        jRadioButtonFullSwingStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonFullSwingStartBod = new javax.swing.JRadioButton();
        jLabel4 = new javax.swing.JLabel();
        jScrollPaneLowPwrXtal = new javax.swing.JScrollPane();
        jPanelLowPwrXtal = new javax.swing.JPanel();
        jPanel9 = new javax.swing.JPanel();
        jRadioButtonLowPwrFreq04 = new javax.swing.JRadioButton();
        jRadioButtonLowPwrFreq09 = new javax.swing.JRadioButton();
        jRadioButtonLowPwrFreq30 = new javax.swing.JRadioButton();
        jRadioButtonLowPwrFreq80 = new javax.swing.JRadioButton();
        jPanel8 = new javax.swing.JPanel();
        jRadioButtonLowPwrTypeCrystal = new javax.swing.JRadioButton();
        jRadioButtonLowPwrTypeCeramic = new javax.swing.JRadioButton();
        jPanel10 = new javax.swing.JPanel();
        jRadioButtonLowPwrStartFast = new javax.swing.JRadioButton();
        jRadioButtonLowPwrStartSlowly = new javax.swing.JRadioButton();
        jRadioButtonLowPwrStartBod = new javax.swing.JRadioButton();
        jLabel5 = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();
        jCheckBoxDivClockBy8 = new javax.swing.JCheckBox();
        jCheckBoxOutputClock = new javax.swing.JCheckBox();

        setLayout(new java.awt.BorderLayout());

        jTabbedPaneClockSource.setPreferredSize(new java.awt.Dimension(220, 160));
        jTabbedPaneClockSource.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                jTabbedPaneClockSourceStateChanged(evt);
            }
        });

        jPanel3.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupIntRc128Osci.add(jRadioButtonIntRc128OsciStartFast);
        jRadioButtonIntRc128OsciStartFast.setText("fast rising power");

        buttonGroupIntRc128Osci.add(jRadioButtonIntRc128OsciStartSlowly);
        jRadioButtonIntRc128OsciStartSlowly.setSelected(true);
        jRadioButtonIntRc128OsciStartSlowly.setText("slowly rising power");

        buttonGroupIntRc128Osci.add(jRadioButtonIntRc128OsciStartBod);
        jRadioButtonIntRc128OsciStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonIntRc128OsciStartFast)
                    .addComponent(jRadioButtonIntRc128OsciStartSlowly)
                    .addComponent(jRadioButtonIntRc128OsciStartBod))
                .addContainerGap(407, Short.MAX_VALUE))
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addComponent(jRadioButtonIntRc128OsciStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonIntRc128OsciStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonIntRc128OsciStartBod))
        );

        jLabel3.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel3.setText("128kHz internal low power oscillator");

        javax.swing.GroupLayout jPanelIntRcOsci128kHzLayout = new javax.swing.GroupLayout(jPanelIntRcOsci128kHz);
        jPanelIntRcOsci128kHz.setLayout(jPanelIntRcOsci128kHzLayout);
        jPanelIntRcOsci128kHzLayout.setHorizontalGroup(
            jPanelIntRcOsci128kHzLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelIntRcOsci128kHzLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelIntRcOsci128kHzLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel3)
                    .addComponent(jPanel3, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelIntRcOsci128kHzLayout.setVerticalGroup(
            jPanelIntRcOsci128kHzLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelIntRcOsci128kHzLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel3)
                .addGap(18, 18, 18)
                .addComponent(jPanel3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(301, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("Internal 128kHz RC oscillator", jPanelIntRcOsci128kHz);

        jPanel5.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupIntRcOsci.add(jRadioButtonIntRcOsciStartFast);
        jRadioButtonIntRcOsciStartFast.setText("fast rising power");

        buttonGroupIntRcOsci.add(jRadioButtonIntRcOsciStartSlowly);
        jRadioButtonIntRcOsciStartSlowly.setSelected(true);
        jRadioButtonIntRcOsciStartSlowly.setText("slowly rising power");

        buttonGroupIntRcOsci.add(jRadioButtonIntRcOsciStartBod);
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
                .addContainerGap(407, Short.MAX_VALUE))
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
                    .addComponent(jPanel5, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelIntRcOsciLayout.setVerticalGroup(
            jPanelIntRcOsciLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelIntRcOsciLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel2)
                .addGap(18, 18, 18)
                .addComponent(jPanel5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(301, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("Calibrated internal RC oscillator", jPanelIntRcOsci);

        jPanel6.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupExtClock.add(jRadioButtonExtClockStartFast);
        jRadioButtonExtClockStartFast.setText("fast rising power");

        buttonGroupExtClock.add(jRadioButtonExtClockStartSlowly);
        jRadioButtonExtClockStartSlowly.setSelected(true);
        jRadioButtonExtClockStartSlowly.setText("slowly rising power");

        buttonGroupExtClock.add(jRadioButtonExtClockStartBod);
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
                .addContainerGap(407, Short.MAX_VALUE))
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
                    .addComponent(jPanel6, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelExtClockLayout.setVerticalGroup(
            jPanelExtClockLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelExtClockLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel6)
                .addGap(18, 18, 18)
                .addComponent(jPanel6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(301, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("External clock", jPanelExtClock);

        jPanel13.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupLowFreq.add(jRadioButtonLowFreqStartFast);
        jRadioButtonLowFreqStartFast.setText("fast rising power");

        buttonGroupLowFreq.add(jRadioButtonLowFreqStartSlowly);
        jRadioButtonLowFreqStartSlowly.setSelected(true);
        jRadioButtonLowFreqStartSlowly.setText("slowly rising power");

        buttonGroupLowFreq.add(jRadioButtonLowFreqStartBod);
        jRadioButtonLowFreqStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel13Layout = new javax.swing.GroupLayout(jPanel13);
        jPanel13.setLayout(jPanel13Layout);
        jPanel13Layout.setHorizontalGroup(
            jPanel13Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel13Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel13Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonLowFreqStartFast)
                    .addComponent(jRadioButtonLowFreqStartSlowly)
                    .addComponent(jRadioButtonLowFreqStartBod))
                .addContainerGap(407, Short.MAX_VALUE))
        );
        jPanel13Layout.setVerticalGroup(
            jPanel13Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel13Layout.createSequentialGroup()
                .addComponent(jRadioButtonLowFreqStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowFreqStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowFreqStartBod)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jLabel1.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel1.setText("32.768kHz watch crystal");

        javax.swing.GroupLayout jPanelLowFreqXtalLayout = new javax.swing.GroupLayout(jPanelLowFreqXtal);
        jPanelLowFreqXtal.setLayout(jPanelLowFreqXtalLayout);
        jPanelLowFreqXtalLayout.setHorizontalGroup(
            jPanelLowFreqXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelLowFreqXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelLowFreqXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel13, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jLabel1))
                .addContainerGap())
        );
        jPanelLowFreqXtalLayout.setVerticalGroup(
            jPanelLowFreqXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelLowFreqXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addGap(18, 18, 18)
                .addComponent(jPanel13, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(289, Short.MAX_VALUE))
        );

        jTabbedPaneClockSource.addTab("Low frequency crystal oscillator", jPanelLowFreqXtal);

        jPanel11.setBorder(javax.swing.BorderFactory.createTitledBorder("Type"));

        buttonGroupFullSwingType.add(jRadioButtonFullSwingTypeCrystal);
        jRadioButtonFullSwingTypeCrystal.setSelected(true);
        jRadioButtonFullSwingTypeCrystal.setText("crystal");

        buttonGroupFullSwingType.add(jRadioButtonFullSwingTypeCeramic);
        jRadioButtonFullSwingTypeCeramic.setText("ceramic resonator");

        javax.swing.GroupLayout jPanel11Layout = new javax.swing.GroupLayout(jPanel11);
        jPanel11.setLayout(jPanel11Layout);
        jPanel11Layout.setHorizontalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel11Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonFullSwingTypeCrystal)
                    .addComponent(jRadioButtonFullSwingTypeCeramic))
                .addContainerGap(472, Short.MAX_VALUE))
        );
        jPanel11Layout.setVerticalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel11Layout.createSequentialGroup()
                .addComponent(jRadioButtonFullSwingTypeCrystal)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonFullSwingTypeCeramic))
        );

        jPanel12.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupFullSwingStart.add(jRadioButtonFullSwingStartFast);
        jRadioButtonFullSwingStartFast.setText("fast rising power");

        buttonGroupFullSwingStart.add(jRadioButtonFullSwingStartSlowly);
        jRadioButtonFullSwingStartSlowly.setSelected(true);
        jRadioButtonFullSwingStartSlowly.setText("slowly rising power");

        buttonGroupFullSwingStart.add(jRadioButtonFullSwingStartBod);
        jRadioButtonFullSwingStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel12Layout = new javax.swing.GroupLayout(jPanel12);
        jPanel12.setLayout(jPanel12Layout);
        jPanel12Layout.setHorizontalGroup(
            jPanel12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel12Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonFullSwingStartFast)
                    .addComponent(jRadioButtonFullSwingStartSlowly)
                    .addComponent(jRadioButtonFullSwingStartBod))
                .addContainerGap(407, Short.MAX_VALUE))
        );
        jPanel12Layout.setVerticalGroup(
            jPanel12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel12Layout.createSequentialGroup()
                .addComponent(jRadioButtonFullSwingStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonFullSwingStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonFullSwingStartBod)
                .addContainerGap())
        );

        jLabel4.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel4.setText("0.4MHz - 20MHz full swing crystal/ceramic resonator oscillator");

        javax.swing.GroupLayout jPanelFullSwingXtalLayout = new javax.swing.GroupLayout(jPanelFullSwingXtal);
        jPanelFullSwingXtal.setLayout(jPanelFullSwingXtalLayout);
        jPanelFullSwingXtalLayout.setHorizontalGroup(
            jPanelFullSwingXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelFullSwingXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelFullSwingXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel12, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jLabel4)
                    .addComponent(jPanel11, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelFullSwingXtalLayout.setVerticalGroup(
            jPanelFullSwingXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelFullSwingXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel4)
                .addGap(18, 18, 18)
                .addComponent(jPanel11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jPanel12, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(192, Short.MAX_VALUE))
        );

        jScrollPaneFullSwingXtal.setViewportView(jPanelFullSwingXtal);

        jTabbedPaneClockSource.addTab("Full swing crystal oscillator", jScrollPaneFullSwingXtal);

        jPanel9.setBorder(javax.swing.BorderFactory.createTitledBorder("Frequency range"));

        buttonGroupLowPwrFreq.add(jRadioButtonLowPwrFreq04);
        jRadioButtonLowPwrFreq04.setText("0.4MHz - 0.9MHz (for ceramic resonators only!)");

        buttonGroupLowPwrFreq.add(jRadioButtonLowPwrFreq09);
        jRadioButtonLowPwrFreq09.setText("0.9MHz - 3.0MHz");

        buttonGroupLowPwrFreq.add(jRadioButtonLowPwrFreq30);
        jRadioButtonLowPwrFreq30.setSelected(true);
        jRadioButtonLowPwrFreq30.setText("3.0MHz - 8.0MHz");

        buttonGroupLowPwrFreq.add(jRadioButtonLowPwrFreq80);
        jRadioButtonLowPwrFreq80.setText("8.0MHz - 16.0MHz");

        javax.swing.GroupLayout jPanel9Layout = new javax.swing.GroupLayout(jPanel9);
        jPanel9.setLayout(jPanel9Layout);
        jPanel9Layout.setHorizontalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonLowPwrFreq04)
                    .addComponent(jRadioButtonLowPwrFreq09)
                    .addComponent(jRadioButtonLowPwrFreq30)
                    .addComponent(jRadioButtonLowPwrFreq80))
                .addContainerGap(286, Short.MAX_VALUE))
        );
        jPanel9Layout.setVerticalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addComponent(jRadioButtonLowPwrFreq04)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowPwrFreq09)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowPwrFreq30)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowPwrFreq80))
        );

        jPanel8.setBorder(javax.swing.BorderFactory.createTitledBorder("Type"));

        buttonGroupLowPwrType.add(jRadioButtonLowPwrTypeCrystal);
        jRadioButtonLowPwrTypeCrystal.setSelected(true);
        jRadioButtonLowPwrTypeCrystal.setText("crystal");

        buttonGroupLowPwrType.add(jRadioButtonLowPwrTypeCeramic);
        jRadioButtonLowPwrTypeCeramic.setText("ceramic resonator");

        javax.swing.GroupLayout jPanel8Layout = new javax.swing.GroupLayout(jPanel8);
        jPanel8.setLayout(jPanel8Layout);
        jPanel8Layout.setHorizontalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel8Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonLowPwrTypeCrystal)
                    .addComponent(jRadioButtonLowPwrTypeCeramic))
                .addContainerGap(472, Short.MAX_VALUE))
        );
        jPanel8Layout.setVerticalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel8Layout.createSequentialGroup()
                .addComponent(jRadioButtonLowPwrTypeCrystal)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowPwrTypeCeramic))
        );

        jPanel10.setBorder(javax.swing.BorderFactory.createTitledBorder("Start-up time"));

        buttonGroupLowPwrStart.add(jRadioButtonLowPwrStartFast);
        jRadioButtonLowPwrStartFast.setText("fast rising power");

        buttonGroupLowPwrStart.add(jRadioButtonLowPwrStartSlowly);
        jRadioButtonLowPwrStartSlowly.setSelected(true);
        jRadioButtonLowPwrStartSlowly.setText("slowly rising power");

        buttonGroupLowPwrStart.add(jRadioButtonLowPwrStartBod);
        jRadioButtonLowPwrStartBod.setText("brown out detection enabled");

        javax.swing.GroupLayout jPanel10Layout = new javax.swing.GroupLayout(jPanel10);
        jPanel10.setLayout(jPanel10Layout);
        jPanel10Layout.setHorizontalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jRadioButtonLowPwrStartFast)
                    .addComponent(jRadioButtonLowPwrStartSlowly)
                    .addComponent(jRadioButtonLowPwrStartBod))
                .addContainerGap(407, Short.MAX_VALUE))
        );
        jPanel10Layout.setVerticalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addComponent(jRadioButtonLowPwrStartFast)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowPwrStartSlowly)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jRadioButtonLowPwrStartBod)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jLabel5.setFont(new java.awt.Font("DejaVu Sans", 0, 14));
        jLabel5.setText("0.4MHz - 20MHz low power crystal/ceramic resonator oscillator");

        javax.swing.GroupLayout jPanelLowPwrXtalLayout = new javax.swing.GroupLayout(jPanelLowPwrXtal);
        jPanelLowPwrXtal.setLayout(jPanelLowPwrXtalLayout);
        jPanelLowPwrXtalLayout.setHorizontalGroup(
            jPanelLowPwrXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelLowPwrXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelLowPwrXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel10, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jLabel5)
                    .addComponent(jPanel8, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel9, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanelLowPwrXtalLayout.setVerticalGroup(
            jPanelLowPwrXtalLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelLowPwrXtalLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel5)
                .addGap(18, 18, 18)
                .addComponent(jPanel8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jPanel10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(43, Short.MAX_VALUE))
        );

        jScrollPaneLowPwrXtal.setViewportView(jPanelLowPwrXtal);

        jTabbedPaneClockSource.addTab("Low power crystal oscillator", jScrollPaneLowPwrXtal);

        add(jTabbedPaneClockSource, java.awt.BorderLayout.CENTER);

        jPanel1.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        jPanel1.setPreferredSize(new java.awt.Dimension(100, 80));

        jCheckBoxDivClockBy8.setText("divide system clock by 8");

        jCheckBoxOutputClock.setText("output system clock on pin CLKO (pin PB0)");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jCheckBoxDivClockBy8)
                    .addComponent(jCheckBoxOutputClock))
                .addContainerGap(357, Short.MAX_VALUE))
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
    private javax.swing.ButtonGroup buttonGroupExtClock;
    private javax.swing.ButtonGroup buttonGroupFullSwingStart;
    private javax.swing.ButtonGroup buttonGroupFullSwingType;
    private javax.swing.ButtonGroup buttonGroupIntRc128Osci;
    private javax.swing.ButtonGroup buttonGroupIntRcOsci;
    private javax.swing.ButtonGroup buttonGroupLowFreq;
    private javax.swing.ButtonGroup buttonGroupLowPwrFreq;
    private javax.swing.ButtonGroup buttonGroupLowPwrStart;
    private javax.swing.ButtonGroup buttonGroupLowPwrType;
    private javax.swing.JCheckBox jCheckBoxDivClockBy8;
    private javax.swing.JCheckBox jCheckBoxOutputClock;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel10;
    private javax.swing.JPanel jPanel11;
    private javax.swing.JPanel jPanel12;
    private javax.swing.JPanel jPanel13;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel6;
    private javax.swing.JPanel jPanel8;
    private javax.swing.JPanel jPanel9;
    private javax.swing.JPanel jPanelExtClock;
    private javax.swing.JPanel jPanelFullSwingXtal;
    private javax.swing.JPanel jPanelIntRcOsci;
    private javax.swing.JPanel jPanelIntRcOsci128kHz;
    private javax.swing.JPanel jPanelLowFreqXtal;
    private javax.swing.JPanel jPanelLowPwrXtal;
    private javax.swing.JRadioButton jRadioButtonExtClockStartBod;
    private javax.swing.JRadioButton jRadioButtonExtClockStartFast;
    private javax.swing.JRadioButton jRadioButtonExtClockStartSlowly;
    private javax.swing.JRadioButton jRadioButtonFullSwingStartBod;
    private javax.swing.JRadioButton jRadioButtonFullSwingStartFast;
    private javax.swing.JRadioButton jRadioButtonFullSwingStartSlowly;
    private javax.swing.JRadioButton jRadioButtonFullSwingTypeCeramic;
    private javax.swing.JRadioButton jRadioButtonFullSwingTypeCrystal;
    private javax.swing.JRadioButton jRadioButtonIntRc128OsciStartBod;
    private javax.swing.JRadioButton jRadioButtonIntRc128OsciStartFast;
    private javax.swing.JRadioButton jRadioButtonIntRc128OsciStartSlowly;
    private javax.swing.JRadioButton jRadioButtonIntRcOsciStartBod;
    private javax.swing.JRadioButton jRadioButtonIntRcOsciStartFast;
    private javax.swing.JRadioButton jRadioButtonIntRcOsciStartSlowly;
    private javax.swing.JRadioButton jRadioButtonLowFreqStartBod;
    private javax.swing.JRadioButton jRadioButtonLowFreqStartFast;
    private javax.swing.JRadioButton jRadioButtonLowFreqStartSlowly;
    private javax.swing.JRadioButton jRadioButtonLowPwrFreq04;
    private javax.swing.JRadioButton jRadioButtonLowPwrFreq09;
    private javax.swing.JRadioButton jRadioButtonLowPwrFreq30;
    private javax.swing.JRadioButton jRadioButtonLowPwrFreq80;
    private javax.swing.JRadioButton jRadioButtonLowPwrStartBod;
    private javax.swing.JRadioButton jRadioButtonLowPwrStartFast;
    private javax.swing.JRadioButton jRadioButtonLowPwrStartSlowly;
    private javax.swing.JRadioButton jRadioButtonLowPwrTypeCeramic;
    private javax.swing.JRadioButton jRadioButtonLowPwrTypeCrystal;
    private javax.swing.JScrollPane jScrollPaneFullSwingXtal;
    private javax.swing.JScrollPane jScrollPaneLowPwrXtal;
    private javax.swing.JTabbedPane jTabbedPaneClockSource;
    // End of variables declaration//GEN-END:variables

}
