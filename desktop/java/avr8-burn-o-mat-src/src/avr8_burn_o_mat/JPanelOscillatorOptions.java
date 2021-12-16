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

import java.awt.event.ContainerAdapter;
import java.awt.event.ContainerEvent;

public abstract class JPanelOscillatorOptions
extends javax.swing.JPanel
implements FusesObserver {
    
    protected final Fuse.FuseState PROG = Fuse.FuseState.PROGRAMMED;
    protected final Fuse.FuseState UNPROG = Fuse.FuseState.UNPROGRAMMED;
    
    protected FusesEditor m_fusesEditor;
    
    public JPanelOscillatorOptions(FusesEditor fusesEditor) {
    
        m_fusesEditor = fusesEditor;
        
        m_fusesEditor.getFusesObservable().addObserver(this);
        
    }
    
    public void destroy() {
        m_fusesEditor.getFusesObservable().removeObserver(this);
    }
    
    public abstract void fusesChanged();
    
    protected int getFusesInt(Fuse.FuseState[] fuses) throws Exception {
        
        int val = 0, i;

        for (i = 0; i < fuses.length; i++)
            val |= (Fuse.FuseState2Integer(fuses[i]) << i);

        return val;
    }

}
