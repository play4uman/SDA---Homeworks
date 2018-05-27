#!/bin/bash

if  [[ ! $2 =~ http://lzdx.bfra.bg/logs/201[0-9] ]]; then
	echo "Invalid download link!"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Invalid directory!"
	exit 2
fi

participants=$(curl -s ${2} | tail -n +11 | head -n -2 | tr -s ' '|cut -d ' ' -f 5 | grep -o '".*"' | sed 's/"//g')

for i in $participants; do
   curl http://lzdx.bfra.bg/logs/2017/${i} > ${1}/${i}.txt
done;

