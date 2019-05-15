# Arduino- Raspberry pi setup 
## Arduino libraties 
## python 
- use version 2.7 
- install pyserial if required
- install mysql connector
# install mysql
sudo apt-get install mysql-server php-mysql -y
launch
mysql -u root -p

First, connect in sudo mysql

sudo mysql -u root
Check your accounts present in your db

SELECT User,Host FROM mysql.user;

  User             | Host      
 ------------------|-----------
 | admin            | localhost |
 | debian-sys-maint | localhost |
 | magento_user     | localhost |
 | mysql.sys        | localhost |
 | root             | localhost |

Delete current root@localhost account

mysql> DROP USER 'root'@'localhost';
Query OK, 0 rows affected (0,00 sec)
Recreate your user

mysql> CREATE USER 'root'@'%' IDENTIFIED BY '';
Query OK, 0 rows affected (0,00 sec)
Give permissions to your user (don't forget to flush privileges)

mysql> GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
Query OK, 0 rows affected (0,00 sec)

mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0,01 sec)

# Create Table
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
);


## Root password
- Toor
# Raspberry pi
- Hostname: ControlPi





# Missing 
-Light Set up


