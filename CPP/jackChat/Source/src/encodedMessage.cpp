#include "encodedMessage.h"
using namespace std;

encodedMessage::encodedMessage()
{
    message = "";
    sent = false;
    messageSet = false;
    encoded = false;
}

encodedMessage::encodedMessage(string constructorMessage, bool encodedAlready)
{
    encoded = encodedAlready;
    message = constructorMessage;

    messageSet = true;
    sent = false;

    if(encoded)
        decode();
    else
        encode();


}

encodedMessage::~encodedMessage()
{
    //dtor
}

bool encodedMessage::encode()
{
    if (sent || !messageSet || encoded)
        return false;

    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < (int)message.length(); j++)
        {
            if((message[j] >= 'a' && message[j] <= 'z') || (message[j] >= 'A' && message[j] <= 'Z')){
                switch(message[j])
                {
                    case 'z' :
                        message[j] = 'a';
                        break;
                    case 'Z' :
                        message[j] = 'A';
                        break;
                    default :
                        message[j]++;
                }
            }
        }
    }
    encoded = true;
    return true;
}

bool encodedMessage::decode()
{
    if (sent || !messageSet || !encoded)
        return false;


    for(int i = 0; i < 13; i++)
    {

        for(int j = 0; j < (int)message.length(); j++)
        {
            if((message[j] >= 'a' && message[j] <= 'z') || (message[j] >= 'A' && message[j] <= 'Z')){
                switch(message[j])
                {
                    case 'a' :
                        message[j] = 'z';
                        break;
                    case 'A' :
                        message[j] = 'Z';
                        break;
                    default :
                        message[j]--;
                }
            }
        }
    }
    encoded = false;
    return true;
}

bool encodedMessage::setMessage(string mes)
{
    if(!messageSet || sent)
    {
        message = mes;
        encode();
        return true;
    }
    return false;
}

bool encodedMessage::send()
{
    if(!sent)
    {
        sent = true;
        return true;
    }
    return false;
}

string encodedMessage::getMessage()
{
    if(!sent)
        return message;
    else
        return "badLogThing";
}

bool encodedMessage::beenSent()
{
    return sent;
}
