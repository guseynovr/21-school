#!/bin/sh

while ! mysql -h $WORDPRESS_DB_HOST -u$WORDPRESS_DB_USER -p$WORDPRESS_DB_PASSWORD  -e ";" 2>/dev/null ; do
		sleep 1
		echo "Waiting for db"
done
chown -R www-data:www-data /var/www/html
([ -z "$(ls -A /var/www/html/)" ]) 2>/dev/null && wp core download
if [[ ! -f "/var/www/html/wp-config.php" ]]; then
	echo "Setup config"
	wp config create --dbhost=$WORDPRESS_DB_HOST --dbname=$WORDPRESS_DB_NAME --dbuser=$WORDPRESS_DB_USER --dbpass=$WORDPRESS_DB_PASSWORD
fi

if ! ( (mysql --host=$WORDPRESS_DB_HOST --user=$WORDPRESS_DB_USER --password=$WORDPRESS_DB_PASSWORD -e "use $WORDPRESS_DB_NAME") 2>/dev/null ); then
	echo "Create db"
    wp db create
	wp core install --url=dgidget.42.fr --title=Inception --admin_user=$WORDPRESS_ADMIN --admin_password=$WORDPRESS_ADMIN_PW --admin_email=$WORDPRESS_ADMIN_EMAIL
	wp user create guest 1234@gmail.com --role=author --user_pass=$WORDPRESS_GUEST_PW
fi

chown -R www-data /var/www/html

echo "Starting php-fpm"
php-fpm7 -F
