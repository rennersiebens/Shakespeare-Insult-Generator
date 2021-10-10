//
// Created by Renner Siebens (18rgs1) on 2021-09-25.
//

#include <iostream>
#include <string>
#include <algorithm>
#include "insultgenerator.h"



using namespace std;


//null constructor
InsultGenerator::InsultGenerator() {}
const int MAX = 10000;


void InsultGenerator::initialize () {
    //define a string line, that will constantly change per line of the input text file.
    string line;
    ifstream inFile;
    inFile.open("InsultsSource.txt");
    //check to see if opening the file worked.
    if (inFile.fail()) {
        //Else, supply the message Illegal File to the FileException class.
        throw FileException("\nIllegal File.");
    }
    //Read the inFile lines into line until you reach the end of the file.
    //The fileIn >> aVal will skip all white space and gives the data value you were looking for.
    //Each time a new string is read into line use .push_back() to put that value in the
    // correct vector depending on the column it is within in the text file.
    while (!inFile.eof()) {
        inFile >> line;
        firstColumn.push_back(line);
        inFile >> line;
        secondColumn.push_back(line);
        inFile >> line;
        thirdColumn.push_back(line);
        }
    inFile.close();
}


int InsultGenerator::randomNumber () {
    return (rand() % sizeof(firstColumn)); //just get the size of one of the columns.
}

string InsultGenerator::talkToMe() {
    int randomNums [3];
    //fill an array with 3 random numbers.
    for (int i = 0; i < sizeof(randomNums); i++)
        randomNums [i] = randomNumber();

    //Create the string roast with "Thou" at the front and "!" at the back.
    string roast = "Thou " + firstColumn [randomNums[0]] +
                    " " + secondColumn [randomNums[1]]  +
                    " " + thirdColumn [randomNums[2]] + "!";
    return roast;
}

vector<string> InsultGenerator::generate(const int size) {
    if (size > MAX || size < 1) {
        throw NumInsultsOutOfBounds("Illegal number of insults supplied!");
    }
    vector<string> shakespearInsults;
    while (size > shakespearInsults.size()) {
        string roast = (talkToMe());
        shakespearInsults.push_back(roast);
    }
    sortAndRemove (shakespearInsults, size);
    return shakespearInsults;
}

vector<string> InsultGenerator::generateAndSave(const string outputFile, const int size) {
    ofstream outPutFile (outputFile);
    vector<string> shakespearInsults;
    if (size > MAX || size < 1) {
        //Throws this output message to the exception class NumInsultsOutOfBounds.
        throw NumInsultsOutOfBounds("Number of insults supplied out of bounds!");

    } else {
        while (size > shakespearInsults.size()) {
            shakespearInsults.push_back(talkToMe());
        }
        sortAndRemove (shakespearInsults, size); //function that removes and replaces
                                                    // duplicates and sorts the vector

        //After vector shakespearInsults has been sorted and duplicates have been removed,
        //save the file to outPutFile.
        for (int i = 0; i < size; i++) {
            outPutFile << shakespearInsults[i] + "\n";
        }
    }
    return shakespearInsults;
}

void InsultGenerator::sortAndRemove (vector<string>& toBeSorted, int size) {
    //This function removes duplicates in supplied vector.
    unique(toBeSorted.begin(), toBeSorted.end());
    if (toBeSorted.size() < size) {
        //create the number of new elements needed to get to the size supplied.
        for (int i = 0; i < (size - toBeSorted.size()); i++){
            toBeSorted.push_back(talkToMe());
        }
        //call until there are no more duplicates remaining and the
        //vector is the same as the supplied size.
        sortAndRemove (toBeSorted, size);
    }
    sort (toBeSorted.begin(), toBeSorted.end());
}

FileException::FileException(const string& file_msg) : file_msg(file_msg) {}
string& FileException::what() { return file_msg; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& bounds_msg) : bounds_msg(bounds_msg) {}
string& NumInsultsOutOfBounds::what() { return bounds_msg; }


