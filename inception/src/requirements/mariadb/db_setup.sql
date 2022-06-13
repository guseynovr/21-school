ALTER USER 'root'@'localhost' IDENTIFIED BY '123';
DELETE FROM mysql.user WHERE User='';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';
CREATE USER 'user_wp'@'%.inception-network' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON db_wordpress.* TO 'user_wp'@'%.inception-network';
FLUSH PRIVILEGES;
