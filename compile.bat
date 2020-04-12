#!/bin/bash
echo "please enter file name"
read NAME
echo $NAME
gcc -ansi -pedantic -Wall -Werror "$NAME".c -o "$NAME".out
"$NAME".out

