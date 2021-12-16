#!/usr/bin/python

import mysql.connector as mysql

# connecting to the database using 'connect()' method
# it takes 3 required parameters 'host', 'user', 'passwd'
db = mysql.connect(host = "localhost",user = "sqluser",passwd = "")

# creating an instance of 'cursor' class which is used to execute the 'SQL' statements in 'Python'
dbcsr = db.cursor()

# creating a databse called 'datacamp'
# 'execute()' method is used to compile a 'SQL' statement
# below statement is used to create the 'sensor' database
dbcsr.execute("CREATE DATABASE sensor")

# Get all databases into buffer
dbcsr.execute("SHOW DATABASES")

# 'fetchall()' method fetches all the rows from the last executed statement
dbases = dbcsr.fetchall()
print(dbases)

###############################

# access spesific database
tbl = mysql.connect(host = "localhost",user = "sqluser",passwd = "",database = "sensor")
tblcsr = tbl.cursor()

tblcsr.execute("CREATE TABLE adc(date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, v0 INT(16))")

###############################

tblcsr.execute("INSERT INTO adc(v0) VALUES (%s)" % (str(100)))
tbl.commit()

###############################

tblcsr.execute("SELECT * FROM adc")
records = tblcsr.fetchall()
for record in records:
	print(record)

tblcsr.execute("SELECT v0 FROM adc")
records = tblcsr.fetchall()
for record in records:
	print(record)
