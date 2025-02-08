#! /bin/bash

sudo docker build -t myapp .
sudo docker run -d  -v ./src:/app myapp