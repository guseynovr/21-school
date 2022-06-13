FROM alpine:3.14

RUN adduser -u 82 -D -S -G www-data www-data

RUN apk update          \
    &&                  \
    apk add             \
    --no-cache          \
    libmcrypt-dev       \
    zlib-dev            \
    gmp-dev             \
    freetype-dev        \
    libjpeg-turbo-dev   \
    libpng-dev          \
    php7-fpm            \
    php7-json           \
    php7-zlib           \
    php7-xml            \
    php7-xmlwriter      \
    php7-simplexml      \
    php7-pdo            \
    php7-phar           \
    php7-openssl        \
    php7-pdo_mysql      \
    php7-mysqli         \
    php7-session        \
    php7-gd             \
    php7-iconv          \
    php7-mcrypt         \ 
    php7-gmp            \
    php7-zip            \
    php7-curl           \
    php7-opcache        \
    php7-ctype          \
    php7-apcu           \
    php7-intl           \
    php7-bcmath         \
    php7-dom            \
    php7-mbstring       \
    php7-xmlreader      \
    mysql-client        \
    curl                \
    busybox

WORKDIR /var/www/html

RUN curl -Os https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar &&\
	chmod +x wp-cli.phar &&\
	mv wp-cli.phar /usr/local/bin/wp

RUN sed -i 's/127.0.0.1:9000/9000/g' /etc/php7/php-fpm.d/www.conf

EXPOSE 9000

COPY start.sh /usr/local/bin
CMD [ "start.sh" ]
