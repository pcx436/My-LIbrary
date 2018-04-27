#include <vector>
#include <fstream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sstream>
#include <iostream>
#include <chrono>
#include <time.h>
#include <encodedMessage.h>

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

class networkManager
{
    public:
        networkManager();               // Default constructor
        networkManager(std::string[]);       // Constructor that sets if you're host, the destination IP or source IP address, and user name
        ~networkManager();

        bool amIHost();                 // returns true if you're hosting, false otherwise
        std::string getIP();                 // Get the destination IP address
        std::string getName();               // Get your user name
        bool connectionOpen();          // Tell you if the connection is open or not.

        void listenr();
        void sender();
        void makeSocket();

        bool setIP(std::string);             // Change the destination IP address
        bool setName(std::string);           // Change your user name

        bool sendMessage(encodedMessage);
        std::string validIP(std::string);

    private:
        bool isHost;                    // Variable to know if you're in server or client mode.
        bool openConnection;            // Variable to know if the connection is open or not.
        int cSocket, nSocket;
        std::string IP;                      // Variable to keep track of the source or destination IP address
        std::string userName;                // Sets the user name that will appear in the chat as you talk.
        std::string otherUser;
        std::vector <std::string> timeStamps;
        std::vector <encodedMessage> messagesReceived;
        std::vector <bool> youSaid;

        void recordMessage(encodedMessage, bool);
        bool writeMessages();

};

#endif // NETWORKMANAGER_H
