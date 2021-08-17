#!/usr/bin/env bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd "${SCRIPT_DIR}/.."
set -x
docker run -v "${pwd}":/data -it plutoo/cocos-cli python tools/tojs/genbindings.py

