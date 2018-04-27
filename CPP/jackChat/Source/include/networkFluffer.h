// Not used.
#ifndef NETWORKFLUFFER_H
#define NETWORKFLUFFER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class networkFluffer
{
    public:
        // Constructors
        networkFluffer();                       // Default constructor
        networkFluffer(string);                 // Constructor that sets the name of the network fluffer
        networkFluffer(string, char, char);     // Constructor that sets the name, activator, and markup character of the fluffer.

        ~networkFluffer();                      // Obligatory destructor

        // Getters
        string getName();
        char getActiv();
        char getMark();
        void getInsults(vector <string>);
        void getCompliments(vector <string>);

        string markup(string);                  // Convert a string to a marked up string should it have the markup character. If it doesn't have the character return the original string.
        void command(string);                   // Do a command if the beginning of the line starts with the activator character. act accordingly if it has a valid command

        // Setters
        bool setName(string);
        bool setActivator(char);
        bool setMarkup(char);

        // Add insults or compliments, respectively
        bool addInsults(vector <string>);
        bool addCompliments(vector <string>);


        bool eraseInsults();                    // Wipe the insult vector.
        bool eraseCompliments();                // Wipe the compliment vector.
        string removeCompliment(int);           // Removes an compliment at provided index from the compliment array
        string removeInsult(int);               // Removes an insult at provided index from the insult array

    private:
        // Commands
        string roll(string);                    // Roll a N sided dice X times. String entered as XdN
        string insult(string, int);             // Grabs a specified number of random insults from the insults array and returns them
        string compliment(string, int);         // Grabs a specified number of random compliments from the compliments array and returns them
        string yell(string);                    // Makes a lot of spaces and essentially shouts something for you
        void tts(string);                       // Text to speech? Not sure if i want to do this.

        // Data members
        string name;                            // Name of the fluffer. Personally, I like "Choity" the chat bot :D
        char activator;                         // The character that will used for activation. Can't be a letter.
        char markupChar;                        // The character that is used in markup, default '*'
        vector <string> insults;                // Vector array of insults
        vector <string> compliments;            // Vector array of compliments
};

#endif // NETWORKFLUFFER_H
