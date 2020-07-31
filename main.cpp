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
// Lê a mensagem de um arquivo
int readFile(string filename, string &text)
{
    ifstream file;
    string line;
    file.open(filename, ios::in);
    if(!file)
    {
        cout << "Falha na leitura do arquivo" << endl;
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
// Escreve a mensagem em um arquivo
int writeFile(string filename, string &text)
{
    ofstream file;
    file.open(filename, ios::trunc);
    if(!file)
    {
        cout << "Falha na escrita do arquivo" << endl;
        return 1;
    }
    file << text << endl;
    file.close();
    return 0;
}
// Criptografa caracter por caracter da mensagem
void encryptMessage(int key, string &text)
{
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
// Descriptografa caracter por caracter da mensagem
void decryptMessage(int key, string &text)
{
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
// Regex para remoção de caracteres especiais
string removeCharacteres(string text)
{
    string ret;
    regex re ("[.,;!?]");
    ret = regex_replace(text, re, "");
    return ret;
}
// Converte caracter por caracter para upperCase
string toUpperCase(string text)
{
    string ret;
    for (size_t k = 0; k < text.size(); k++)
        ret.push_back(toupper(text[k]));
    return ret;
}
// Converte caracter por caracter para lowerCase
string toLowerCase(string text)
{
    string ret;
    for (size_t k = 0; k < text.size(); k++)
        ret.push_back(tolower(text[k]));
    return ret;
}
// Obtém a chave com maior incidência de palavras corretas
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
// Avalia se a palavra existe no dicionário de palavras
int wordExist(string word)
{
    ifstream file;
    string wordFile;
    string filename = "./Dictionary.txt";
    file.open(filename, ios::in);
    while(!file.eof())
    {
        getline(file, wordFile);
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
    // Vetor de combinações para cada chave
    vector<int> combinations;
    // Vetor de palavras da mensagem
    vector<string> words;
    // Mensagens descriptografadas
    string message[letters.size()];

    // Nome do Arquivo
    string filename;
    // Mensagem lida
    string text;
    // String auxiliar
    string aux;

    // Chave
    int key;

    // Obtém o nome do arquivo informado por parametro 
    filename = argv[1];

    cout << "Lendo a mensagem criptografada" << endl;
    if(readFile(filename, text))
    {
        return -1;
    }

    cout << "Descriptografando a mensagem com as n-chaves [0 ... 30]" << endl;
    for(size_t k = 0; k < letters.size(); k++)
    {
        // Copiando a mensagem para a string auxiliar
        aux.assign(text);
        decryptMessage(k, aux);
        // Salvando a mensagem descriptografada no vetor de mensagens
        message[k] = aux;
    }
    cout << "Verificando a veracidade da mensagem" << endl;
    // Vericando mensagem por mensagem a incidência de palavras validas
    for(size_t k = 0; k < letters.size(); k++)
    {
        // Copiando a mensage para a string auxiliar
        aux.assign(message[k]);
        size_t i = 0;
        size_t j = aux.find(' ');

        cout << "Separando as palavras da mensagem descriptografada com a chave: " << k <<  endl;
        // Separando as palavras da mensagem
        while(j != string::npos)
        {
            // Removendo caracteres especiais para armazenar a palavra
            words.push_back(removeCharacteres(aux.substr(i, j-i)));
            i = ++j;
            j = aux.find(' ', j);
            if (j == string::npos)
            {
                // Removendo caracteres especiais para armazenar a palavra
                words.push_back(removeCharacteres(aux.substr(i, aux.size())));
            }
        }

        // Inicializa a chave com zero incidências
        combinations.push_back(0);

        cout << "Verificando as palavras da mensagem descriptografada com a chave: " << k << endl;
        // Percorrendo todas as palavras da mensagem
        for(size_t r = 0; r < words.size(); r++)
        {
            // Vericando se a palavra é válida
            if(wordExist(words[r]))
                combinations[k]++;
            else
                break;
        }

        // Limpando todas as palavras armazenadas
        words.clear();
    }

    cout << "Calculando qual é a chave" << endl;
    // Calcula a chave com maior incidência de acerto
    key = findKey(combinations);

    // Imprime a chave e a mensagem
    cout << "Chave: " << key << endl;
    cout << "Mensagem: " << message[key] << endl;

    return 0;
}
