#!/bin/bash

FILE=.venv
if test -f "$FILE"; then
   python3 -m virtualenv $FILE

   $FILE/bin/python -m pip install scons==4.5.2
fi


