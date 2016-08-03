#!/bin/bash
exec 0<$1
while read line;do	
echo "Line is: $line"
done
