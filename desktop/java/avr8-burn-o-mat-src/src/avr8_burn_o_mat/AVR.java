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
import java.io.FileWriter;
import java.util.Vector;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

public class AVR {
    
    private Vector <Fuse>   m_fuseList = new Vector <Fuse>();
    
    private String          m_name;
    
    private String          m_caption;
    
    private BrownOutDetection m_brownOutDetection;
    
    private OscillatorOptions m_oscillatorOptions;
    
    /** Creates a new instance of AVR */
    public AVR() {
    }
    
    public AVR(String name, String caption) {
        m_name = name;
        m_caption = caption;
    }
    
    public String getName() {
        return m_name;
    }
    
    public String getCaption() {
        return m_caption;
    }
    
    public void setFuseList(Vector <Fuse> fuseList) {
        m_fuseList = fuseList;
    }
    
    public Vector <Fuse> getFuseList() {
        return m_fuseList;
    }
    
    public boolean hasFuseByte(String fuseByte) {
        
        for (Fuse fuse : m_fuseList) {
            if (fuseByte.equals(fuse.getFuseByte()))
                return true;
        }
        
        return false;
    }
    
    public Vector <String> getUsedFuseBytes() {
        
        Vector <String> fuseBytes = new Vector <String>();
        
        for (Fuse fuse : m_fuseList) {
            
            boolean fuseIsAlreadyInList = false;
            
            for (String b : fuseBytes) {
                if (b.equals(fuse.getFuseByte())) {
                    fuseIsAlreadyInList = true;
                    break;
                }
            }
            
            if (!fuseIsAlreadyInList) {
                fuseBytes.add(fuse.getFuseByte());
            }
        }
        
        return fuseBytes;
    }
    
    public int getFuseByteData(String fuseByte) {
        
        int data = 0;
        
        for (Fuse fuse : m_fuseList) {
            if (fuseByte.equals(fuse.getFuseByte())) {
                
                if (!fuse.isProgrammed())
                    data |= 1 << fuse.getBitNumber();
            }
        }
        
        return data;
    }
    
    public void setFuseByteData(String fuseByte, int data) {
        
        for (Fuse fuse : m_fuseList) {
            if (fuseByte.equals(fuse.getFuseByte())) {
                
                if ((data & (1 << fuse.getBitNumber())) == 0)
                    fuse.setFuseState(Fuse.FuseState.PROGRAMMED);
                else
                    fuse.setFuseState(Fuse.FuseState.UNPROGRAMMED);
            }
        }
        
    }
    
    public void loadFromXml(Node nodeAvr) throws Exception {
        
        m_brownOutDetection = null;
        m_oscillatorOptions = null;
        
        m_fuseList.clear();
        
        m_name = XmlUtil.getAttr(nodeAvr, "name");
        m_caption = XmlUtil.getAttr(nodeAvr, "caption");

        Node nodeFuse = nodeAvr.getFirstChild();
        
        while (nodeFuse != null) {
            
            if (nodeFuse.getNodeName().equals("Fuse")) {
                
                Fuse fuse = new Fuse();
                fuse.loadFromXml(nodeFuse);
                
                m_fuseList.add(fuse);
            }
            
            nodeFuse = nodeFuse.getNextSibling();
        }
            
        Node nodeBod = nodeAvr.getFirstChild();
        
        while (nodeBod != null) {
            
            if (nodeBod.getNodeName().equals("BrownOutDetection")) {
                m_brownOutDetection = BrownOutDetection.createFromXmlNode(m_fuseList, nodeBod);
                break;
            }
            
            nodeBod = nodeBod.getNextSibling();
        }
        
        Node nodeOsciOpt = nodeAvr.getFirstChild();
        
        while (nodeOsciOpt != null) {
            
            if (nodeOsciOpt.getNodeName().equals("OscillatorOptions")) {
                m_oscillatorOptions = OscillatorOptions.createFromXmlNode(m_fuseList, nodeOsciOpt);
                break;
            }
            
            nodeOsciOpt = nodeOsciOpt.getNextSibling();
        }
    }
    
    public void saveFusesStateToXml(File file) throws Exception {

        DocumentBuilderFactory factory  = DocumentBuilderFactory.newInstance();
        DocumentBuilder        builder  = factory.newDocumentBuilder();
        Document               doc = builder.newDocument();
        
        Element elem = doc.createElement("AVR");
        
        elem.setAttribute("name", m_name);
        elem.setAttribute("caption", m_caption);
        
        doc.appendChild(elem);
        
        for (Fuse fuse : m_fuseList) {
            fuse.saveStateToXml(doc, elem);
        }
        
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.transform(new DOMSource(doc), new StreamResult(new FileWriter(file))); 
    }
    
    public void loadFusesStateFromXml(File file) throws Exception {
        
        DocumentBuilderFactory factory  = DocumentBuilderFactory.newInstance();
        DocumentBuilder        builder  = factory.newDocumentBuilder();
        Document               document = builder.parse(file);
        
        Node nodeAvr = document.getDocumentElement();
        
        if ((nodeAvr == null) || !nodeAvr.getNodeName().equals("AVR"))
            throw new Exception("missing root node AVR");
        
        Node nodeFuse = nodeAvr.getFirstChild();
        while (nodeFuse != null) {
            
            if (nodeFuse.getNodeName().equals("Fuse")) {
                
                String name = XmlUtil.getAttr(nodeFuse, "name");
                
                for (Fuse f : m_fuseList) {
                    if (f.getName().equals(name)) {
                        f.loadStateFromXml(nodeFuse);
                        break;
                    }
                        
                }
            }
            
            nodeFuse = nodeFuse.getNextSibling();
        }
    }
    
    public BrownOutDetection getBrownOutDetection() {
        return m_brownOutDetection;
    }
    
    public OscillatorOptions getOscillatorOptions() {
        return m_oscillatorOptions;
    }
}
