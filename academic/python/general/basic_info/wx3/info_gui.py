# -*- coding: utf-8 -*- 

###########################################################################
## Python code generated with wxFormBuilder (version Feb 15 2016)
## http://www.wxformbuilder.org/
##
## PLEASE DO "NOT" EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

###########################################################################
## Class frmInfo
###########################################################################

class frmInfo ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"Info System", pos = wx.DefaultPosition, size = wx.Size( 200,71 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		
		bSizer1 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.btnInfoConsole = wx.Button( self, wx.ID_ANY, u"Console", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer1.Add( self.btnInfoConsole, 0, wx.ALL, 5 )
		
		self.btnInfoDialog = wx.Button( self, wx.ID_ANY, u"Dialog", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer1.Add( self.btnInfoDialog, 0, wx.ALL, 5 )
		
		
		self.SetSizer( bSizer1 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.btnInfoConsole.Bind( wx.EVT_BUTTON, self.infoConsole )
		self.btnInfoDialog.Bind( wx.EVT_BUTTON, self.infoDialog )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def infoConsole( self, event ):
		event.Skip()
	
	def infoDialog( self, event ):
		event.Skip()
	

