#!/bin/bash

forward=0
reverse=1

setup()
{
	for i in $forward $reverse ; do gpio mode $i out; done
	gpio write $forward 0
	gpio write $reverse 0	
}

flash()
{
	gpio write $reverse 1
	#~ gpio write $forward 0
	echo "uno"
	sleep 1
	
	#~ gpio write $forward 1
	gpio write $reverse 0
	echo "dos"
	sleep 1	
	
	gpio write $forward 1
	#~ gpio write $reverse 0
	echo "tres"
	sleep 1	
	
	gpio write $forward 0
	#~ gpio write $reverse 0
	echo "quatro"
	sleep 1	
}	
	

setup
while true; do
	flash
done
	
