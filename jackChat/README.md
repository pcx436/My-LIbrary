# jackChat

jackChat is a simple TCP IP based chat program built in C++. It was developed as my final project for Computer Science 1300: Computer Science 1 (CSCI-1300) course in my first semester at CU.

## Prerequisites

1. You must be using a Unix/Linux based system. Confirmed to work on CentOS, Ubuntu, and Kali Linux. Unknown compatability for OSX.
2. You and the person you wish to communicate to must be on the same (local) network for this to function, unless the host uses port forwarding.
3. You must communicate the IP address of the host prior to connection. There is no way to communicate this automatically.
4. Example IP addresses are stored in "validIPs.txt". **Do not delete this file if you want to be able to see those examples**.

## Known Issues

1. Unsynchronized threads, causing problem where a message you receive will be on the same line of a message you're currently typing. However, does not interfere with sending messages.
2. Chat log system begins with a bunch of empty messages.
3. Connection broken upon host DHCP host renewal.

## Compiling from Source

This project was made using a Codeblocks project. In order to compile it without Codeblocks, using the command line, use `g++ -std=c++11 -pthread -I include/ src/*.cpp main.cpp`

## Development Background

This program was a real labor of love. It was a serious challenege to myself, considering it used:
* Pointers and references.
* Structs
* Multi-threading
* Dynamic memory allocation & managment

_None_ of these had been taught in class, since it was for beginners. So, I had to learn them myself. I ran into a lot of road blocks considering that the course assistants couldn't help me with their usage. But I finished it. And while this program has a few flaws, I'm still proud of the result!
