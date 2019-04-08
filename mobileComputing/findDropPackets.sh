#!/bin/bash

dropPkt=0
rcdPkt=0

while IFS="" read -r line
do
    char="${line:0:1}"
    if [[ $char = "d" ]] 
    then
        dropPkt=$((dropPkt+1))
    elif [[ $char = "r" ]]
    then
        rcdPkt=$((rcdPkt+1))
    fi
done < "$1"

echo "The number of dropped packets are : ${dropPkt}"
echo "The number of received packets are : ${rcdPkt}"


