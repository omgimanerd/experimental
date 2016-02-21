#!/bin/bash

confirm () {
    # call with a prompt string or use a default
    read -r -p "${1:-Are you sure? [y/N]} " response
    case $response in
        [yY][eE][sS]|[yY]) 
            true
            ;;
        *)
            false
            ;;
    esac
}

install_mongo () {
    sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 7F0CEB10
    echo "deb http://repo.mongodb.org/apt/ubuntu "$(lsb_release -sc)"/mongodb-org/3.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.0.list
    sudo apt-get install -y mongodb-org
}

install_flux () {
    sudo add-apt-repository ppa:kilian/f.lux
    sudo apt-get update
    sudo apt-get install fluxgui
}

# Install Git, Java, Chromium, Emacs, OpenSSH, python-dev, xclip, and libssl-dev
confirm "Install Git, Java, Chromium, Emacs, OpenSSH, python-dev, xclip, and libssl-dev? [y/n]" && sudo apt-get install git default-jdk default-jre chromium-browser emacs24 openssh-server python-dev xclip libssl-dev

# Install Node Version Manager
confirm "Install NVM? [y/n]" && curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.0/install.sh | bash

# Install MongoDB
confirm "Install MongoDB? [y/n]" && install_mongo

# Install f.lux
confirm "Install f.lux? [y/n]" && install_flux
