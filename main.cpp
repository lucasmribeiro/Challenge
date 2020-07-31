#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <vector>

using namespace std;

/* Constants */
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,;!?";
const string dictWords = "./words.txt";

/* Prototypes */
int readFile(string filename, string &text);
int writeFile(string filename, string &text);
void encryptMessage(int key, string &text);
void decryptMessage(int key, string &text);
string removeCharacteres(string text);
string toUpperCase(string text);
string toLowerCase(string text);
int findKey(vector<int> match);
int wordExist(string word);

/* Functions */
int readFile(string filename, string &text)
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
        text.append(line);
        text.append("\n");
    }
    file.close();
    return 0;
}
int writeFile(string filename, string &text)
{
    ofstream file;
    file.open(filename, ios::trunc);
    if(!file)
    {
        cout << "Failed to write file." << endl;
        return 1;
    }
    file << text << endl;
    file.close();
    return 0;
}
void encryptMessage(int key, string &text)
{
    // Encrypts character by character
    for(size_t k = 0; k < text.size(); k++)
    {
        int pos = letters.find(text[k], 0);
        if(pos != -1)
        {
            text[k] = letters[(pos + key) % letters.size()];
        }
        else
        {
            text[k] = '#';
        }
    }
}
void decryptMessage(int key, string &text)
{
    // Decrypts character by character
    for(size_t k = 0; k < text.size(); k++)
    {
        int pos = letters.find(text[k], 0);
        if(pos != -1)
        {
            text[k] = letters[(pos + letters.size() - key) % letters.size()];
        }
        else
        {
            text[k] = ' ';
        }
    }
}
string removeCharacteres(string text)
{
    string ret;
    regex re ("[.,;!?]");
    ret = regex_replace(text, re, "");
    return ret;
}
string toUpperCase(string text)
{
    string ret;
    for (size_t k = 0; k < text.size(); k++)
        ret.push_back(toupper(text[k]));
    return ret;
}
string toLowerCase(string text)
{
    string ret;
    for (size_t k = 0; k < text.size(); k++)
        ret.push_back(tolower(text[k]));
    return ret;
}
int findKey(vector<int> combinations)
{
    int key = 0;
    for(size_t k = 0; k < combinations.size(); k++)
    {
        if(combinations[k] > key)
            key = k;
    }
    return key;
}
int wordExist(string word)
{
    ifstream file;
    string wordFile;
    string filename = "./Dictionary.txt";
    file.open(filename, ios::in);
    while(!file.eof())
    {
        getline(file, wordFile);
        // Verify if word exist in dictionary
        if(word == toUpperCase(wordFile))
        {
            file.close();
            return 1;
        }
    }
    file.close();
    return 0;
}

int main(int argc, char* argv[])
{
    // Vector of string messages decrypt
    vector<int> combinations;
    vector<string> words;
    string message[letters.size()];

    // Strings
    string filename;
    string text;
    string word;
    string aux;

    // Ifstream
    ifstream inputFile;
    ofstream outputFile;

    // Integer
    int key;

    // Get the filename of message
    filename = argv[1];

    cout << "Reading the message" << endl;
    // Read file with the message
    if(readFile(filename, text))
    {
        return -1;
    }

    cout << "Decrypt the message with n-keys" << endl;
    // Decrypt the message with n-key [0 ... 30]
    for(size_t k = 0; k < letters.size(); k++)
    {
        // Copy the message to aux
        aux.assign(text);
        decryptMessage(k, aux);
        // Store the message descrypted in array of messages
        message[k] = aux;
    }
    cout << "Verify what message is valid" << endl;
    // Verify what message is valid
    for(size_t k = 0; k < letters.size(); k++)
    {
        // Copy the message to auxiliar string
        aux.assign(message[k]);
        size_t i = 0;
        size_t j = aux.find(' ');

        cout << "Spliting the words" << endl;
        // Split the message with delimiter ' '
        while(j != string::npos)
        {
            words.push_back(removeCharacteres(aux.substr(i, j-i)));
            i = ++j;
            j = aux.find(' ', j);
            if (j == string::npos)
            {
                words.push_back(removeCharacteres(aux.substr(i, aux.size())));
            }
        }

        // Inicialize the combination with zero
        combinations.push_back(0);

        cout << "Verify if the words are valid" << endl;
        // Iterate the words of message
        for(size_t r = 0; r < words.size(); r++)
        {
            // Verify if word of message exists
            if(wordExist(words[r]))
                combinations[k]++;
            else
                break;
        }

        // Clean vector of words
        words.clear();
    }

    cout << "Finding the key" << endl;
    // Find the key
    key = findKey(combinations);

    // Print the key and the message
    cout << "Key is: " << key << endl;
    cout << "Message is: " << message[key] << endl;

    return 0;
}
