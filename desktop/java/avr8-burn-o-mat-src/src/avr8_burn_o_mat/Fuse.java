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

import java.io.IOException;
import org.w3c.dom.Document;
import org.w3c.dom.DOMException;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

public class Fuse {
    
    public static final String[ ] FUSE_BYTES = { "fuse", "lfuse", "hfuse", "efuse" };
    
    public enum FuseState {
        PROGRAMMED,
        UNPROGRAMMED
    }
    
    public enum FuseMode {
        NORMAL,
        EXPERT
    }
    
    private String      m_name;
    
    private String      m_description;
    
    private Integer     m_bitNumber;
    
    private String      m_fuseByte;
    
    private FuseState   m_fuseState;
    
    private FuseState   m_defaultFuseState;
    
    private FuseMode    m_fuseMode;
    
    public Fuse() {
        m_name = "";
        m_description = "";
        m_bitNumber = 0;
        m_fuseByte = "fuse";
        m_fuseState = FuseState.UNPROGRAMMED;
        m_defaultFuseState = FuseState.UNPROGRAMMED;
        m_fuseMode = FuseMode.EXPERT;
        
        assert m_fuseState != null;
    }
    
    /** Creates a new instance of AVR8_Fuse */
    public Fuse(String name,
                String desc,
                Integer bitNumber,
                String fuseByte,
                FuseState defaultFuseState,
                FuseMode fuseMode) throws Exception {
        
        if (!isValidFuseName(fuseByte))
            throw new Exception("'" + fuseByte + "' is not a valid fuse name!");
        
        m_name = name;
        m_description = desc;
        m_bitNumber = bitNumber;
        m_fuseByte = fuseByte;
        m_fuseState = defaultFuseState;
        m_defaultFuseState = defaultFuseState;
        m_fuseMode = fuseMode;
        
        assert m_fuseState != null;
    }
    
    public static boolean isValidFuseName(String fuse) {
      
        for (String f : FUSE_BYTES) {
            if (f.equals(fuse))
                return true;
        }
        
        return false;
    }
    
    public static Integer FuseState2Integer(FuseState fuseState) throws Exception {
        if (fuseState == FuseState.PROGRAMMED)
            return 0;
        else if (fuseState == FuseState.UNPROGRAMMED)
            return 1;
        else
        {
            assert false;
            throw new Exception("internal error function: FuseState2Integer");
        }
    }
    
    public static FuseState Integer2FuseState(Integer fuseState) throws Exception {
        if (fuseState == 0)
            return FuseState.PROGRAMMED;
        else if (fuseState == 1)
            return FuseState.UNPROGRAMMED;
        else
            throw new Exception("invalid fuse state, 0 or 1 expected");
    }
    
    public String getName() {
        return m_name;
    }
    
    public String getDescription() {
        return m_description;
    }
    
    public Integer getBitNumber() {
        return m_bitNumber;
    }
    
    public String getFuseByte() {
        return m_fuseByte;
    }
    
    public FuseState getDefaultFuseState() {
        return m_defaultFuseState;
    }
    
    public Boolean isProgrammed() {
        return m_fuseState == FuseState.PROGRAMMED;
    }
    
    public void setFuseState(FuseState fuseState) {
        assert fuseState != null;
        m_fuseState = fuseState;
    }
    
    public FuseState getFuseState() {
        assert m_fuseState != null;
        return m_fuseState;
    }
    
    public FuseMode getFuseMode() {
        return m_fuseMode;
    }
    
    public void loadFromXml(Node nodeFuse) throws Exception {
        
        m_name = XmlUtil.getAttr(nodeFuse, "name");
        m_description = XmlUtil.getAttr(nodeFuse, "desc");

        String s = XmlUtil.getAttr(nodeFuse, "bit");
        
        try {
            m_bitNumber = Integer.parseInt(s);
        } catch (NumberFormatException e) {
            throw new DOMException(DOMException.TYPE_MISMATCH_ERR,
                                   "Attribute \"bit\" in fuse tag is not a number!");
        }

        if ((m_bitNumber < 0) || (m_bitNumber > 7))
            throw new DOMException(DOMException.TYPE_MISMATCH_ERR,
                                   "Attribute \"bit\" in fuse tag must be a number between 0 and 7!");
        
        s = XmlUtil.getAttr(nodeFuse, "fuseByte").toLowerCase();
        
        if (isValidFuseName(s))
            m_fuseByte = s;
        else
        {
            String msg = "Attribute \"fuseByte\" in fuse tag is not valid, valid values:";
            
            for (String f : Fuse.FUSE_BYTES)
                msg += " " + f;
            
            throw new DOMException(DOMException.TYPE_MISMATCH_ERR,
                                   msg);
        }
        
        String defaultFuseState = XmlUtil.getAttr(nodeFuse, "default");
        
        try {
            m_defaultFuseState = Integer2FuseState( Integer.parseInt(defaultFuseState));
            m_fuseState = m_defaultFuseState;
        } catch (NumberFormatException e) {
            throw new DOMException(DOMException.TYPE_MISMATCH_ERR,
                                   "Attribute \"default\" in fuse tag is not a number!");
        }

        m_fuseMode = FuseMode.NORMAL;
        
        try {
            s = XmlUtil.getAttr(nodeFuse, "mode").toLowerCase();
            if (s.equals("expert"))
                m_fuseMode = FuseMode.EXPERT;
        } catch (DOMException e) {}

        assert m_fuseState != null;
    }
    
    public void loadStateFromXml(Node nodeFuse) throws Exception {
        
        String name = XmlUtil.getAttr(nodeFuse, "name");
        
        assert name.equals(m_name);
        
        String fuseState = XmlUtil.getAttr(nodeFuse, "state");
        
        try {
            m_fuseState = Integer2FuseState(Integer.parseInt(fuseState));
        } catch (NumberFormatException e) {
            throw new Exception("Attribute \"state\" in fuse tag is not a number!");
        }
        
        assert m_fuseState != null;
    }

    public void saveStateToXml(Document doc, Node nodeAvr) throws Exception {
        
        Integer fuseState = FuseState2Integer(m_fuseState);
        String s;
        
        Element elem = doc.createElement("Fuse");
        
        elem.setAttribute("name", m_name);
        elem.setAttribute("state", fuseState.toString());
        
        nodeAvr.appendChild(elem);
    }
    
}

