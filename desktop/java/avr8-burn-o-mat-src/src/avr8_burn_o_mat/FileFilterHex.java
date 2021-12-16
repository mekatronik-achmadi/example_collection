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
import javax.swing.filechooser.FileFilter;

public class FileFilterHex extends FileFilter {
    
    /** Creates a new instance of HexFileFilter */
    public FileFilterHex() {
    }
    
    public boolean accept(File f) {
        String filename = f.getName().toLowerCase();
        return f.isDirectory()
            || filename.endsWith(".hex")
            || filename.endsWith(".mot")
            || filename.endsWith(".txt")
            || filename.endsWith(".raw");
    }
    
    public String getDescription() {
        return "hex files";
    }
}
