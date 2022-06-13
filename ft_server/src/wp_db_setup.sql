CREATE DATABASE wp;
CREATE USER 'admin'@'localhost' identified by 'admin';
GRANT ALL PRIVILEGES ON wp.* TO 'admin'@'localhost';
FLUSH PRIVILEGES;
