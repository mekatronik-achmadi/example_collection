#!/usr/bin/python2

import os
import time
import cv2

import pygtk
pygtk.require('2.0')
    
import gtk
import gtk.glade
import numpy
    
class Test1:
    
    imgView = None
    lblStatus = None
    
    cap = None
    font = cv2.FONT_HERSHEY_SIMPLEX
    
    sttCapture = 0
    dirCapture = "captured_image/"
    
    def __init__(self):
        
        guibuilder=gtk.Builder() #bulid gtk
        guibuilder.add_from_file("/home/alarm/Desktop/capture.glade") #open file dari glade
        guibuilder.connect_signals(self) #standart dari gtk konek ke file
        
        window=guibuilder.get_object("window1")
        window.connect("destroy",self.on_destroy)
        
        self.lblStatus=guibuilder.get_object("lblStatus")
        btnCapture=guibuilder.get_object("btnCapture")
        self.imgView=guibuilder.get_object("imgView") #ambil id dari file glade
        
        self.cap = cv2.VideoCapture(0)
        #self.cap.set(3,320) #width
        #self.cap.set(4,380) #height
        
        btnCapture.connect("clicked",self.on_capture) #untuk capture
        gtk.timeout_add(200, self.timer_cb) #delay tampilan
        
        strtime = time.strftime("%H-%M-%S")
        strdate = time.strftime("%d-%m-%Y")
        strname = strdate + "__" + strtime
        self.lblStatus.set_text("Camera Opened at " + strname) #label dari tgl dan waktu
        
        window.show()#tampilan
        window.fullscreen()
        
    def on_destroy(self, widget):#ketika close
        gtk.main_quit()#gtk dihapus
        self.cap.release() #capture berhenti
        
    def on_capture(self,widget): #tanda capture, ketika capture 1, ketika tidak akan 0
        self.sttCapture=1
        
    def timer_cb(self): #fungsi ketika waktu berjalan
        
        ret,imgOri = self.cap.read() #membaca capture
        imgCam = imgOri[130:510,80:400] #cropping gambar titik-titik pojok
	imgRow,imgCol,imgChan = imgCam.shape #membaca gambar dari polygon titik-titik pojok
	
        #imgsize = str(imgRow) + " " + str(imgCol) + " " + str(imgChan) 
        #print imgsize 
        
        vB0 = imgCam[imgRow/2,imgCol/2,0]
	vB1 = imgCam[(imgCol/2)-100,(imgRow/2)-100,0]
	vB2 = imgCam[(imgCol/2)-100,(imgRow/2)+100,0]
	vB3 = imgCam[(imgCol/2)+100,(imgRow/2)+100,0]
	vB4 = imgCam[(imgCol/2)+100,(imgRow/2)-100,0]
	b = [vB0,vB1,vB2, vB3, vB4]	
	vB = numpy.mean(b)

	vG0 = imgCam[imgRow/2,imgCol/2,1]
	vG1 = imgCam[(imgCol/2)-100,(imgRow/2)-100,1]
	vG2 = imgCam[(imgCol/2)-100,(imgRow/2)+100,1]
	vG3 = imgCam[(imgCol/2)+100,(imgRow/2)+100,1]
	vG4 = imgCam[(imgCol/2)+100,(imgRow/2)-100,1]
	g = [vG0,vG1,vG2, vG3, vG4]
	vG = numpy.mean(g)        


	vR0 = imgCam[imgRow/2,imgCol/2,2]
	vR1 = imgCam[(imgCol/2)-100,(imgRow/2)-100,2]
	vR2 = imgCam[(imgCol/2)-100,(imgRow/2)+100,2]
	vR3 = imgCam[(imgCol/2)+100,(imgRow/2)+100,2]
	vR4 = imgCam[(imgCol/2)+100,(imgRow/2)-100,2]
	r = [vR0,vR1,vR2, vR3, vR4]
	vR = numpy.mean(r)

	
	# konstanta BGR
	aB = 25.136645212479028
	aG = -22.257801348895931
	aR = 40.392922444468006
	
	# konstanta Green
	cG = 27.843677970082545
	
	# konstanta Luminos
	cL = 29.499892196993738
	
	# calculate Luminos
	lum_val = 0.07*vB + 0.72*vG + 0.21*vR
	
	# calculate Chlorophil Estimation
	C_bgr = aR*vR + aG*vG + aB*vB
	C_g = cG*vG
	C_lum = cL*lum_val
	
        val = "%i %i %i %i" % (vB,vG,vR,lum_val)
	res_val = "%.2f %.2f %.2f" % (C_bgr,C_g,C_lum)
        
        cv2.circle(imgCam,(imgCol/2,imgRow/2), 5, (255,0,0), -1)
	cv2.circle(imgCam,((imgCol/2)-100,(imgRow/2)-100), 5, (255,0,0), -1)
	cv2.circle(imgCam,((imgCol/2)-100,(imgRow/2)+100), 5, (255,0,0), -1)
	cv2.circle(imgCam,((imgCol/2)+100,(imgRow/2)-100), 5, (255,0,0), -1)
	cv2.circle(imgCam,((imgCol/2)+100,(imgRow/2)+100), 5, (255,0,0), -1)
	
	cv2.putText(imgCam,val,(0,12), self.font, 0.5,(255,0,0),1) #tampilan text dari val
	cv2.putText(imgCam,res_val,(0,imgRow-2), self.font, 0.5,(255,0,0),1) #tampilan text dari res_val
        
        if self.sttCapture == 0: #ketika sedang runing akan menampilkan
            imgCam = cv2.cvtColor(imgCam,cv2.COLOR_BGR2RGB) #RGB
            imgCamView = gtk.gdk.pixbuf_new_from_array(imgCam, gtk.gdk.COLORSPACE_RGB, 8) 
            self.imgView.set_from_pixbuf(imgCamView) #tampilan ke layar
        else: #selain 0
            strtime = time.strftime("%H-%M-%S")
            strdate = time.strftime("%d-%m-%Y")
            strname = strdate + "__" + strtime
            
            if not os.path.exists(self.dirCapture): #direktori folder ketika ada folder
                os.makedirs(self.dirCapture) 
            
            imgname=self.dirCapture +strname + ".jpg" 
            
            cv2.imwrite(imgname, imgCam, [int(cv2.IMWRITE_JPEG_QUALITY), 95]) #save file, kualitas 95
	    time.sleep(1) #delay program
            self.lblStatus.set_text("saved as " + imgname) #tampilan sttus
            self.sttCapture=0
        
        return True #sukses
        
if __name__ == "__main__": #main program
    app = Test1() #akses ke test 1
    gtk.main() #running tampilan
