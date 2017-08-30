#!/bin/bash

yellow=0
orange=1
tick=0
setup()
{
	for i in $yellow $orange ; do gpio mode $i out; done
	gpio write $yellow 1
}

flash()
{
	gpio write $yellow 1
	gpio write $orange 0
	sleep 0.5
	echo "bLep"
	echo " "
	gpio write $yellow 0
	gpio write $orange 1
	sleep 0.5
	echo "bLo0p"
	echo " "
	let tick=tick+1
	if [ $tick -eq 5 ]
	then
		gpio write $orange 0
		sleep 0.5
		echo "fLoNk"
		echo " "
		tick=0
	fi
		
}	
	

setup
while true; do
	flash
done
	
