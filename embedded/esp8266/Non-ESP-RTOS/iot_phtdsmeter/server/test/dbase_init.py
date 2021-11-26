#!/usr/bin/python

#########
# sudo chown -R mysql /var/lib/mysql
# sudo mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
# sudo systemctl enable mysqld
# sudo systemctl start mysqld
# sudo mysql -N -B -u root -e 'SHOW DATABASES'

#########
# sudo mysql -u root
# SELECT User,Host FROM mysql.user;
# CREATE USER 'sqluser'@localhost IDENTIFIED BY '';
# GRANT ALL PRIVILEGES ON *.* TO 'sqluser'@localhost WITH GRANT OPTION;
# FLUSH PRIVILEGES;
# exit

#########
# mysql -u sqluser
# exit

########
# sudo mysql -u root
# SELECT User,Host FROM mysql.user;
# DROP USER 'sqluser'@localhost;
# FLUSH PRIVILEGES;
# exit

import mysql.connector as mysql

######## Creating Database ##############
db = mysql.connect(host = "localhost",user = "sqluser",passwd = "")
cursor = db.cursor()

cursor.execute("SHOW DATABASES LIKE 'sensor'")
sqlout = cursor.fetchall()
if not sqlout:
	cursor.execute("CREATE DATABASE sensor")
	sqlout = cursor.fetchall()
	print(sqlout)
	print('Database sensor created')
else:
	print('Database sensor exist')
	cursor.execute("SHOW DATABASES")
	sqlout = cursor.fetchall()
	print(sqlout)

########### Cretating Table ##############
tbl = mysql.connect(host = "localhost",user = "sqluser",passwd = "",database = "sensor")
tblcsr = tbl.cursor()

tblcsr.execute("SHOW TABLES LIKE 'adc'")
sqlout = tblcsr.fetchall()
if not sqlout:
	tblcsr.execute("CREATE TABLE adc(date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, v0 INT(16))")
	print('ADC table created')
else:
	print('ADC table exist')

############ Insert a data ############

