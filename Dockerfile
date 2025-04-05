FROM debian

RUN echo "deb http://archive.debian.org/debian/ wheezy main" >> /etc/apt/sources.list
RUN apt update --allow-insecure-repositories
RUN apt install -y --allow-unauthenticated gcc-4.6 g++-4.6 make python3 python3-pip
RUN python3 -m pip install --break-system-packages pyelftools iced-x86
