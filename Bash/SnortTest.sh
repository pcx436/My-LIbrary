#!/bin/bash
# A script that sees if various user-agents trigger Snort IDS/IPS rules on a specific server
declare -a agents
declare -a pages
declare -a error

agents[0]="hacker-browser"
agents[1]="hacker-browser1.0"
agents[2]="hacker-brows1.1"
agents[3]="hack-browser1.2"

pages[0]="exploitpage.html"
pages[1]="exploitpage.php"
pages[2]="exploitpage.php"
pages[3]="exploit.php"
pages[4]="exploit.htm"
pages[5]="31337.php"
pages[6]="1337.html"

NUM=1
IND=0
for a in ${agents[@]}; do
	for p in ${pages[@]}; do
		echo -e "Test #$NUM: curl --user-agent \"${a}\" --cookie \"login-status=1\" http://192.168.0.2/${p}"
		curl --user-agent "${a}" --cookie "login-status=1" http://192.168.0.2/${p}
		echo "Did it work (Y/n)?"
		read res
		while [[ ${#res} -eq 0 ]] || [[ ${#res} -gt 1 ]] && [[ ! $res =~ (Y|y|n|N) ]]; do
			echo "error: invalid input. Try again"
			read res
		done
		if [[ ! $res =~ (Y|y) ]]; then
			error[$IND]=$NUM
			((IND++))
		fi

		((NUM++))
	done
done

if [[ ${#error[@]} -ne 0 ]]; then
	echo "Problemed command(s)"
	for i in ${error[@]}; do
		echo "#$i"
	done
else
	echo "No errors reported"
fi
