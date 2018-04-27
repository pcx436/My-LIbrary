#!/bin/bash

# A simple script that will add an alias when provided it's two arguments.
# If you say "--help" or "-h" for an argument, it will tell you what you can do.
# If you look through the code, you'll see a few comments with equivalent statements in regex below them. The commented statements are from before I was able to use regex enough to do them simply.

# Command line arguments
if [[ $# -eq 1 ]]; then
	if [[ $1 =~ -(-)?h(elp)? ]]; then
		echo -e "This script will add an alias to the current user. It will prompt you for the alias name and the contents of the alias. It will prompt for approval after printing out what will be entered."
		exit
	fi
elif [[ $# -ge 2 ]]; then
	echo "Invalid arguments. Enter --help or -h for the help menu."
	exit
fi

# User entry variable
ans="n"
while [[ $ans =~ [nN] ]]; do
	finString="alias "
	fir=""
	sec=""

	# Variable used to tell if this is the first time
	firTru=true
	while [[ -z $fir ]]; do	

		# If they entered nothing:
		if ! $firTrue; then
			echo "#1 Invalid enter, must be non-empty. Try again:"
			firTrue=false
		fi

		echo -e "Enter alias name:"
		read fir

		firTrue=false
	done

	firTrue=true
	while [[ -z $sec ]]; do
		if ! $firTrue; then
			echo -e "#2 Invalid enter, must be non-empty. Try again:"
			firTrue=false
		fi

		echo -e "Enter alias contents:"
		read sec
			
		firTrue=false
	done
	firTrue=true

	# Asking for confirmation
	echo -e "\nIs this the alias you want (Y/n):"
	echo -e "alias $fir=\"$sec\""
	read ans

	# While choice is invalid & not empty
	while [[ ! $ans =~ [yYnN] ]] && [[ ! -z $ans ]]; do
		echo "Invalid answer. Must be Y, y, N, or n. (Empty input will be interpreted as a yes.)"
		read ans
	done

	
	if [[ $ans =~ [nN] ]]; then
		echo -e "Restarting script...\n\n"
	elif [[ $ans =~ [yY] ]] || [[ ${#ans} -eq 0 ]]; then
		echo -e "alias $fir=\"$sec\"" >> ~/.bash_aliases
		echo "Done!"
		cat ~/.bash_aliases
	fi
done
