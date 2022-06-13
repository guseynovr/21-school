#!/bin/sh

if [[ ! -d "/var/lib/mysql/mysql" ]]; then
mysql_install_db --user=mysql --datadir=/var/lib/mysql &&\
chown -R mysql:mysql /var/lib/mysql
fi
if [[ ! -d "/var/lib/mysql/db_wordpress" ]]; then
rc-service mariadb start &&\
mariadb -p$MYSQL_ROOT_PASSWORD < /tmp/db_setup.sql &&\
rc-service mariadb stop
fi
echo "Starting mariadb"
mysqld_safe
