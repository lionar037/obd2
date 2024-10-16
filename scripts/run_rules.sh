#!/bin/bash

LINK_RULES=$PWD/others/rules.gdb
LINK_APP=$PWD/bin/ELM327_app

echo "$PWD"

sudo gdb -x $LINK_RULES $LINK_APP

