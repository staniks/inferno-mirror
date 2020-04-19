#!/usr/bin/env bash
# Removes U+FEFF BOM invisible character from all files

function fix_file_bom() {
    local f="$1"
    echo -n "$f ..."
    local tmp=$( mktemp )
    if ! awk '{ if (NR==1) sub(/^\xef\xbb\xbf/,""); print }' "$f" > "$tmp"; then
        echo  "ERROR"
        rm -f "$tmp"
        return 1
    fi
    if ! cp "$tmp" "$f"; then
        echo "ERROR"
        return 1
    fi
    echo "DONE"
    return 0
}

find . -name '*.cpp' -or  -name '*.h' |
    ( while read f; do
          fix_file_bom "$f"
      done  )
