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

import java.util.Vector;
import org.w3c.dom.Node;

public abstract class OscillatorOptions {
    
    protected Vector <Fuse> m_fuseList;

    protected OscillatorOptions(Vector <Fuse> fuseList) {
        m_fuseList = fuseList;
    }
    
    public abstract JPanelOscillatorOptions createPanel(FusesEditor fusesEditor);
    
    public static OscillatorOptions createFromXmlNode(Vector <Fuse> fuseList, Node node) throws Exception {
        
        String type = XmlUtil.getAttr(node, "Type");
        
        if (type.equals("ATmega8"))
            return new OscillatorOptionsATmega8(fuseList);
        else if (type.equals("ATmega48"))
            return new OscillatorOptionsATmega48(fuseList);
        else if (type.equals("ATmega329"))
            return new OscillatorOptionsATmega329(fuseList);
        else if (type.equals("ATtiny2313"))
            return new OscillatorOptionsATtiny2313(fuseList);
        else
            throw new Exception("Error in configuration file: unknown oscillator options type: " + type);
    }
}
