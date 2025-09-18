#!/bin/bash

PROG="./so_long"
MAP_DIR="maps/"
TEMP_OUTPUT="/tmp/so_long_output.txt"
i=0

for map in $MAP_DIR/*.ber; do
	echo -e "\n------------------------------------"
    echo "Starting level: $i"

    "$PROG" "$map" > "$TEMP_OUTPUT" 2>&1

    last_line=$(tail -n 1 "$TEMP_OUTPUT")

    if [[ "$last_line" == "You won the game. So long!" ]]; then
        echo "Level completed!"
    elif [[ "$last_line" == "You lost the game. So long!" ]]; then
        echo "Level failed. Exiting..."
        break
    else
        echo "Unexpected program output. Exiting..."
        break
    fi

	if [ $i -eq 4 ]; then
		echo "------------------------------------"
		echo "All levels finished!"
		break;
	else
    	read -n 1 -s -p "Press Enter to continue to the next level..." key
		if [ "$key" != "" ]; then
    		echo -e "\nExiting..."
			break;
		fi
	fi

	((i++))
done

rm -f "$TEMP_OUTPUT"
