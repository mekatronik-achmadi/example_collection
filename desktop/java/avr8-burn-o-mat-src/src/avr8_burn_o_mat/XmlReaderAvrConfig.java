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

import java.io.File;
import java.net.URI;
import java.util.Vector;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Node;

public class XmlReaderAvrConfig {
    
    private Vector <AVR> m_avrList = new Vector <AVR>();
    
    /** Creates a new instance of FuseReader */
    public XmlReaderAvrConfig() {
    }
    
    public Vector <AVR> getAVRList() {
        return m_avrList;
    }
    
    public void readXmlFile(String uri) throws Exception {
        
        DocumentBuilderFactory factory  = DocumentBuilderFactory.newInstance();
        DocumentBuilder        builder  = factory.newDocumentBuilder();
        Document               document = builder.parse(uri);

        Node nodeAvrFuses = document.getDocumentElement().getFirstChild();
        
        while (nodeAvrFuses != null) {
            if (nodeAvrFuses.getNodeName().equals("AVR_Fuses")) {
                readAvrFuses(nodeAvrFuses);
            }
            
            nodeAvrFuses = nodeAvrFuses.getNextSibling();
        }
        
    }
    
    private void readAvrFuses(Node nodeAvrFuses) throws Exception {
        
        Node nodeAvr = nodeAvrFuses.getFirstChild();
        
        while (nodeAvr != null) {
            
            if (nodeAvr.getNodeName().equals("AVR")) {
              
                AVR  avr = new AVR();
                avr.loadFromXml(nodeAvr);
                
                m_avrList.add(avr);
            }
            
            nodeAvr = nodeAvr.getNextSibling();
        }
    }
    
}
