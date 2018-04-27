#include "networkManager.h"

using namespace std;
networkManager::networkManager()
{
    isHost = true;
    int sizeV = 10000;
    timeStamps.resize(sizeV);
    messagesReceived.resize(sizeV);
    youSaid.resize(sizeV);

    for(int i = 0; i < sizeV; i++)
    {
        timeStamps[i] = "";
        youSaid[i] = false;
    }

    openConnection = false;
    userName, IP = "";
    cSocket, nSocket = -1;
}

networkManager::networkManager(string strStuff[])
{
    int sizeV = 10000;
    timeStamps.resize(sizeV);
    messagesReceived.resize(sizeV);
    youSaid.resize(sizeV);

    int i = 0;
    while(i < sizeV)
    {
        timeStamps[i] = "";
        youSaid[i] = false;
        i++;
    }

    nSocket, cSocket = -1;
    if(strStuff[0] == "1")
        isHost = true;
    else if(strStuff[0] == "2")
        isHost = false;
    else
        cout << "HOST PARAMETER ERROR" << endl;

    cout << "Network manager being created..." << endl;
    IP = strStuff[1];
    userName = strStuff[2];
    openConnection = false;
    makeSocket();

    //cout << "DONT" << endl;
    //openConnection = true;
    cout << "Network manager has been completed!\nWhen finished please enter \"S_EXIT\" (without the quotes)." << endl;
}

