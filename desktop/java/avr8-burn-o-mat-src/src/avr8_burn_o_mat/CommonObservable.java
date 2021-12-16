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

public abstract class CommonObservable <T_Observer> {
    
    protected Vector <T_Observer> m_observerList;
    
    public CommonObservable() {
        m_observerList = new Vector <T_Observer>();
    }
    
    public synchronized void addObserver(T_Observer o) {
        int idx;
        
        for (idx = 0; idx < m_observerList.size(); idx++) {
            if (m_observerList.elementAt(idx) == o)
                return;
        }
        
        m_observerList.add(o);
    }
    
    public synchronized void removeObserver(T_Observer o) {
        int idx;
        
        for (idx = 0; idx < m_observerList.size(); idx++) {
            if (m_observerList.elementAt(idx) == o) {
                m_observerList.remove(idx);
                break;
            }
        }
    }
    
    
}

