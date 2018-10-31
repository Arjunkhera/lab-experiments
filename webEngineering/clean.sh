#! usr/bin/bash

# script to stop and remove the active docker containers

docker stop $(docker ps -q)
docker rm $(docker ps -a -q)
