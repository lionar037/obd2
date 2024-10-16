
#!/bin/bash

PAIR=00:00:00:00

COM=$1

if [[ $COM == "blue" ]]; then
	bluetoothctl
fi



if [[ $COM == "scan" ]]; then
        agent on
	scan on
fi


if [[ $COM == "pair" ]]; then
        ¢pair $PAIR    
        
fi
