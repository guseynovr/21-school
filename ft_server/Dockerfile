FROM debian:buster

WORKDIR /usr/src/ft_server

EXPOSE 80
EXPOSE 443

RUN apt-get update && apt-get -y install	\
	wget nginx mariadb-server				\
	php-fpm	php-mysql php-mbstring			\
	php-zip	php-gd php-xml					\
	vim	

COPY ./src/default			/etc/nginx/sites-available/default	
COPY ./src/start.sh			/bin
COPY ./src/wp_db_setup.sql	/tmp
COPY ./src/wp_filled_db.sql	/tmp

RUN wget -q https://wordpress.org/latest.tar.gz	\
	&& tar xf latest.tar.gz						\
	&& rm latest.tar.gz

WORKDIR ./wordpress

RUN wget https://files.phpmyadmin.net/phpMyAdmin/5.1.0/phpMyAdmin-5.1.0-all-languages.tar.gz \
	&& tar xf phpMyAdmin-5.1.0-all-languages.tar.gz	\
	&& rm phpMyAdmin-5.1.0-all-languages.tar.gz		\
	&& mv phpMyAdmin-5.1.0-all-languages phpmyadmin

CMD bash /bin/start.sh
