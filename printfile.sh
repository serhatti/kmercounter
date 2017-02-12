#!/bin/bash

source printtop.sh

if [[ $# -ne 2 ]] ;then
  echo "Commandline Error. Usage:"
  echo "printfile <infile> <topcount>"
fi

printtop $1 $2
