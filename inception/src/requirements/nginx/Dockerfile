FROM alpine:3.14

RUN apk upgrade && apk add nginx openssl
RUN adduser -u 82 -D -S -G www-data www-data

EXPOSE 443

COPY conf/default.conf /etc/nginx/http.d/default.conf
COPY conf/nginx.conf /etc/nginx/nginx.conf

# RUN nginx -t
COPY start.sh /usr/local/bin
CMD ["start.sh"]