void networkManager::makeSocket()
{
    char *hello = new char[IP.length() +1];
    strcpy(hello, IP.c_str());
    bool timeToStop = false;

    if(isHost)
    {
        cSocket = socket(AF_INET, SOCK_STREAM, 0);
        int opt = 1;
        if(cSocket == 0)
        {
            timeToStop = true;
            cout << "Error in creating socket.";
        }


        if(!timeToStop && setsockopt(cSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            timeToStop = true;
            cout << "Error in setting socket options.";
        }

        if(!timeToStop)
        {
            struct sockaddr_in address;
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = inet_addr(hello);
            address.sin_port = htons(8080);


            if(bind(cSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
            {
                timeToStop = true;
                cout << "Error in binding to the socket." << endl;
            }

            if(!timeToStop && listen(cSocket, 3) < 0)
            {
                timeToStop = true;
                cout << "No connections makes me sad :(" << endl;
            }

            if(!timeToStop)
            {
                cout << "We are now hosting." << endl;

                socklen_t sits = sizeof(address);

                if(!timeToStop && (nSocket = accept(cSocket, (struct sockaddr *)&address, (socklen_t*)&sits)) < 0)
                {
                    timeToStop = true;
                }

                if(!timeToStop)
                {
                    openConnection = true;
                }
            }
        }
    }
    else
    {

        int port = 8080;
        struct hostent* host = gethostbyname(hello);

        sockaddr_in sendSockAddr;
        bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
        sendSockAddr.sin_family = AF_INET;
        sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));

        sendSockAddr.sin_port = htons(port);
        cSocket = socket(AF_INET, SOCK_STREAM, 0);
        nSocket = cSocket;
        //try to connect...
        int status = connect(cSocket, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
        if(status < 0)
        {
            timeToStop = true;
            cout<<"Error connecting to socket!"<<endl;
        }
        else
        {
            openConnection = true;

            cout << "Connected to the server!" << endl;
        }

    }

    delete hello;
    hello = nullptr;
}

networkManager::~networkManager()
{
    //dtor
}

bool networkManager::amIHost()
{
    return isHost;
}

string networkManager::getIP()
{
    return IP;
}

string networkManager::getName()
{
    return userName;
}

bool networkManager::connectionOpen()
{
    return openConnection;
}

bool networkManager::setIP(string newIP)
{
    if(!openConnection && cSocket == -1 && nSocket == -1)
    {
        IP = newIP;
        return true;
    }
    return false;
}

bool networkManager::setName(string newName)
{
    if(!openConnection && cSocket == -1 && nSocket == -1)
    {
        userName = newName;
        return true;
    }
    return false;
}

string networkManager::validIP(string ip)
{
    //Check length requirements
    if(ip.length() > 15 || ip.length() < 7)
        return "Invalid length. Must be [7,15] characters.";

    string cleaned = ip;

    int octNum = 0;
    string ret = "Bad character \"";
    //Check the string for characters that aren't numbers and '.'. Will also count '.'
    for(int i = 0; i < (int)ip.length(); i++)
        if(ip[i] != '.' && (ip[i] < '0' || ip[i] > '9'))
            return ret + ip[i] + "\" found"; // Bad character found
        else if(ip[i] == '.')
            octNum++;
    if(octNum != 3)
        return "Invalid number of octets:" + octNum; // Invalid number of octets.

    stringstream ss(ip);
    string octet;
    octNum = 1;
    while(getline(ss, octet, '.'))
    {
        if(octet.length() == 0 || octet.length() > 3)
            return "Invalid octet length:" + (int)octet.length();
        else
        {
            int a = stoi(octet);
            if(((octNum == 2 || octNum == 3) && (a > 255 || a < 0)))
                return "Octet size too great:" + octet;
            else if(((octNum == 1 || octNum == 4) && (a > 255 || a < 1)))
                return "Octet size too great:" + octet;
            stringstream bb;
            bb << a;
            string hi;
            bb >> hi;
            if(hi != octet)
                return "Extra characters in octet:" + octet;
            octNum++;
        }

    }
    return ip;

}

bool networkManager::writeMessages()
{
    time_t t;
    struct tm * now;
    time(&t);
    now = localtime(&t);

    string fileName;
    stringstream ss;
    ss << "jackChat-" << (now->tm_mon + 1) << "-" << (now->tm_mday) << "-" << (now->tm_year + 1900) << ".txt";
    ss >> fileName;
    ofstream write(fileName, ios::app);
    ss.flush();
    if(write.fail() || !write.is_open())
        return false;

    string beginChat = "--------START OF CHAT--------";
    string endChat = "-----------END OF CHAT-------";

    write.flush();
    write << beginChat << endl;
    write.flush();

    for(int i = 0; i < (int)messagesReceived.size(); i++){
        write.flush();

        write << timeStamps[i];
        write.flush();

        if(youSaid[i])
            write << userName;
        else
            write << otherUser;
        write.flush();
        write << ":" << messagesReceived[i].getMessage() << endl;
        write.flush();
    }
    write << endChat << endl;
    write.flush();

    write.close();
    return true;
}

void networkManager::listenr()
{
    time_t rawtime;
    struct tm * now;
    time(&rawtime);
    now = localtime(&rawtime);

    cout.flush();
    cout << asctime(now);
    cout.flush();

    char buffer[1500];
    memset(&buffer, 0, sizeof(buffer));//clear the buffer


    // Getting the username
    if(isHost)
    {
        recv(nSocket, (void *)&buffer, 1500, 0);
    }
    else
    {
        recv(cSocket, (void *)&buffer, 1500, 0);
    }
    string encodedUser(buffer);

    encodedMessage receivedUser(encodedUser, true);
    otherUser = receivedUser.getMessage();

    while(openConnection)
    {
        memset(&buffer, 0, sizeof(buffer));//clear the buffer

        if(isHost)
        {
            recv(nSocket, (void *)&buffer, 1500, 0);
        }
        else
        {
            recv(cSocket, (void *)&buffer, 1500, 0);
        }

        string buff(buffer);
        encodedMessage receivedMessage(buff, true);
        recordMessage(receivedMessage, false);


        if(receivedMessage.getMessage() == "S_EXIT")
        {
            cout << endl << otherUser << " has closed the connection. Please hit enter to quit." << endl;
            openConnection = false;
            writeMessages();
            break;
        }
        else
        {
            cout.flush();
            cout << "\b" << otherUser << ": " << receivedMessage.getMessage() << endl << ">";
            cout.flush();
        }
    }
}

void networkManager::recordMessage(encodedMessage message, bool youOrNot){
    if(message.getMessage().length() == 0)
        return;
    time_t rawtime;
    struct tm * now;
    time(&rawtime);
    now = localtime(&rawtime);

    stringstream stamp;
    stamp << (now->tm_hour) << ":" << (now->tm_min) << ">";

    string timeStamp;
    stamp >> timeStamp;

    messagesReceived.push_back(message);
    timeStamps.push_back(timeStamp);
    youSaid.push_back(youOrNot);
}

void networkManager::sender()
{
    char msg[1500];

    bool first = true;

    encodedMessage name(userName, false);
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, name.getMessage().c_str());
    this_thread::sleep_for(chrono::milliseconds(30));
    name.send();

    if(isHost)
    {
        send(nSocket, (char*)&msg, strlen(msg), 0);
    }
    else
    {
        send(cSocket, (char*)&msg, strlen(msg), 0);
    }

    while(1 && openConnection)
    {
        string data;
        if(first)
        {
            this_thread::sleep_for(chrono::milliseconds(30));
            first = false;
        }

        cout.flush();
        cout << ">";
        cout.flush();

        getline(cin, data);
        if(data.length() > 1500)
        {
            cout << "!You entered a string that's too long! Maximum of 1500 characters" << endl;
            continue;
        }
        encodedMessage toSend(data, false);

        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, toSend.getMessage().c_str());

        recordMessage(encodedMessage (toSend.getMessage(), true), false);
        if(isHost)
        {
            send(nSocket, (char*)&msg, strlen(msg), 0);
        }
        else
        {
            send(cSocket, (char*)&msg, strlen(msg), 0);
        }

        if(data == "S_EXIT")
        {
            openConnection = false;
            writeMessages();
            break;
        }

    }

}
