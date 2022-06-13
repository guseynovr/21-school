DPATH	=	src/docker-compose.yml

up:
			docker-compose -f $(DPATH) up --build

down:
			docker-compose -f $(DPATH) down -v

start:
			docker-compose -f $(DPATH) start

stop:
			docker-compose -f $(DPATH) stop

.PHONY: 	up down start stop
