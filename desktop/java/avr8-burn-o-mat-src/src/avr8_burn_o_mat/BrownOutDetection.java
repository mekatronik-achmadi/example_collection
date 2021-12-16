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
import org.w3c.dom.DOMException;
import org.w3c.dom.Node;

public class BrownOutDetection {
    
    private Vector <Fuse> m_fuseList;
    
    public enum FuseSetting {
        PROGRAMMED,
        UNPROGRAMMED,
        IGNORED
    }

    public class Setting {
        
        public Vector <FuseSetting> m_fuseSettings;
        
        private String m_name;
        
        public Setting(String caption) {
            m_fuseSettings = new Vector <FuseSetting>();
            m_name = caption;
        }
        
        public String getName() {
            return m_name;
        }
        
        public boolean fusesEqual(Vector <Fuse> fuseList) {
            assert fuseList.size() == m_fuseSettings.size();
            
            int idx;
            
            for (idx = 0; idx < fuseList.size(); idx++) {
                
                Fuse.FuseState fuseState = fuseList.elementAt(idx).getFuseState();
                
                switch (m_fuseSettings.elementAt(idx)) {
                    case PROGRAMMED:
                        if (fuseState != Fuse.FuseState.PROGRAMMED)
                            return false;
                        break;
                        
                    case UNPROGRAMMED:
                        if (fuseState != Fuse.FuseState.UNPROGRAMMED)
                            return false;
                        break;

                    case IGNORED:
                        break;
                        
                    default:
                        assert false;
                }
            }
            
            return true;
        }
        
        public void applyFusesFromSetting(Vector <Fuse> fuseList) {
            
            assert fuseList.size() == m_fuseSettings.size();
            
            int idx;
            
            for (idx = 0; idx < fuseList.size(); idx++) {
                
                Fuse fuse = fuseList.elementAt(idx);
                
                switch (m_fuseSettings.elementAt(idx)) {
                    case PROGRAMMED:
                        fuse.setFuseState(Fuse.FuseState.PROGRAMMED);
                        break;
                        
                    case UNPROGRAMMED:
                        fuse.setFuseState(Fuse.FuseState.UNPROGRAMMED);
                        break;
                        
                    case IGNORED:
                        break;
                    
                    default:
                        assert false;
                }
            }
        }
    }
    
    public Vector <Setting> m_settingList;
    
    private BrownOutDetection() {
        m_fuseList = new Vector <Fuse>();
        m_settingList = new Vector <Setting>();
    }
    
    public int getSettingIndexFromFusesState() {
        
        int idx;
        
        for (idx = 0; idx < m_settingList.size(); idx++) {
            if (m_settingList.elementAt(idx).fusesEqual(m_fuseList))
                return idx;
        }
        
        return -1;
    }
    
    public void applyFusesFromSetting(int idx) {
        m_settingList.elementAt(idx).applyFusesFromSetting(m_fuseList);
    }
    
    public static BrownOutDetection createFromXmlNode(Vector <Fuse> fuseList, Node node) throws Exception {
        BrownOutDetection bod = new BrownOutDetection();
        bod.loadFromXml(fuseList, node);
        return bod;
    }
    
    private void loadFromXml(Vector <Fuse> fuseList, Node node) throws Exception {
        readFusesFromXml(node, fuseList);
        readSettingsFromXml(node);
    }

    private void readFusesFromXml(Node node, Vector<Fuse> fuseList) throws Exception, DOMException {

        m_fuseList.clear();
        
        Node nodeFuse = node.getFirstChild();
        while (nodeFuse != null) {

            if (nodeFuse.getNodeName().equals("Fuse")) {

                String name = XmlUtil.getAttr(nodeFuse, "name");

                boolean found = false;
                for (Fuse f : fuseList) {
                    if (f.getName().equals(name)) {
                        m_fuseList.add(f);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    throw new Exception("brown out detection fuse not found: " + name);
                }
            }

            nodeFuse = nodeFuse.getNextSibling();
        }

        if (m_fuseList.size() == 0) {
            throw new Exception("error in brown out detection description, no fuses defined");
        }
    }

    private void readSettingsFromXml(Node node) throws Exception {
        
        m_settingList.clear();
        
        Node nodeSetting = node.getFirstChild();
        while (nodeSetting != null) {

            if (nodeSetting.getNodeName().equals("Setting")) {
                
                Setting setting = new Setting(XmlUtil.getAttr(nodeSetting, "caption"));
                
                int idx;
                
                for (idx = 0; idx < m_fuseList.size(); idx++) {
                    
                    String fuseSettingStr = XmlUtil.getAttr(nodeSetting, String.format("Fuse%d", idx + 1));
                    
                    FuseSetting fuseSetting;
                    
                    if (fuseSettingStr.isEmpty())
                        fuseSetting = FuseSetting.IGNORED;
                    else
                    {
                        try {
                            int n = Integer.parseInt(fuseSettingStr);
                            
                            if (n == 0)
                                fuseSetting = FuseSetting.PROGRAMMED;
                            else if (n == 1)
                                fuseSetting = FuseSetting.UNPROGRAMMED;
                            else
                                throw new Exception("fuse state must be 0 or 1");
                                
                        } catch (NumberFormatException e) {
                            throw new Exception("Fuse state is not a number!");
                        }
                    }
                    
                    setting.m_fuseSettings.add(fuseSetting);
                }
                
                if (m_fuseList.size() != setting.m_fuseSettings.size())
                    throw new Exception("internal error BrownOutDetection.readSettingsFromXml");
                
                m_settingList.add(setting);
            }

            nodeSetting = nodeSetting.getNextSibling();
        }
    }
}

