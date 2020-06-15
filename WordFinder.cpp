#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm> // used for find function to iterate through array
using namespace std;

void readFile(string fileName); // reads words from a file and writes words to another file
int countWords(string fileName); // counts number of words including duplicates
int countUnique(string fileName); // counts number of unique words
int numAppearances(string words[10000], string word); // returns number of times a word appears in a string vector of words
void findWild(string word, string fileName); // prints number of occurrences of words including ? as a wild character
int findWord(string word, string fileName); // counts the number of times the specified word appears in file fileName
bool compareStrings(string a, string b); // compares strings for similarity, with ? as a wildcard character

void readFile(string fileName) {
    ifstream inFile;
    inFile.open(fileName);

    ofstream outFile;
    outFile.open("words.txt");

    string tempWord = "";
    string tempLine = "";
    unsigned int index;
    while (getline(inFile, tempLine)) { // continue reading lines
        index = 0;
        //cout << "Length: " << tempLine.length() << endl;
        while (index < tempLine.length()){ // read characters from line
            if (isalpha(tempLine.at(index))) { // build word
                char tempChar = tolower(tempLine.at(index));
                tempWord = tempWord + tempChar;
                index++;
            }
            else if (!isalpha(tempLine.at(index))) { // reached break character, reset word
                outFile << tempWord << " ";
                index++;
                tempWord = "";
            }
             if (index >= tempLine.length()) {
                outFile << tempWord << endl;
                tempWord = "";
                break;
            }
        }
    }
}

int countWords(string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    string word;
    int words = 0;
    while (!inFile.eof()) {
        inFile >> word;
        if (inFile.eof())
            break;
        words = words+1;
    }
    return words;
}

int countUnique(string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    string words[10000];
    string word = "";
    bool hasWord = false;
    int index = 0;
    while (!inFile.eof()) {
        inFile >> word;
        hasWord = false;
       // check all previous words for search word
        if (find(words, words+10000, word) != words+10000) {// word already exists in words
            hasWord = true;
        }
        if (hasWord == false) { // word is not yet in list
            words[index] = word;
            index++;
        }
        
    }
    return index;
}
    
void findWild(string word, string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    string words[10000]; // array for all words in the text
    string curr; // string for curr string on iteration
    string valid[10000]; // array for unique strings for printing
    int counts[10000]; // array for count of each string
    int index = 0;

    while (inFile >> curr) {
        //TODO
        words[index] = curr;
        index++;
    }
    int index2 = 0; // index for iterating through val
    //todo: fix bugs here
    for (int i = 0; i < index; i ++) { // iterate through all words
        if (compareStrings(word, words[i]) == true) { // found target in array of words
            if (find(valid, valid+10000, words[i]) >= valid+10000) { // array doesn't yet contain string
                valid[index2] = (words[i]); // each word in valid corresponds to a value in counts
                counts[index2] = (numAppearances(words, words[i])); // number of times words appear
                index2++;
            }
        }
    }
    // iterate through valid
    for ( int i = 0; i < index2; i ++) {
        cout << "The word " << valid[i] << " appears " << counts[i] << " times in the document" << endl;
    }
    cout << endl;
}

int numAppearances(string words[10000], string word) {
    int count = 0;
    for (unsigned int i = 0; i < 10000; i ++) {
        if (words[i] == word) {
            count++;
        }
    }
    return count;
}
int findWord(string word, string fileName) {
    ifstream inFile;
    inFile.open(fileName);

    string words[10000];
    string curr;
    int index = 0;
    int count = 0;
    while (!inFile.eof()) {
        inFile >> curr;
        if (inFile.eof())
            break;
        words[index] = curr;
        index++;
    }
    for (unsigned int i = 0; i < 10000; i++) {
        if (word == words[i]) {
            count++;
        }
        
    }
    return count;
}

bool compareStrings(string a, string b) { // used for comparing strings with wildcard
    // a is the string with ?s
    if (b.length() > a.length())
        return false;
    if (a == b)
        return true;
    unsigned int index = 0;
    for (unsigned int i = 0; i < a.length(); i ++) {
        if (isalpha(a[i])) {
            if (index >= b.length()) {
                return false;
            }
            else if (a[i] != b[i]) {
                return false;
            }
            else {
                index++;
                continue;
            }
        }
        else if (a[i] == '?') {
            index++;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    readFile(argv[1]);
    cout << "The number of words found in the file was " << countWords("words.txt") << endl;
    cout << "The number of distinct words found in the file was " << countUnique("words.txt") << endl;
    cout << "\n";
    string userInput = "";
    cout << "Please enter a word: ";
    while (cin >> userInput) {
        for (unsigned int i = 0; i < userInput.length(); i++) {
            if (isalpha(userInput.at(i))) {
                userInput[i] = tolower(userInput[i]);
            }
        }
        if (userInput.find("?") != std::string::npos) {
            //cout << "finding wild";
            findWild(userInput, "words.txt");
        }
        else {
            //cout << "finding word";
            cout << "The word " << userInput << " appears " << findWord(userInput, "words.txt") << " times in the document" << endl;
            cout << endl;
        }
        cout << "Please enter a word: ";
    }

}


