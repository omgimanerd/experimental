GIT_PS1_SHOWDIRTYSTATE=1
GIT_PS1_SHOWSTASHSTATE=1
GIT_PS1_SHOWUNTRACKEDFILES=1

# Shell prompt customization
export PROMPT_COMMAND="history -a"
export PS1='\[\033[01;31m\]\h:\[\033[01;34m\]\w\[\033[0;32m\]$(__git_ps1 " [%s] ")\[\033[01;34m\]\$ \[\033[01;32m\]'
trap 'echo -ne "\e[0m"' DEBUG

# Custom aliases
alias android-studio='/usr/local/android-studio/bin/studio.sh'
alias arduino='/usr/local/arduino/arduino'
alias lock='gnome-screensaver-command -l'
alias python='python3'
alias show='gnome-open'
alias sl='ls'

# Custom functions
function news() {
  curl http://getnews.tech/$1
}

function weather() {
  curl http://wttr.in/$1
}

function sps() {
  git stash;
  git pull;
  git stash pop;
}

function rit() {
  ssh axl1439@$1.cs.rit.edu
}
