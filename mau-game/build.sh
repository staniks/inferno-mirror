#!/usr/bin/env bash
# Copyright (C) 2020 by Marin Saric
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
# IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Note from author: OK to relicense as anything, including GPLv3, etc.
# Builds the whole project.
# build.sh [Debug] -- builds a debug version (exe in build/mau)
# build.sh Release -- builds a release version (exe in build/mau)
# build.sh rebuild [Release] -- rebuilds everything from scratch

cmd="$1"
if [[ "$cmd" == "rebuild" ]]; then
    shift
    rm -rf build
fi

reltype="$1"
if [[ "$reltype" == "" ]]; then
    reltype=Debug
fi
shift

echo "Release: "$reltype >/dev/stderr
mkdir -p build

cd build && cmake -DCMAKE_BUILD_TYPE=$reltype .. && make "${@}" && \
    echo "Built release: "$reltype >/dev/stderr
