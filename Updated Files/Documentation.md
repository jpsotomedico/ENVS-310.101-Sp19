# Arduno- Raspberry pi- mysql

-This prototype , as well as the other parts contained in this package, are  just the structural requirements, and are not free of bugs and 
will most likely, be modified to fit the needs of the project.

#  Arduino

## Arduino libraties 
- Some libraries required manual installation. 
- Adafruit_SI1145.h
- DHT.h
- FastLED.h
- serial port might change, manual configuration is required.

## python 2.7
- use version 2.7  serial manipulation varies among versions. This code has been writen with version 2.7
- install pyserial if required 
- install mysql-connector
# Install mysql
```
sudo apt-get install mysql-server php-mysql -y
````
launch
```
mysql -u root -p
```
First, connect in sudo mysql
```
sudo mysql -u root
```
Check your accounts present in your db
```
SELECT User,Host FROM mysql.user;
```
| User             | Host      |
------------------|-----------
| admin            | localhost |
| debian-sys-maint | localhost |
| magento_user     | localhost |
| mysql.sys        | localhost |
| root             | localhost |

Delete current root@localhost account
```mysql
mysql> DROP USER 'root'@'localhost';
Query OK, 0 rows affected (0,00 sec)
Recreate your user
```
```mysql
mysql> CREATE USER 'root'@'%' IDENTIFIED BY '';
Query OK, 0 rows affected (0,00 sec)
Give permissions to your user (don't forget to flush privileges)
```
```mysql
mysql> GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
Query OK, 0 rows affected (0,00 sec)
```
```mysql
mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0,01 sec)
```

# Create Table

``` mysql
CREATE TABLE IF NOT EXISTS `data` (
	`id` int(10) NOT NULL auto_increment,
	`ph` Float(10,3),
	`volt` Float(10,3),
	`waterlevel` Float(10,3),
	`humidity` Float(10,3),
	`temperature` Float(10,3),
	`uv` Float(10,3),
	`thermistor` Float(10,3),
	PRIMARY KEY( `id` )
):
```


## Current user
- user: admin
- Password: no password set (testing purposes only)



