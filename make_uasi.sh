#!/bin/sh

docker run -e keymap=uasi -e keyboard=ergodox_ez --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
