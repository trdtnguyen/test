#!/bin/bash
stringZ=abcABC123ABCabc
#       123456789......
echo ${#stringZ}
expr "$stringZ" : "abc[A-Z]*.2"
expr substr "$stringZ" 3 5
expr index $stringZ C
echo ${stringZ:0}
echo ${stringZ:l:5}
expr "$stringZ" : "\(..[a-z]..[A-Z]\)"
