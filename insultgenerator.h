//
// Created by Renner Siebens (18rgs1) on 2021-09-25.
//

#ifndef LAB1_INSULTGENERATOR_18RGS1_H
#define LAB1_INSULTGENERATOR_18RGS1_H


#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

//FileException class to account for if the file could not be opened or no file could be supplied.
class FileException {
public:
    FileException (const string& file_msg);
    string& what();
private:
    string file_msg;
};

//This exception class is to check if the size supplied is in the bounds of 1 and 10,000.
class NumInsultsOutOfBounds {
public:
    NumInsultsOutOfBounds(const string& bounds_msg);
    string& what();
private:
    string bounds_msg;
};

class InsultGenerator {
public:
    //The InsultGenerator constructor.
    InsultGenerator(); //null constructor
    //This function reads the supplied text file and puts the columns of strings into
    //3 seperate vectors. Throws as exception if there is an error with opening the file.
    void initialize();
    //initializes an array of size 3, where 3 random numbers are stored.
    //The random number stored in 0 position is the random number assigned to the first column.
    //Random number stored in 1 position is the number assigned to the second column, etc.
    string talkToMe();
    //recursive function that removes duplicates then replaces them with new values so that the size will not
    //be reduced. Passed by reference to ensure that the shakespearInsults vector is also changed.
    void sortAndRemove(vector<string>&, int size);
    //returns a random number using the rand operation.
    int randomNumber ();
    //This function generates a supplied number of insults using the talkToMe() function.
    vector<string> generate (const int size);
    //This function generates a supplied number of insults and saves them to a file
    //with a name supplied by the user.
    vector<string> generateAndSave (const string outputFile, const int size); //generates and saves insults to a file

private: //these are the different columns from the text file that are used in the initialize function.
    vector<string> firstColumn;
    vector<string> secondColumn;
    vector<string> thirdColumn;
};
#endif //INC_320_LAB1_INSULTGENERATOR_18RGS1_H




