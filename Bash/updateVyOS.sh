#!/bin/bash
# A simple script used to automate the process of updating a collection of VyOS VMs

IPEND=70
IPFULL="192.168.0."
while [ $IPEND -lt 244 ]
do
	ssh root@"$IPFULL$IPEND" yum install epel-release
	((IPEND++))
done
echo -e "\n\nDone!!"
