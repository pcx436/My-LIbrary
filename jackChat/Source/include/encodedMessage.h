#ifndef ENCODEDMESSAGE_H
#define ENCODEDMESSAGE_H
#include <string>

class encodedMessage
{
    public:
        // Constructors
        encodedMessage();                   // Default constructor
        encodedMessage(std::string, bool);        // Constructor that allows you to specify the secret message and the algorithm to use.

        // Destructor
        ~encodedMessage();                  // Obligatory destructor

        // Setters
        bool setMessage(std::string);            // Set the message. Wont allow you to do so if it has been sent.
        bool send();                        // Set the sent variable to true. Cannot be set back to false.

        // Getters
        std::string getMessage();                // Get the message that has been set.
        bool beenSent();                    // Returns true if the message has been sent, false otherwise.

    private:
        bool encode();                      // This will be called to do the encoding on the message.
        bool decode();                      // This will be called to decode a message.
        std::string message;                     // Data member to store the unencoded message. Will be erased upon encoding.

        bool encoded;                       // Data member to know if the message has been encoded
        bool messageSet;                    // Data member to know if the encoded message has been set.
        bool sent;                          // Data member to know if the encoded message has been sent.
};

#endif // ENCODEDMESSAGE_H
