GIT_PS1_SHOWDIRTYSTATE=1
GIT_PS1_SHOWSTASHSTATE=1
GIT_PS1_SHOWUNTRACKEDFILES=1

# Shell prompt customization
export PROMPT_COMMAND="history -a"
export PS1='\[\033[01;31m\]\h:\[\033[01;34m\]\w\[\033[0;32m\]$(__git_ps1 " [%s] ")\[\033[01;34m\]\$ \[\033[01;32m\]'
trap 'echo -ne "\e[0m"' DEBUG

# Custom aliases
alias rit='ssh axl1439@glados.cs.rit.edu'
alias show='gnome-open'
alias sl='ls'
alias windows='cd /media/omgimanerd/Windows8_OS/Users/omgimanerd'

# Custom functions
function news() {
  curl http://54.201.130.221/$1
}

function weather() {
  curl http://wttr.in/$1
}

function sps() {
  git stash;
  git pull;
  git stash pop;
}
