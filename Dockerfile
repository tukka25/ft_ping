FROM ubuntu:plucky

WORKDIR /app

USER root

COPY src/ /app/

RUN apt-get update && apt-get install -y gcc make

CMD ["sleep", "infinity"]