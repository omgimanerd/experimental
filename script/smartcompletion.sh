#/usr/bin/env bash
# Interesting smart completion

_generate_completions() {
  COMPREPLY=(".")
  IFS="/" read -ra TOKENS <<< "${COMP_WORDS[-1]}"
  for TOKEN in "${TOKENS[@]}"; do
    if [[ $TOKEN == "." ]]; then
      continue
    fi
    NEW_PATHS=()
    for A_PATH in "${COMPREPLY[@]}"; do
      for MATCH in "$A_PATH"/"$TOKEN"*; do
        if [[ -e "$MATCH" && -d "$MATCH" ]]; then
          NEW_PATHS+=("$MATCH")
        fi
      done
    done
    COMPREPLY=("${NEW_PATHS[@]}")
  done
}

complete -F _generate_completions -o dirnames -o nospace -o plusdirs cd
