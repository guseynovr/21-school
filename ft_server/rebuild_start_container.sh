docker rm -f server
docker image rm server
docker build -t  server .
docker run --name server -tid -p 80:80 -p 443:443 server
docker exec -it server bash
