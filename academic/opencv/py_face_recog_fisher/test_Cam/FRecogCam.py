#!/usr/bin/python

import os
import sys
import cv2
import numpy as np

class FaceRecCam:

    dir_pre = "u"
    allmetode = ["lbph","fisher","eigen"]

    def __init__(self,cara,lstnama,haarfile):
        self.nama = [""] + lstnama

        self.metode = cara

        if os.path.exists(haarfile):
            self.haarcas = haarfile
        else:
            print("file deteksi %s tidak ada" % haarfile)
            sys.exit()

        if self.metode == "lbph":
            self.face_recog = cv2.face.LBPHFaceRecognizer_create()
        elif self.metode == "fisher":
            self.face_recog = cv2.face.FisherFaceRecognizer_create()
        elif self.metode == "eigen":
            self.face_recog = cv2.face.EigenFaceRecognizer_create()
        else:
            print("metode %s tidak tersedia." % self.metode)
            pesan = "yang tesedia saat ini:"
            for i in range(len(self.allmetode)):
                pesan += " %s |" % self.allmetode[i]
            print(pesan)
            sys.exit()

    def face_detect(self,img):
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        f_cas = cv2.CascadeClassifier(self.haarcas)
        face = f_cas.detectMultiScale(gray,scaleFactor=1.2,minNeighbors=5,minSize=(30, 30))

        if(len(face)==0):
            return None,None

        (x,y,w,h) = face[0]

        if self.metode == "lbph":
            r_img = gray
        else:
            r_img = cv2.resize(gray[y:y+h, x:x+w],(150,200),interpolation=cv2.INTER_CUBIC)

        return r_img, face[0]

    def prepare_train(self,folder_path):
        dirs = os.listdir(folder_path)

        faces = []
        labels = []

        for dirname in dirs:
            if not dirname.startswith(self.dir_pre):
                continue

            label = int(dirname.replace(self.dir_pre,""))
            sub_dirpath = folder_path + "/" + dirname
            sub_img_name = os.listdir(sub_dirpath)

            for img_name in sub_img_name:
                if img_name.startswith("."):
                    continue

                img_path = sub_dirpath + "/" + img_name

                image = cv2.imread(img_path)
                cv2.resize(image, (400, 500),interpolation=cv2.INTER_CUBIC)
                face, rect = self.face_detect(image)

                if face is not None:
                    faces.append(face)
                    labels.append(label)

        return faces, labels

    def training(self,u_faces, u_labels):
    	self.face_recog.train(u_faces, np.array(u_labels))

    def guessing(self,imgtest):
        face, rect = self.face_detect(cv2.imread(imgtest))
        
        if face is not None:
            label, confidence = self.face_recog.predict(face)
            label_nama = self.nama[label]
    
            if confidence <= 1500:
                label_nama = "LU_SIAPA"
    
            return label_nama, rect, confidence
        
        else:
            return None, None, 0

    def guessing_cam(self,imgtest):
        face, rect = self.face_detect(imgtest)
        
        if face is not None:
            label, confidence = self.face_recog.predict(face)
            label_nama = self.nama[label]
    
            if confidence <= 1500:
                label_nama = "LU_SIAPA"
    
            return label_nama, rect, confidence
        
        else:
            return None, None, 0

    def draw_marker(self,imguri,rect,text):
        img = cv2.imread(imguri)

        (x, y, w, h) = rect
        cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)
        cv2.putText(img, text, (x, y), cv2.FONT_HERSHEY_PLAIN, 1.5, (0, 255, 0), 2)
        return img

    def draw_marker_cam(self,img,rect,text):

        (x, y, w, h) = rect
        cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)
        cv2.putText(img, text, (x, y), cv2.FONT_HERSHEY_PLAIN, 1.5, (0, 255, 0), 2)
        return img

    def save_train(self,file_path):
        self.face_recog.write(file_path)

    def load_train(self,file_path):
        self.face_recog.read(file_path)

    def analisa(self):
        eig = self.face_recog.getEigenValues()
        eigv = self.face_recog.getEigenVectors()
        eigm = self.face_recog.getMean()
        eigprj = self.face_recog.getProjections()

        return eig,eigv,eigm,eigprj
    
    def imresize(self,imgin,rasio=50):
        imW = int(imgin.shape[1] * rasio/100)
        imH = int(imgin.shape[0] * rasio/100)
        imres = cv2.resize(imgin,(imW,imH),interpolation=cv2.INTER_CUBIC)
        return imres
