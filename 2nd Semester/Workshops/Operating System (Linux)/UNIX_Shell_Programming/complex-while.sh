#!/bin/bash
#Read the console input until the user provides a filename the exists and can be read

F=""
while [ -z "$F" ] || [ ! -r "$F" ] || [ ! -f "$F" ]; do
	read -p "Provide an existing and readable file path:" F
done