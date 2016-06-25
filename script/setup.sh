#!/bin/bash

confirm () {
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
    sudo apt-get update
    sudo apt-get install -y mongodb-org
}

install_flux () {
    sudo add-apt-repository ppa:kilian/f.lux
    sudo apt-get update
    sudo apt-get install fluxgui
}

# Install Git, Emacs, OpenSSH, python-dev, python-pip, xclip, ngrok, screen, make, and libssl-dev
confirm "Install Git, Emacs, python-dev, python-pip, xclip, ngrok, screen, make, tkdiff, and libssl-dev? [y/n]" && sudo apt-get install git emacs24 python-dev python-pip xclip ngrok-client screen make tkdiff libssl-dev

# Install Chromium
confirm "Install Chromium? [y/n]" && sudo apt-get install chromium-browser

# Install Gimp
confirm "Install Gimp? [y/n]" && sudo apt-get install gimp

# Install Heroku
confirm "Install Heroku? [y\n]" && wget -O- https://toolbelt.heroku.com/install-ubuntu.sh | sh

# Install LaTeX
confirm "Install LaTeX? [y\n]" && sudo apt-get install texlive texlive-latex-base texlive-latex-extra texlive-fonts-extra

# Install Java
confirm "Install Java JRE and JDK? [y/n]" && sudo apt-get install default-jre default-jdk

# Install OpenSSH client and server
confirm "Install OpenSSH client and server? [y/n]" && sudo apt-get install openssh-client openssh-server

# Install Node Version Manager
confirm "Install NVM? [y/n]" && curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.0/install.sh | bash

# Install MongoDB
confirm "Install MongoDB? [y/n]" && install_mongo

# Install f.lux
confirm "Install f.lux? [y/n]" && install_flux

git config --global user.name "omgimanerd"
git config --global user.email "alvin.lin.dev@gmail.com"
git config --global push.default simple
