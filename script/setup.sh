#!/bin/sh

# Install Git, Java, Chromium, Emacs, OpenSSH, python-dev, and libssl-dev
sudo apt-get install git default-jdk default-jre chromium-browser emacs24 openssh-server python-dev libssl-dev

# Install Node Version Manager
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.0/install.sh | bash

# Install MongoDB
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 7F0CEB10
echo "deb http://repo.mongodb.org/apt/ubuntu "$(lsb_release -sc)"/mongodb-org/3.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.0.list
sudo apt-get install -y mongodb-org

# Install f.lux
sudo add-apt-repository ppa:kilian/f.lux
sudo apt-get update
sudo apt-get install fluxgui
