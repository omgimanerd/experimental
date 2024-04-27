#!/bin/bash

RESET=$'\e[0m'
BOLD=$'\e[1m'
DIM=$'\e[2m'
UNDERLINE=$'\e[4m'
FG=$'\e[39m'

BLACK=$'\e[30m'
RED=$'\e[31m'
GREEN=$'\e[32m'
YELLOW=$'\e[33m'
BLUE=$'\e[34m'
MAGENTA=$'\e[35m'
CYAN=$'\e[36m'
LIGHT_GRAY=$'\e[37m'
DARK_GRAY=$'\e[90m'
LIGHT_RED=$'\e[91m'
LIGHT_GREEN=$'\e[92m'
LIGHT_YELLOW=$'\e[93m'
LIGHT_BLUE=$'\e[94m'
LIGHT_MAGENTA=$'\e[95m'
LIGHT_CYAN=$'\e[96m'
WHITE=$'\e[97m'

git_status() {
  GIT_STATUS=$(git status -s 2> /dev/null | cut -c1,2 | sort | uniq | \
    sed -r "s/([A-Z])([A-Z])/${LIGHT_GREEN}\1${RED}\2/" | \
    sed -r "s/ ([A-Z])/${RED}\1/" | \
    sed -r "s/([A-Z]) /${LIGHT_GREEN}\1/" | \
    sed "s/??/${RED}?${RESET}/" | \
    paste -sd ' ')
  echo "${WHITE}[$GIT_STATUS${WHITE}]${RESET} "
}

PS1='$(git_status)'\
'${BOLD}${LIGHT_GREEN}\u${RESET}'\
':${LIGHT_BLUE}$(dirs)${RESET}\$ '
