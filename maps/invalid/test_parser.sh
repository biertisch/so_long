#!/bin/bash

PROG="./so_long"
MAP_DIR="maps/invalid"

# Check if valgrind is installed
if ! command -v valgrind &> /dev/null; then
	echo "Error: valgrind is not installed."
	exit 1
fi

# Test with no map
echo "------------------------------------"
echo "Testing with no map"

echo "Programme output:"
valgrind --leak-check=full --error-exitcode=42 --quiet "$PROG"
status=$?
if [ $status -eq 0 ]; then
	echo "Program exited normally (unexpected for invalid map)"
elif [ $status -eq 42 ]; then
	echo "Memory leak detected!"
else
	echo "Program exited with error code $status (likely due to invalid map)"
fi

# Test with each invalid map
for map in $MAP_DIR/*; do
	echo "------------------------------------"
	echo "Testing map: $map"

	echo -n "Programme output: "
	valgrind --leak-check=full --error-exitcode=42 --quiet "$PROG" "$map"

	status=$?

	if [ $status -eq 0 ]; then
		echo "Program exited normally (unexpected for invalid map)"
	elif [ $status -eq 42 ]; then
		echo "Memory leak detected!"
	else
		echo "Programme exited with error code $status (likely due to invalid map)"
	fi
done

echo "------------------------------------"
echo "All tests finished."