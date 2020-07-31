#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

/* Constants */
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,;!?";

/* Prototypes */
int readFile(string filename, string &message);
int writeFile(string filename, string &message);
void encryptMessage(int key, string &message);
void decryptMessage(int key, string &message);
void removeCharacteres(string &message);

/* Functions */
int readFile(string filename, string &message)
{
    ifstream file;
    string line;
    file.open(filename, ios::in);
    if(!file)
    {
        cout << "Failed to read file." << endl;
        return 1;
    }
    while(!file.eof())
    {
        getline(file, line);
        message.append(line);
        message.append("\n");
    }
    file.close();
    return 0;
}
int writeFile(string filename, string &message)
{
    ofstream file;
    file.open(filename, ios::trunc);
    if(!file)
    {
        cout << "Failed to write file." << endl;
        return 1;
    }
    file << message << endl;
    file.close();
    return 0;
}
void encryptMessage(int key, string &message)
{
    // Encrypts character by character
    for(size_t k = 0; k < message.size(); k++)
    {
        int pos = letters.find(message[k], 0);
        if(pos != -1)
        {
            message[k] = letters[(pos + key) % letters.size()];
        }
        else
        {
            message[k] = '#';
        }
    }
}
void decryptMessage(int key, string &message)
{
    // Decrypts character by character
    for(size_t k = 0; k < message.size(); k++)
    {
        int pos = letters.find(message[k], 0);
        if(pos != -1)
        {
            message[k] = letters[(pos + letters.size() - key) % letters.size()];
        }
        else
        {
            message[k] = ' ';
        }
    }
}
void removeCharacteres(string &message)
{
    regex re ("[.,;!?]");
    string aux;
    cout << regex_replace(message, re, "") << endl;

    cout << aux << endl;
}
int main(int argc, char* argv[])
{
    // Array of string messages decrypt
    string messages[letters.size()];
    //
    string filename;
    //
    string message;
    //
    string aux;

    // Get the filename of message
    filename = argv[1];
    // Read file with the message
    if(readFile(filename, message))
    {
        return -1;
    }

    // Decrypt the message with n-key [0 ... 30]
    for(size_t k = 0; k < letters.size(); k++)
    {
        // Copy the message to aux
        aux.assign(message);
        decryptMessage(k, aux);
        // Store the message descrypted in array of messages
        messages[k] = aux;
    }

    aux = messages[19];
    removeCharacteres(aux);

    for(size_t k = 0; k < letters.size(); k++)
    {
        cout << messages[k] << endl;
    }

    // Get filename of the destination
    filename = argv[2];
    // Write file with a correct message decrypted
    if(writeFile(filename, messages[19]))
    {
        return -1;
    }

    return 0;
}
