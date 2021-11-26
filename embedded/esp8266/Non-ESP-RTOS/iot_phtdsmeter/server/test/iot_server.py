#!/usr/bin/python

from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import socket
import numpy as np
import mysql.connector as mysql

hostName = socket.gethostbyname(socket.gethostname())
serverPort = 8050

tbl = mysql.connect(host = "localhost",user = "sqluser",passwd = "",database = "sensor")
tblcsr = tbl.cursor()

class MyServer(BaseHTTPRequestHandler):
	def do_GET(self):
		self.send_response(200)
		self.send_header("Content-type", "text/html")
		self.end_headers()
		self.wfile.write(bytes("<html><head><title>Python Server</title></head>", "utf-8"))
		self.wfile.write(bytes("<body>", "utf-8"))
		self.wfile.write(bytes("<p>This is an example Python web server.</p>", "utf-8"))
		self.wfile.write(bytes("<p>Request: %s</p>" % self.path, "utf-8"))
		self.wfile.write(bytes("</body></html>", "utf-8"))

		print("Path URL: %s" % self.path)
		str_adc_array = self.path.split("/")
		adc_array = np.array([ int(str_adc_array[1]), int(str_adc_array[2]), int(str_adc_array[3]) ])
		print('ADC array: ', end='')
		print(adc_array)

		tblcsr.execute("INSERT INTO adc(v0) VALUES (%s)" % (str_adc_array[1]))
		tbl.commit()

if __name__ == "__main__":
	webServer = HTTPServer((hostName, serverPort), MyServer)
	print("Server started http://%s:%s" % (hostName, serverPort))

	try:
		webServer.serve_forever()
	except KeyboardInterrupt:
		pass

	webServer.server_close()
	print("Server stopped.")
