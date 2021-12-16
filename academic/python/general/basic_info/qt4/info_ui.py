# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'info.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
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

class Ui_frmInfo(object):
    def setupUi(self, frmInfo):
        frmInfo.setObjectName(_fromUtf8("frmInfo"))
        frmInfo.resize(210, 51)
        self.btnConsole = QtGui.QPushButton(frmInfo)
        self.btnConsole.setGeometry(QtCore.QRect(10, 10, 85, 26))
        self.btnConsole.setObjectName(_fromUtf8("btnConsole"))
        self.btnDialog = QtGui.QPushButton(frmInfo)
        self.btnDialog.setGeometry(QtCore.QRect(110, 10, 85, 26))
        self.btnDialog.setObjectName(_fromUtf8("btnDialog"))

        self.retranslateUi(frmInfo)
        QtCore.QMetaObject.connectSlotsByName(frmInfo)

    def retranslateUi(self, frmInfo):
        frmInfo.setWindowTitle(_translate("frmInfo", "Info System", None))
        self.btnConsole.setText(_translate("frmInfo", "Console", None))
        self.btnDialog.setText(_translate("frmInfo", "Dialog", None))

