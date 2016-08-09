#!/bin/bash
# Ubuntu 14.04

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

confirm "Install Git, Emacs, python-dev, python-pip, screen, make, tkdiff? [y/n]" && sudo apt-get install git emacs24 python-dev python-pip screen make tkdiff

# Install Gimp
confirm "Install Gimp? [y/n]" && sudo apt-get install gimp

# Install Heroku
confirm "Install Heroku? [y\n]" && wget -O- https://toolbelt.heroku.com/install-ubuntu.sh | sh

# Install LaTeX
confirm "Install LaTeX? [y\n]" && sudo apt-get install texlive texlive-latex-base texlive-latex-extra

# Install Java
confirm "Install Java JRE and JDK? [y/n]" && sudo apt-get install default-jre default-jdk

# Install OpenSSH client and server
confirm "Install OpenSSH client and server? [y/n]" && sudo apt-get install openssh-client openssh-server

# Install Node Version Manager
confirm "Install NVM? [y/n]" && curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.3/install.sh | bash
