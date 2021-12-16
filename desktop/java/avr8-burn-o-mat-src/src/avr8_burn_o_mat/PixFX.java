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
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.ColorModel;
import java.awt.image.PixelGrabber;
import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;
import javax.swing.JPanel;
import javax.swing.Timer;

public class PixFX
extends JPanel
implements ActionListener, MouseMotionListener, MouseListener {
    
    private final static double ACCELERATION = 12;
    private final static double TIME_STEP = 0.5;
    private final static double FRICTION = 0.984;
    private final static int    TIMER_INTERVALL = 50;
    private final static int    WIN_WIDTH = 450;
    private final static int    WIN_HEIGHT = 300;
    private final static int    ADD_MOVER_SPEED = 20;
    
    public enum MoverAppearanceMode {
        FOUR_EDGES, AROUND, FOUR_PIECES, BORDERS, BIG_BANG, SPUTTERING
    }

    public enum MoverDisappearanceMode{
        EXPLODE_AND_FALL_DOWN, SUCTION
    }

    private class Borders {
        double m_borderTop;
        double m_borderBottom;
        double m_borderLeft;
        double m_borderRight;
    }
    
    private class Mover {
        
        private double m_px, m_py;  // position
        private double m_vx, m_vy;  // velocity
        private double m_tx, m_ty;  // target coordinates
        
        private Borders m_borders;
        
        private Color   m_color;
        
        private int     m_colorRGB;
        
        public boolean  m_active = false;
        
        public Mover(Borders borders,
                     double tx, double ty,
                     Color color) {
            
            m_borders = borders;
            m_px = 0;
            m_py = 0;
            m_vx = 0;
            m_vy = 0;
            m_tx = tx;
            m_ty = ty;
            m_color = color;
            m_colorRGB = m_color.getRGB();
        }
        
        public Color getColor() {
            return m_color;
        }
        
        public int getColorRGB() {
            return m_colorRGB;
        }
        
        public void setTarget(double tx, double ty) {
            m_tx = tx;
            m_ty = ty;
        }
        
        public void setPos(double px, double py) {
            m_px = px;
            m_py = py;
        }
        
        public void setVelocity(double vx, double vy) {
            m_vx = vx;
            m_vy = vy;
        }
        
        public double getPosX() {
            return m_px;
        }
        
        public double getPosY() {
            return m_py;
        }
        
        public void calcTimeStep() {
            
            if (!m_active)
                return;
            
            double dx = m_px - m_tx;
            double dy = m_py - m_ty;
            double dd = dx * dx + dy * dy;
            double f = -ACCELERATION / (dd + 7);
            double v = m_vx * m_vx + m_vy * m_vy;
                    
            if ((v < 5) && (dd < 5))
            {
                m_px = m_tx;
                m_py = m_ty;
                m_vx = 0;
                m_vy = 0;
            }
            else
            {
                m_vx += f * dx;
                m_vy += f * dy;
                
                m_vx *= FRICTION;
                m_vy *= FRICTION;
                
                m_px += m_vx * TIME_STEP;
                m_py += m_vy * TIME_STEP;
            }
            
            if (m_px > m_borders.m_borderRight) {
                m_px = m_borders.m_borderRight;
                m_vx = 0;
            } else if (m_px < m_borders.m_borderLeft) {
                m_px = m_borders.m_borderLeft;
                m_vx = 0;
            }
            
            if (m_py > m_borders.m_borderBottom) {
                m_py = m_borders.m_borderBottom;
                m_vy = 0;
            } else if (m_py < m_borders.m_borderTop) {
                m_py = m_borders.m_borderTop;
                m_vy = 0;
            }
        }
        
        public double getTargetPosX() {
            return m_tx;
        }
        
        public double getTargetPosY() {
            return m_ty;
        }
        
        public void addRandMove(double strong) {
            
            if (m_active) {
                m_vx += (0.5 - Math.random()) * strong;
                m_vy += (0.5 - Math.random()) * strong;
            }
        }
        
        public void mouseMoved(double x, double y) {
            
            if (m_active) {
                double dx = x - m_tx;
                double dy = y - m_ty;
                double dd = dx * dx + dy * dy;
                double f = -ACCELERATION / (dd + 7);

                m_vx += f * dx * 3;
                m_vy += f * dy * 3;
            }
        }
    }
    
    private class MoverList {
        
        private Vector <Mover> m_moverTempList;
        private Mover[]        m_moverList;
        
        private int m_numberOfActiveMover = 0;
        
        public MoverList() {
            m_moverTempList = new Vector <Mover>();
        }
        
        public void clear() {
            m_numberOfActiveMover = 0;
            m_moverTempList.clear();
            m_moverList = null;
        }
        
        public void addMover(Mover mover) {
            m_moverTempList.add(mover);
        }
        
        /** Must be called after last mover is added.
         */
        public void addMoverFinished() {
            
            Collections.sort(m_moverTempList,
                new Comparator <Mover>() {
                    public int compare(Mover m1, Mover m2) {
                        if (m1.getColorRGB() < m2.getColorRGB())
                            return -1;
                        else if (m1.getColorRGB() > m2.getColorRGB())
                            return 1;
                        else
                            return 0;
                    }
                });
                
            m_moverList = new Mover [m_moverTempList.size()];
            m_moverList = m_moverTempList.toArray(m_moverList);
        }
        
        public void calcTimeStep() {
            for (Mover m : m_moverList) {
                if (m.m_active) {
                    m.calcTimeStep();
                }
            }
            
            int idx;
            
            for (idx = 0; (idx < ADD_MOVER_SPEED) && (m_numberOfActiveMover < m_moverList.length); idx++) {
                m_moverList[m_numberOfActiveMover].m_active = true;
                m_numberOfActiveMover++;
            }
        }
        
        public void draw(Graphics g) {
            
            int currColorRGB = g.getColor().getRGB();
            
            for (Mover m : m_moverList) {
                if (m.m_active) {
                    
                    if (m.getColorRGB() != currColorRGB)
                        g.setColor(m.getColor());

                    int x = (int)m.getPosX();
                    int y = (int)m.getPosY();

                    g.drawLine(x, y, x, y);
                }
            }
        }
        
        public double[] storeTargetPosX() {
            
            double[] x = new double[m_moverList.length];
            int idx;
            
            for (idx = 0; idx < m_moverList.length; idx++)
                x[idx] = m_moverList[idx].getTargetPosX();
            
            return x;
        }
        
        public double[] storeTargetPosY() {
            
            double[] y = new double[m_moverList.length];
            int idx;
            
            for (idx = 0; idx < m_moverList.length; idx++)
                y[idx] = m_moverList[idx].getTargetPosY();
            
            return y;
        }
        
        public void setTargetPos(double[] tx, double[] ty) {
            
            int idx;
            
            for (idx = 0; idx < m_moverList.length; idx++) {
                m_moverList[idx].setTarget(tx[idx], ty[idx]);
            }
        }
        
        public void setMoverAppearance(MoverAppearanceMode mode) {
            
            int idx, cnt, x, y;
            
            cnt = m_moverList.length;
            
            switch (mode) {
                
                case AROUND:
                case BORDERS:
                    
                    idx = 0;
                    
                    while (idx < cnt) {
                        
                        y = 0;
                        for (x = 0; (x < WIN_WIDTH) && (idx < cnt); x++) {
                            m_moverList[idx].setPos(x, y);
                            m_moverList[idx].setVelocity(0, 0);
                            idx++;
                        }
                        
                        x = WIN_WIDTH - 1;
                        for (y = 0; (y < WIN_HEIGHT) && (idx < cnt); y++) {
                            m_moverList[idx].setPos(x, y);
                            m_moverList[idx].setVelocity(0, 0);
                            idx++;
                        }
                        
                        y = WIN_HEIGHT - 1;
                        for (x = WIN_WIDTH - 1; (x >= 0) && (idx < cnt); x--) {
                            m_moverList[idx].setPos(x, y);
                            m_moverList[idx].setVelocity(0, 0);
                            idx++;
                        }
                        
                        x = 0;
                        for (y = WIN_HEIGHT - 1; (y >= 0) && (idx < cnt); y--) {
                            m_moverList[idx].setPos(x, y);
                            m_moverList[idx].setVelocity(0, 0);
                            idx++;
                        }
                    }
                    
                    for (Mover m : m_moverList) {
                        m.m_active = (mode == MoverAppearanceMode.BORDERS);
                    }
                    
                    if (mode == MoverAppearanceMode.BORDERS) {
                        m_numberOfActiveMover = cnt;
                    } else {
                        m_numberOfActiveMover = 0;
                    }
                    
                    break;
                    
                case BIG_BANG:
                case SPUTTERING:
                    
                    for (Mover m : m_moverList) {
                        
                        m.m_active = (mode == MoverAppearanceMode.BIG_BANG);
                        
                        double angle = Math.random() * Math.PI * 2;
                        double value = Math.random() * 10 + 1;
                        
                        m.setPos(WIN_WIDTH / 2, WIN_HEIGHT / 2);
                        m.setVelocity(value * Math.cos(angle), value * Math.sin(angle));
                    }
                    
                    if (mode == MoverAppearanceMode.BIG_BANG)
                        m_numberOfActiveMover = cnt;
                    else
                        m_numberOfActiveMover = 0;
                    
                    break;
                
                case FOUR_EDGES:
                case FOUR_PIECES:
                    
                    for (idx = 0; idx < cnt; idx++) {
                        
                        Mover m = m_moverList[idx];
                        
                        m.m_active = (mode == MoverAppearanceMode.FOUR_PIECES);
                        
                        switch (idx % 4) {
                            case 0:
                                m.setPos(0, 0);
                                m.setVelocity(3, 0);
                                break;
                                
                            case 1:
                                m.setPos(WIN_WIDTH - 1, 0);
                                m.setVelocity(0, 3);
                                break;
                                
                            case 2:
                                m.setPos(WIN_WIDTH - 1, WIN_HEIGHT - 1);
                                m.setVelocity(-3, 0);
                                break;
                                
                            case 3:
                                m.setPos(0, WIN_HEIGHT - 1);
                                m.setVelocity(0, -3);
                                break;
                        }
                    }
                    
                    if (mode == MoverAppearanceMode.FOUR_PIECES)
                        m_numberOfActiveMover = cnt;
                    else
                        m_numberOfActiveMover = 0;

                    break;
                    
                default:
                    assert false;
            }

        }

        public void setMoverDisappearance(MoverDisappearanceMode mode) {
            
            switch (mode) {
                
                case EXPLODE_AND_FALL_DOWN:
                    
                    for (Mover m : m_moverList) {
                        
                        double x = m.getPosX() - WIN_WIDTH / 2;
                        double y = m.getPosY() - WIN_HEIGHT / 2;
                        
                        double a = 30 / Math.sqrt(x * x + y * y);
                        
                        m.setVelocity(x * a, y * a);
                        m.setTarget(x * a, WIN_HEIGHT + 100);
                    }
                    
                    break;
                    
                case SUCTION:
                    
                    for (Mover m : m_moverList)
                        m.setTarget(WIN_WIDTH + 50, WIN_HEIGHT + 50);
                    
                    break;
                    
                default:
                    assert false;
            }
        }
        
        public void addRandMove(double strong) {
            for (Mover m : m_moverList)
                m.addRandMove(strong);
        }
        
        public void mouseMoved(double x, double y) {
            for (Mover m : m_moverList)
                m.mouseMoved(x, y);
        }   
    }
            
    private Borders   m_borders;
    private Image     m_image;
    private MoverList m_moverList;
    private Timer     m_timer;
    private double[]  m_targetBackupX;
    private double[]  m_targetBackupY;
    
    public PixFX(String imageFileName) throws Exception {
        
        m_image = Toolkit.getDefaultToolkit().getImage(imageFileName);
        
        MediaTracker mediaTracker = new MediaTracker(this);
        mediaTracker.addImage(m_image, 0);
        mediaTracker.waitForAll();
        
        if (mediaTracker.isErrorAny())
            throw new Exception("Can not load image " + imageFileName);
        
        setDoubleBuffered(true);
        
        setPreferredSize(new Dimension(WIN_WIDTH + 10, WIN_HEIGHT + 10));
        setSize(WIN_WIDTH + 10, WIN_HEIGHT + 10);
        
        m_borders = new Borders();
        
        m_borders.m_borderLeft = -10;
        m_borders.m_borderRight = WIN_WIDTH + 10;
        m_borders.m_borderTop = -10;
        m_borders.m_borderBottom = WIN_HEIGHT + 10;
        
        m_moverList = new MoverList();
                
        scanImage(m_image);
        
        m_timer = new Timer(TIMER_INTERVALL, this);
        
        addMouseListener(this);
        addMouseMotionListener(this);
    }
    
    private void scanImage(Image image) throws InterruptedException {
        
        m_moverList.clear();
        
        PixelGrabber pg = new PixelGrabber(image, 0, 0, -1, -1, true);
        
        pg.grabPixels();
        
        int[] pixels = (int[])pg.getPixels();
        
        int imgWidth = pg.getWidth();
        int imgHeight = pg.getHeight();
        
        int offsetX = WIN_WIDTH / 2 - imgWidth / 2;
        int offsetY = WIN_HEIGHT / 2 - imgHeight / 2;
        
        if (offsetX < 0)
            offsetX = 0;
        
        if (offsetY < 0)
            offsetY = 0;
        
        Vector <Integer> colorRGB = new Vector <Integer>();
        Vector <Color> color = new Vector <Color>();
        
        ColorModel cm = pg.getColorModel();

        int x, y, n = 0;
        
        for (y = 0; y < imgHeight; y++) {
            for (x = 0; x < imgWidth; x++) {

                int colRGB = pixels[n];
                
                if (cm.getAlpha(colRGB) > 100) {

                    Color col;
                    int idx = colorRGB.indexOf(colRGB);

                    if (idx == -1) {
                        col = new Color(colRGB);
                        colorRGB.add(colRGB);
                        color.add(col);
                    }
                    else
                        col = color.elementAt(idx);

                    Mover m = new Mover(m_borders, x + offsetX, y + offsetY, col);

                    m_moverList.addMover(m);
                }
                
                n++;
            }
        }
        
        m_moverList.addMoverFinished();
        
        m_targetBackupX = m_moverList.storeTargetPosX();
        m_targetBackupY = m_moverList.storeTargetPosY();
        
        assert colorRGB.size() == color.size();
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, getWidth(), getHeight());
        
        m_moverList.draw(g);
    }
    
    public void actionPerformed(ActionEvent evt) {
        m_moverList.calcTimeStep();
        repaint();
    }
    
    public void start() {
        
        m_moverList.setTargetPos(m_targetBackupX, m_targetBackupY);
        m_moverList.setMoverAppearance(MoverAppearanceMode.AROUND);
        
        m_timer.start();
    }
    
    public void stop() {
        m_timer.stop();
    }
    
    public void mouseMoved(MouseEvent event)
    {
        m_moverList.mouseMoved(event.getX(), event.getY());
    }   

    public void mousePressed(MouseEvent event)
    {
        m_moverList.addRandMove(20);
    }

    public void mouseDragged(MouseEvent event) {}   
    public void mouseClicked(MouseEvent event) {}
    public void mouseExited(MouseEvent event) {}
    public void mouseEntered(MouseEvent event) {}
    public void mouseReleased(MouseEvent event) {}
}

