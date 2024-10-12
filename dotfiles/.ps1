#!/bin/bash

# Escapes the non-printing characters in the given argument string. If the
# command prompt is not escaped, the text length of ANSI color codes is
# computed incorrectly and the cursor will jump erratically.
# https://stackoverflow.com/a/52465778/5792737
#
# This is the easiest way to use color codes in PS1 because \[ and \] are
# treated as special characters and cannot be outputted in echo.
function readline_ANSI_escape() {
  if [[ $# -ge 1 ]]; then
    echo "$*"
  else
    cat  # Read string from STDIN
  fi | \
  perl -pe 's/(?:(?<!\x1)|(?<!\\\[))(\x1b\[[0-9;]*[mG])(?!\x2|\\\])/\x1\1\x2/g'
}

# Sets and exports PS1 formatted with the current git workspace state
# if the current working directory is a git directory.
function ps1_() {
  # ANSI-C Quoted Strings for the ANSI color codes
  # https://www.gnu.org/software/bash/manual/html_node/ANSI_002dC-Quoting.html
  local RESET=$'\e[0m'
  local BOLD=$'\e[1m'
  local DIM=$'\e[2m'
  local UNDERLINE=$'\e[4m'
  local FG=$'\e[39m'

  local BLACK=$'\e[30m'
  local RED=$'\e[31m'
  local GREEN=$'\e[32m'
  local YELLOW=$'\e[33m'
  local BLUE=$'\e[34m'
  local MAGENTA=$'\e[35m'
  local CYAN=$'\e[36m'
  local LIGHT_GRAY=$'\e[37m'
  local DARK_GRAY=$'\e[90m'
  local LIGHT_RED=$'\e[91m'
  local LIGHT_GREEN=$'\e[92m'
  local LIGHT_YELLOW=$'\e[93m'
  local LIGHT_BLUE=$'\e[94m'
  local LIGHT_MAGENTA=$'\e[95m'
  local LIGHT_CYAN=$'\e[96m'
  local WHITE=$'\e[97m'

  local GIT_STATUS=$(git status -s 2> /dev/null | cut -c1,2 | sort | uniq | \
    # When a file is modified, staged, and modified again, it will show up as
    # AM in the shortened git status. Capture both and color them correctly.
    sed -r "s/([AM])([AM])/${LIGHT_GREEN}\1${RED}\2/" | \
    # Files that are modified but not staged show up as M on the right column.
    sed -r "s/ (M)/${RED}\1/" | \
    # Files that are staged for commit can be either added new files or modified
    # existing files.
    sed -r "s/([AM]) /${LIGHT_GREEN}\1/" | \
    # Newly added files show up as '?'
    sed "s/??/${RED}?${RESET}/" | \
    paste -sd ' ')
  local GIT_STATUS_="${WHITE}[${GIT_STATUS}${WHITE}]${RESET} "
  local USER_="${LIGHT_GREEN}${USER}${RESET}:"
  local PWD_="${LIGHT_BLUE}${PWD/~/\~}${RESET}"

  readline_ANSI_escape "${GIT_STATUS_}${USER_}${PWD_}\$ "
}

# ps1 function is single quoted for evaluation in the terminal itself.
PS1='$(ps1_)'
