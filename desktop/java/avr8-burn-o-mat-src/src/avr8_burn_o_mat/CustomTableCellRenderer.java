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

import java.awt.Color;
import java.awt.Component;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableModel;

public class CustomTableCellRenderer extends DefaultTableCellRenderer {
    
    private TableModelFuses m_tableModelFuses;
    
    /** Creates a new instance of CustomTableCellRenderer */
    public CustomTableCellRenderer(TableModelFuses tableModelFuses) {
        m_tableModelFuses = tableModelFuses;
    }
    
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected,
            boolean hasFocus, int row, int column) {
        
        Component cell = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        
        if (m_tableModelFuses.isRowEditable(row)) {
            cell.setBackground(Color.white);
        } else {
            cell.setBackground(Color.red);
        }
        
        return cell;
        
    }
}

