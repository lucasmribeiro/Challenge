#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

/* Constants */
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,;!?";

/* Variables */
ifstream fileIN;
ofstream fileOUT;

/* Prototypes */
int readFile(string filename, string &message);
int writeFile(string filename, string &message);
void encryptMessage(int key, string &message);
void decryptMessage(int key, string &message);

/* Functions */
int readFile(string filename, string &message)
{
    string line;
    fileIN.open(filename, ios::in);
    if(!fileIN)
    {
        cout << "Failed to read file." << endl;
        return 1;
    }
    while(!fileIN.eof())
    {
        getline(fileIN, line);
        message.append(line);
        message.append("\n");
    }
    fileIN.close();
    return 0;
}

int writeFile(string filename, string &message)
{
    fileOUT.open(filename, ios::trunc);
    if(!fileOUT)
    {
        cout << "Failed to write file." << endl;
        return 1;
    }
    fileOUT << message << endl;
    fileOUT.close();
    return 0;
}

void encryptMessage(int key, string &message)
{
    for(size_t k = 0; k < message.size(); k++)
    {
        size_t pos = letters.find(message[k], 0);
        if(k != -1)
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
    for(size_t k = 0; k < message.size(); k++)
    {
        size_t pos = letters.find(message[k], 0);
        if(k != -1)
        {
            message[k] = letters[(pos + letters.size() - key) % letters.size()];
        }
        else
        {
            message[k] = ' ';
        }
    }
}

int main(int argc, char* argv[])
{
    string filename, message;
    filename = argv[1];
    if(readFile(filename, message))
    {
        return -1;
    }

    filename = argv[2];
    if(writeFile(filename, message))
    {
        return -1;
    }

    return 0;
}
