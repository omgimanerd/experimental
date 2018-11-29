_PS1_SHOWDIRTYSTATE=1
GIT_PS1_SHOWSTASHSTATE=1
GIT_PS1_SHOWUNTRACKEDFILES=1

# Shell prompt customization
export PROMPT_COMMAND="history -a"
export PS1='\[\033[01;31m\]\h:\[\033[01;34m\]\w\[\033[0;32m\]$(__git_ps1 " [%s] ")\[\033[01;34m\]\$ \[\033[01;32m\]'
trap 'echo -ne "\e[0m"' DEBUG

export PATH=$PATH:/home/omgimanerd/backburner/doclt

# Custom aliases
alias android-studio='/usr/local/android-studio/bin/studio.sh &'
alias arduino='/usr/local/arduino/arduino &'
alias intellij='/usr/local/intellij/bin/idea.sh &'
alias show='xdg-open'
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
###-begin-doclt.js-completions-###
#
# yargs command completion script
#
#
_yargs_completions()
{
    local cur_word args type_list

    cur_word="${COMP_WORDS[COMP_CWORD]}"
    args=("${COMP_WORDS[@]}")

    # ask yargs to generate completions.
    type_list=$(doclt.js --get-yargs-completions "${args[@]}")

    COMPREPLY=( $(compgen -W "${type_list}" -- ${cur_word}) )

    # if no match was found, fall back to filename completion
    if [ ${#COMPREPLY[@]} -eq 0 ]; then
      COMPREPLY=( $(compgen -f -- "${cur_word}" ) )
    fi

    return 0
}
complete -F _yargs_completions doclt.js
###-end-doclt.js-completions-###

