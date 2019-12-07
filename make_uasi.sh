#!/bin/sh

make git-submodule
docker run --rm -v "$PWD":/qmk_firmware qmkfm/base_container sh -c 'cd /qmk_firmware && make ergodox_ez:uasi'
