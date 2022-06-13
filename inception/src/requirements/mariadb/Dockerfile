FROM alpine:3.14

RUN addgroup -g 99 mysql && adduser -u 99 -D -S -G mysql mysql
RUN apk upgrade && apk add mariadb mariadb-client openrc
RUN mkdir /run/openrc && touch /run/openrc/softlevel && openrc 2>/dev/null

COPY ./db_setup.sql	/tmp

RUN sed -i '/skip-networking$/d' /etc/my.cnf.d/mariadb-server.cnf

EXPOSE 3306

COPY start.sh /usr/local/bin
CMD [ "sh", "/usr/local/bin/start.sh" ]
