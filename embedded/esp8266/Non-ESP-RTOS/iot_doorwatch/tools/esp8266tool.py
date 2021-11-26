# -*- coding: utf-8 -*-

import os
import sys
import subprocess as sp
from pathlib import Path

from PyQt5.QtGui import QTextCursor
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtSerialPort import QSerialPort
from PyQt5.QtCore import pyqtSlot, QIODevice

from Ui_esp8266tool import Ui_MainWindow

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        self.WorkDirPath = str(Path(__file__).resolve().parent.parent)
        self.WorkFirmPath = self.WorkDirPath + "/firmware"
        self.txtPath.setText(self.WorkDirPath)
        self.txtFirm.setText(self.WorkFirmPath)

        self.binInit, self.binBlank = self.get_vendor_bin(self.get_lsb())
        self.txtInitBin.setText(self.binInit)
        self.txtBlankBin.setText(self.binBlank)

        self.AddrBlank1 = '0x3e000'
        self.AddrInit   = '0x3fc000'
        self.AddrBlank2 = '0x3fe000'
        self.txtAddrBlank1.setText(self.AddrBlank1)
        self.txtAddrInit.setText(self.AddrInit)
        self.txtAddrBlank2.setText(self.AddrBlank2)

        self.AddrUser1 = '0x00000'
        self.AddrUser2 = '0x10000'
        self.txtAddrUser1.setText(self.AddrUser1)
        self.txtAddrUser2.setText(self.AddrUser2)

        self.txtESPtool.setText('esptool')
        self.txtESPport.setText('/dev/ttyUSB0')

        self.serial = QSerialPort(self)

        self.setFixedSize(self.width(),self.height())

    def closeEvent(self, event):
        if self.serial.isOpen:
            self.serial.close()
        os.system('rm -rf __pycache__/')
        os.system('rm -f Ui_esp8266tool.py')
        print("Program closed")

    def get_lsb(self):
        lsb = sp.Popen('lsb_release -i | cut -f2', shell=True,stdout=sp.PIPE)
        output = lsb.communicate()[0]
        retcode = lsb.returncode

        if retcode==0:
            return output.decode('utf-8').rstrip('\n')
        else:
            print("This must run on Unix-based OS with lsb_release installed")
            sys.exit()

    def get_vendor_bin(self,strDistro):
        if strDistro=='Arch':
            OpenSDK = '/opt/esp-open-sdk/sdk/bin'
        elif strDistro=='Ubuntu':
            print('Ubuntu not supported yet')
        elif strDistro=='Debian':
            print('Debian not supported yet')
        else:
            print('Unsupported Linux Distribution')

        InitBin = OpenSDK + '/esp_init_data_default.bin'
        BlankBin =  OpenSDK + '/blank.bin'

        return InitBin, BlankBin

    @pyqtSlot()
    def on_btnFirmRebuild_clicked(self):
        self.setEnabled(False)
        makeclean = sp.Popen(['make','clean'], cwd=self.WorkDirPath)
        output,error = makeclean.communicate()
        retcode = makeclean.returncode
        if retcode!=0:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'make clean' failed")
            self.setEnabled(True)
            return
        else:
            print("Previous build cleaned up")

        makeall = sp.Popen(['make','all'], cwd=self.WorkDirPath)
        output,error = makeall.communicate()
        retcode = makeall.returncode
        if retcode!=0:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'make all' failed")
            self.setEnabled(True)
            return
        else:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'make all' success")
            print("New build completed")

        self.setEnabled(True)

    @pyqtSlot()
    def on_btnFirmClean_clicked(self):
        self.setEnabled(False)
        makeclean = sp.Popen(['make','clean'], cwd=self.WorkDirPath)
        output,error = makeclean.communicate()
        retcode = makeclean.returncode
        if retcode!=0:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'make clean' failed")
            self.setEnabled(True)
            return
        else:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'make clean' success")
            print("Previous build cleaned up")
        self.setEnabled(True)

    @pyqtSlot()
    def on_btnFirmUpload_clicked(self):
        self.setEnabled(False)
        rooting = self.cmbESProot.currentText()
        if rooting=='none':
            rooting=''
        esptool = self.txtESPtool.text()
        espport = self.txtESPport.text()

        erasing = sp.Popen([rooting,
                            esptool,
                            '--port',
                            espport,
                            'erase_flash']
                            ,cwd=self.WorkDirPath)
        output,error = erasing.communicate()
        retcode = erasing.returncode
        if retcode!=0:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'erash_flash' failed")
            self.setEnabled(True)
            return
        else:
            print("'erash_flash' success")

        upload_init = sp.Popen([rooting,
                            esptool,
                            '--port',
                            espport,
                            'write_flash',
                            self.AddrBlank1,
                            self.binBlank,
                            self.AddrInit,
                            self.binInit,
                            self.AddrBlank2,
                            self.binBlank]
                            ,cwd=self.WorkDirPath)
        output,error = upload_init.communicate()
        retcode = upload_init.returncode
        if retcode!=0:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'upload init bin' failed")
            self.setEnabled(True)
            return
        else:
            print("'upload init bin' success")

        strUserBin1 = self.WorkFirmPath+'/'+self.AddrUser1+'.bin'
        strUserBin2 = self.WorkFirmPath+'/'+self.AddrUser2+'.bin'

        upload_user = sp.Popen([rooting,
                            esptool,
                            '--port',
                            espport,
                            'write_flash',
                            self.AddrUser1,
                            strUserBin1,
                            self.AddrUser2,
                            strUserBin2]
                            ,cwd=self.WorkDirPath)
        output,error = upload_user.communicate()
        retcode = upload_user.returncode
        if retcode!=0:
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'upload user bin' failed")
            self.setEnabled(True)
            return
        else:
            print("'upload firmware' success")
            self.statusBar.clearMessage()
            self.statusBar.showMessage("'upload firmware' success")

        self.setEnabled(True)

    @pyqtSlot()
    def on_btnConnect_clicked(self):
        port = self.txtESPport.text()
        baud = self.cmbBaud.currentText()

        self.serial.setPortName(port)
        self.serial.setBaudRate(int(baud))

        if self.btnConnect.text()=='Connect':
            if self.serial.open(QIODevice.ReadWrite):
                self.serial.readyRead.connect(self.on_serial_read)
                print("Success connect on %s" % port)
                self.btnConnect.setText('Disconnect')
            else:
                print("Cannot connect to device on port %s" % port)
        else:
            if self.serial.isOpen():
                self.serial.close()
                print("Port %s disconnected" % port)
                self.btnConnect.setText('Connect')

    def on_serial_read(self):
        strData = str(self.serial.readAll(),encoding='utf8',errors='ignore').rstrip('\r')
        self.txtConsole.insertPlainText(strData)
        self.txtConsole.moveCursor(QTextCursor.End)

    def serial_request(self,strReq):
        strData = bytes(strReq+'\n',encoding='utf8')
        if not self.serial.isOpen():
            return
        self.serial.write(strData)

    @pyqtSlot()
    def on_btnClear_clicked(self):
        self.txtConsole.clear()

    @pyqtSlot()
    def on_btnInfoSystem_clicked(self):
        self.serial_request('sysinfo')

    @pyqtSlot()
    def on_btnInfoJSON_clicked(self):
        self.serial_request('jsoninfo')

    @pyqtSlot()
    def on_btnRestart_clicked(self):
        self.serial_request('restart')

    @pyqtSlot()
    def on_btnSwitch_clicked(self):
        self.serial_request('switch')

    @pyqtSlot()
    def on_btnRequest_clicked(self):
        self.serial_request('request')
