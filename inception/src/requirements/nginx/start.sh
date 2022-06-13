#!/bin/sh

openssl req -x509 -nodes -days 365 -subj "/C=CA/ST=QC/O=42, Inc./CN=dgidget.42.fr" -addext "subjectAltName=DNS:dgidget.42.fr" -newkey rsa:2048 -keyout /etc/ssl/private/nginx-selfsigned.key -out /etc/ssl/certs/nginx-selfsigned.crt &&\
chmod 600 /etc/ssl/certs/nginx-selfsigned.crt /etc/ssl/private/nginx-selfsigned.key

echo "Starting nginx"
nginx -g "daemon off;"
