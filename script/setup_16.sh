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

confirm "Install Git, Emacs, python-dev, python-pip, screen, make, tkdiff, terminator? [y/n]" && sudo apt-get install git emacs24 python-dev python-pip python3-pip screen make tkdiff terminator

# Install gnome-tweak-tool
confirm "Install gnome-tweak-tool? [y/n]" && sudo apt-get install gnome-tweak-tool

# Install compizconfig-settings-manager
confirm "Install compizconfig-settings-manager? [y/n]" && sudo apt-get install compizconfig-settings-manager compiz-plugins

# Install Gimp
confirm "Install Gimp? [y/n]" && sudo apt-get install gimp

# Install LaTeX
confirm "Install LaTeX? [y\n]" && sudo apt-get install texlive-full

# Install Java
confirm "Install Java JRE and JDK? [y/n]" && sudo apt-get install default-jre default-jdk

# Install OpenSSH client and server
confirm "Install OpenSSH client and server? [y/n]" && sudo apt-get install openssh-client openssh-server

# Install Node Version Manager
confirm "Install NVM? [y/n]" && curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.3/install.sh | bash

# Install Yarn
confirm "Install Yarn? [y/n]" && curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | sudo apt-key add - && echo "deb https://dl.yarnpkg.com/debian/ stable main" | sudo tee /etc/apt/sources.list.d/yarn.list && sudo apt-get update && sudo apt-get install yarn
