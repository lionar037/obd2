#!/bin/bash

COMMIT_ADD=$1

# Obtener la fecha y hora actual en el formato YYYYMMDDHHMM
timestamp=$(date +'%Y%m%d%H%M')

# Construir el mensaje de commit
commit_message="\t$timestamp \n$COMMIT_ADD"
echo "NAME GIT :"
echo -e ${commit_message}
# Ejecutar los comandos git
git add . && git commit -m "$timestamp $COMMIT_ADD" && git push -u origin main

