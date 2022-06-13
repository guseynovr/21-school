#!/bin/bash
service mysql start &&\
mysql < /tmp/wp_db_setup.sql &&\
mysql < /tmp/wp_filled_db.sql &&\
rm /tmp/wp_filled_db.sql /tmp/wp_db_setup.sql &&\
mkdir /etc/nginx/certs && cd /etc/nginx/certs &&\
openssl req -x509 -out localhost.crt -keyout localhost.key \
  -newkey rsa:2048 -nodes -sha256 \
  -subj '/CN=localhost' -extensions EXT -config <( \
   printf "[dn]\nCN=localhost\n[req]\ndistinguished_name = dn\n[EXT]\nsubjectAltName=DNS:localhost\nkeyUsage=digitalSignature\nextendedKeyUsage=serverAuth") &&\
service php7.3-fpm start &&\
service nginx start &&\
cd /usr/src/ft_server/wordpress &&\
sed 's/database_name_here/wp/g' wp-config-sample.php > wp-config.php
sed -i 's/username_here/admin/g' wp-config.php
sed -i 's/password_here/admin/g' wp-config.php
sed -i 's/DB_HOST/localhost/g' wp-config.php
while true; do sleep 1d; done
