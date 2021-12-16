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

class ActionThread implements Runnable {
    
    public enum Action {
        IDLE,
        WRITE_FLASH,
        WRITE_FLASH_DONE,
        WRITE_FLASH_ERROR,
        READ_FLASH,
        READ_FLASH_DONE,
        READ_FLASH_ERROR,
        VERIFY_FLASH,
        VERIFY_FLASH_DONE,
        VERIFY_FLASH_ERROR,
        WRITE_FUSES,
        WRITE_FUSES_DONE,
        WRITE_FUSES_ERROR,
        READ_FUSES,
        READ_FUSES_DONE,
        READ_FUSES_ERROR,
        VERIFY_FUSES,
        VERIFY_FUSES_DONE,
        VERIFY_FUSES_ERROR,
        WRITE_EEPROM,
        WRITE_EEPROM_DONE,
        WRITE_EEPROM_ERROR,
        READ_EEPROM,
        READ_EEPROM_DONE,
        READ_EEPROM_ERROR,
        VERIFY_EEPROM,
        VERIFY_EEPROM_DONE,
        VERIFY_EEPROM_ERROR
    }
    
    public interface Observer {
        public void actionThreadStateChanged(Action newState);
    }
    
    public class Observable extends CommonObservable <Observer> {
        public void actionThreadStateChanged(Object sender, Action newState) {
            for (Observer o : m_observerList) {
                if (o != sender)
                    o.actionThreadStateChanged(newState);
            }
        }
    }
    
    Observable m_observable = new Observable();
    
    private String m_errorMsg = "";
    
    private Action m_action = Action.IDLE;
    
    private AvrdudeControl m_avrdudeCtrl;
    
    private AVR m_avr;
    
    private String m_filename;
    
    private AvrdudeControl.FileFormat m_fileFormat;
    
    public ActionThread(AvrdudeControl avrdudeCtrl) {
        m_avrdudeCtrl = avrdudeCtrl;
    }
    
    public void writeFuses(AVR avr) {
        assert m_action == Action.IDLE;
        
        m_action = Action.WRITE_FUSES;
        m_avr = avr;
        m_filename = null;
        m_fileFormat = null;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void readFuses(AVR avr) {
        assert m_action == Action.IDLE;
        
        m_action = Action.READ_FUSES;
        m_avr = avr;
        m_filename = null;
        m_fileFormat = null;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void verifyFuses(AVR avr) {
        assert m_action == Action.IDLE;
        
        m_action = Action.VERIFY_FUSES;
        m_avr = avr;
        m_filename = null;
        m_fileFormat = null;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void writeFlash(AVR avr, String filename, AvrdudeControl.FileFormat format) {
        assert m_action == Action.IDLE;
        
        m_action = Action.WRITE_FLASH;
        m_avr = avr;
        m_filename = filename;
        m_fileFormat = format;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void readFlash(AVR avr, String filename, AvrdudeControl.FileFormat format) {
        assert m_action == Action.IDLE;
        
        m_action = Action.READ_FLASH;
        m_avr = avr;
        m_filename = filename;
        m_fileFormat = format;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void verifyFlash(AVR avr, String filename, AvrdudeControl.FileFormat format) {
        assert m_action == Action.IDLE;
        
        m_action = Action.VERIFY_FLASH;
        m_avr = avr;
        m_filename = filename;
        m_fileFormat = format;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void writeEEPROM(AVR avr, String filename, AvrdudeControl.FileFormat format) {
        assert m_action == Action.IDLE;
        
        m_action = Action.WRITE_EEPROM;
        m_avr = avr;
        m_filename = filename;
        m_fileFormat = format;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void readEEPROM(AVR avr, String filename, AvrdudeControl.FileFormat format) {
        assert m_action == Action.IDLE;
        
        m_action = Action.READ_EEPROM;
        m_avr = avr;
        m_filename = filename;
        m_fileFormat = format;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void verifyEEPROM(AVR avr, String filename, AvrdudeControl.FileFormat format) {
        assert m_action == Action.IDLE;
        
        m_action = Action.VERIFY_EEPROM;
        m_avr = avr;
        m_filename = filename;
        m_fileFormat = format;
        
        Thread t = new Thread(this);
        t.start();
    }
    
    public void run() {
        
        try {
            m_observable.actionThreadStateChanged(this, m_action);
            
            synchronized (m_avrdudeCtrl) {
                
                switch (m_action) {
                    case WRITE_FLASH:
                        m_avrdudeCtrl.writeFlash(m_avr,m_filename,m_fileFormat);
                        m_action = Action.WRITE_FLASH_DONE;
                        break;
                        
                    case READ_FLASH:
                        m_avrdudeCtrl.readFlash(m_avr,m_filename,m_fileFormat);
                        m_action = Action.READ_FLASH_DONE;
                        break;
                        
                    case VERIFY_FLASH:
                        m_avrdudeCtrl.verifyFlash(m_avr,m_filename,m_fileFormat);
                        m_action = Action.VERIFY_FLASH_DONE;
                        break;
                        
                    case WRITE_FUSES:
                        m_avrdudeCtrl.writeFuses(m_avr);
                        m_action = Action.WRITE_FUSES_DONE;
                        break;
                        
                    case READ_FUSES:
                        m_avrdudeCtrl.readFuses(m_avr);
                        m_action = Action.READ_FUSES_DONE;
                        break;
                        
                    case VERIFY_FUSES:
                        m_avrdudeCtrl.verifyFuses(m_avr);
                        m_action = Action.VERIFY_FUSES_DONE;
                        break;
                        
                    case WRITE_EEPROM:
                        m_avrdudeCtrl.writeEEPROM(m_avr,m_filename,m_fileFormat);
                        m_action =Action. WRITE_EEPROM_DONE;
                        break;
                        
                    case READ_EEPROM:
                        m_avrdudeCtrl.readEEPROM(m_avr,m_filename,m_fileFormat);
                        m_action = Action.READ_EEPROM_DONE;
                        break;
                        
                    case VERIFY_EEPROM:
                        m_avrdudeCtrl.verifyEEPROM(m_avr,m_filename,m_fileFormat);
                        m_action = Action.VERIFY_EEPROM_DONE;
                        break;
                        
                    default:
                        assert false;
                }
            }
            
            m_observable.actionThreadStateChanged(this, m_action);
            
        } catch (Exception e) {
            
            switch (m_action) {
                case WRITE_FLASH:   m_action = Action.WRITE_FLASH_ERROR;    break;
                case READ_FLASH:    m_action = Action.READ_FLASH_ERROR;     break;
                case VERIFY_FLASH:  m_action = Action.VERIFY_FLASH_ERROR;   break;
                case WRITE_FUSES:   m_action = Action.WRITE_FUSES_ERROR;    break;
                case READ_FUSES:    m_action = Action.READ_FUSES_ERROR;     break;
                case VERIFY_FUSES:  m_action = Action.VERIFY_FUSES_ERROR;   break;
                case WRITE_EEPROM:  m_action = Action. WRITE_EEPROM_ERROR;  break;
                case READ_EEPROM:   m_action = Action.READ_EEPROM_ERROR;    break;
                case VERIFY_EEPROM: m_action = Action.VERIFY_EEPROM_ERROR;  break;
                default: assert false;
            }
            
            m_errorMsg = e.getMessage();
            
            m_observable.actionThreadStateChanged(this, m_action);
        }
            
        m_action = Action.IDLE;
        
        m_observable.actionThreadStateChanged(this, m_action);
        
    }
    
    public String getLastErrorMsg() {
        return m_errorMsg;
    }
}

