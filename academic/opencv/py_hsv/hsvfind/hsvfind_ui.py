# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'hsvfind.ui'
#
# Created by: PyQt4 UI code generator 4.12
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_HSVFind(object):
    def setupUi(self, HSVFind):
        HSVFind.setObjectName(_fromUtf8("HSVFind"))
        HSVFind.resize(454, 437)
        self.centralwidget = QtGui.QWidget(HSVFind)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.btnOpen = QtGui.QPushButton(self.centralwidget)
        self.btnOpen.setGeometry(QtCore.QRect(20, 10, 85, 27))
        self.btnOpen.setObjectName(_fromUtf8("btnOpen"))
        self.lblH = QtGui.QLabel(self.centralwidget)
        self.lblH.setGeometry(QtCore.QRect(20, 60, 31, 31))
        self.lblH.setObjectName(_fromUtf8("lblH"))
        self.lblS = QtGui.QLabel(self.centralwidget)
        self.lblS.setGeometry(QtCore.QRect(20, 90, 31, 31))
        self.lblS.setObjectName(_fromUtf8("lblS"))
        self.lblV = QtGui.QLabel(self.centralwidget)
        self.lblV.setGeometry(QtCore.QRect(20, 120, 31, 31))
        self.lblV.setObjectName(_fromUtf8("lblV"))
        self.txtH = QtGui.QLineEdit(self.centralwidget)
        self.txtH.setGeometry(QtCore.QRect(60, 60, 113, 25))
        self.txtH.setObjectName(_fromUtf8("txtH"))
        self.txtS = QtGui.QLineEdit(self.centralwidget)
        self.txtS.setGeometry(QtCore.QRect(60, 90, 113, 25))
        self.txtS.setObjectName(_fromUtf8("txtS"))
        self.txtV = QtGui.QLineEdit(self.centralwidget)
        self.txtV.setGeometry(QtCore.QRect(60, 120, 113, 25))
        self.txtV.setObjectName(_fromUtf8("txtV"))
        self.sldX = QtGui.QSlider(self.centralwidget)
        self.sldX.setGeometry(QtCore.QRect(10, 360, 431, 17))
        self.sldX.setOrientation(QtCore.Qt.Horizontal)
        self.sldX.setObjectName(_fromUtf8("sldX"))
        self.sldY = QtGui.QSlider(self.centralwidget)
        self.sldY.setGeometry(QtCore.QRect(420, 30, 17, 321))
        self.sldY.setOrientation(QtCore.Qt.Vertical)
        self.sldY.setInvertedAppearance(True)
        self.sldY.setInvertedControls(False)
        self.sldY.setObjectName(_fromUtf8("sldY"))
        HSVFind.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(HSVFind)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 454, 19))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        HSVFind.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(HSVFind)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        HSVFind.setStatusBar(self.statusbar)

        self.retranslateUi(HSVFind)
        QtCore.QMetaObject.connectSlotsByName(HSVFind)

    def retranslateUi(self, HSVFind):
        HSVFind.setWindowTitle(_translate("HSVFind", "HSV Finder", None))
        self.btnOpen.setText(_translate("HSVFind", "Browse", None))
        self.lblH.setText(_translate("HSVFind", "Hue", None))
        self.lblS.setText(_translate("HSVFind", "Sat", None))
        self.lblV.setText(_translate("HSVFind", "Val", None))

