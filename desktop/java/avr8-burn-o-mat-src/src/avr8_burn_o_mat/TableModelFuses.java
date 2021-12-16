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

import java.util.Vector;
import javax.swing.table.AbstractTableModel;

public class TableModelFuses extends AbstractTableModel {
    
    private String[]        m_columnNames = { "Name", "programmed", "Description" };
    
    private Vector <Fuse>   m_fuses;
    
    private Fuse.FuseMode   m_fuseMode = Fuse.FuseMode.NORMAL;
    
    private FusesEditor     m_fusesEditor;
    
    public final int        COL_NAME = 0,
                            COL_STATE = 1,
                            COL_DESC = 2,
                            COL_COUNT = 3;
    
    public TableModelFuses(FusesEditor fusesEditor) {
        m_fusesEditor = fusesEditor;
    }
    
    public void setFuseList(Vector <Fuse> fuses) {
        m_fuses = fuses;
        fireTableStructureChanged();
    }
    
    public void fuseListUpdate() {
        fireTableStructureChanged();
    }
    
    public void resetToDefault() {

        if (m_fuses == null)
            return;
        
        for (Fuse fuse : m_fuses) {
            fuse.setFuseState(fuse.getDefaultFuseState());
        }
        
        fireTableDataChanged();
    }
    
    public Class getColumnClass(int columnIndex) {
        switch (columnIndex) {
            case COL_NAME:
            case COL_DESC:
                return String.class;
            case COL_STATE:
                return Boolean.class;
            default:
                assert false;
                return Object.class;
        }
    }
    
    public int getColumnCount() {
        return m_columnNames.length;
    }
    
    public String getColumnName(int columnIndex) {
        return m_columnNames[columnIndex];
    }
    
    public int getRowCount() {
        if (m_fuses != null)
            return m_fuses.size();
        else
            return 0;
    }
    
    public Object getValueAt(int rowIndex, int columnIndex) {

        if (m_fuses == null)
            return new Object();

        switch (columnIndex) {
            case COL_NAME:
                return m_fuses.elementAt(rowIndex).getName();
            case COL_STATE:
                return m_fuses.elementAt(rowIndex).isProgrammed();
            case COL_DESC:
                return m_fuses.elementAt(rowIndex).getDescription();
            default:
                assert false;
                return new Object();
        }
    }
    
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {

        if (m_fuses == null)
            return;

        if (columnIndex == COL_STATE) {
            Boolean b = (Boolean)aValue;
            
            if (b)
                m_fuses.elementAt(rowIndex).setFuseState(Fuse.FuseState.PROGRAMMED);
            else
                m_fuses.elementAt(rowIndex).setFuseState(Fuse.FuseState.UNPROGRAMMED);
            
            fireTableCellUpdated(rowIndex,columnIndex);
            
            m_fusesEditor.getFusesObservable().fusesChanged(this);
        }
    }
    
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        
        if (m_fuses == null)
            return false;
        
        if (columnIndex == COL_STATE) {
            
            if (m_fuseMode == Fuse.FuseMode.EXPERT)
                return true;
            else
                return m_fuses.elementAt(rowIndex).getFuseMode() == Fuse.FuseMode.NORMAL;
        }
        else
            return false;
    }
    
    public void setFuseMode(Fuse.FuseMode fuseMode) {
        
        m_fuseMode = fuseMode;
        fireTableStructureChanged();
        
    }
    
    public boolean isRowEditable(int row) {
        return isCellEditable(row,COL_STATE);
    }
}
