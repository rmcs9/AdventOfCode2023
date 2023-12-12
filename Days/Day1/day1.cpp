using namespace std;
#include <string>
#include <fstream>
#include <iostream>
#include "day1.h"


int day1::calculate(std::string filepath) {
    ifstream file(filepath);

    int total = 0;
    string currentLine;
    int lines = 0;

    unordered_map<string, char> wordToNumberMap;
    wordToNumberMap["one"] = '1';
    wordToNumberMap["two"] = '2';
    wordToNumberMap["three"] = '3';
    wordToNumberMap["four"] = '4';
    wordToNumberMap["five"] = '5';
    wordToNumberMap["six"] = '6';
    wordToNumberMap["seven"] = '7';
    wordToNumberMap["eight"] = '8';
    wordToNumberMap["nine"] = '9';

    while(getline(file, currentLine)){
        char firstWord = '_', lastWord = '_';
        int firstWordIndex = 500, lastWordIndex = -1;
        //iterate through the num words map and attempt to match word nums in the line
        for(unordered_map<string, char>::iterator k = wordToNumberMap.begin(); k != wordToNumberMap.end(); k++){
            size_t index = currentLine.find(k->first);
            int ind1 = static_cast<int>(index);
            if(index != string::npos){

                if(firstWordIndex == -1){
                    firstWordIndex = ind1;
                    firstWord = k->second;
                }
                else if(ind1 < firstWordIndex){
                    firstWordIndex = ind1;
                    firstWord = k->second;
                }

            }
            index = currentLine.rfind(k->first);
            int ind2 = static_cast<int>(index);
                if (index != string::npos) {

                    if (lastWordIndex == -1) {
                        lastWordIndex = ind2;
                        lastWord = k->second;
                    } else if (ind2 > lastWordIndex) {
                        lastWordIndex = ind2;
                        lastWord = k->second;
                    }
                }
        }
        int firstNumberIndex = 500, lastNumberIndex = -1, j = 0;
       char firstNumber = '_', lastNumber = '_';
       //iterate through the input line and find any digits
       for(string::iterator i = currentLine.begin(); i != currentLine.end(); i++){
           if(std::isdigit(*i)){
                if(firstNumber == '_'){
                    firstNumber = *i;
                    firstNumberIndex = j;
                }
                else{
                    lastNumber = *i;
                    lastNumberIndex = j;
                }
           }
           j++;
       }
       //if there are not multiple digits, make the last digit equal to the first
       if(lastNumberIndex == -1){
           lastNumber = firstNumber;
           lastNumberIndex = firstNumberIndex;
       }
        char numbers[2] = {'_', '_'};
        //if the first digit occurs before the first word, make the first digit the first number
       if(firstNumberIndex < firstWordIndex){
           numbers[0] = firstNumber;
       }
       //else make the first word the first number
       else{
           numbers[0] = firstWord;
       }
       //same idea for the last digit and word
      if(lastNumberIndex > lastWordIndex){
           numbers[1] = lastNumber;
       }
       else{
           numbers[1] = lastWord;
       }

        lines++;
       //DEBUG
//        if(lastNumberIndex == -1) {
//            cout << "line: ";
//            cout << lines;
//            cout.flush();
//            cout << "  num 1: ";
//            cout.flush();
//            cout << firstNumber;
//            cout.flush();
//            cout << "  first word: ";
//            cout.flush();
//            cout << firstWord;
//            cout.flush();
//            cout << "  num 2: ";
//            cout.flush();
//            cout << lastNumber;
//            cout.flush();
//            cout << "  last word  ";
//            cout.flush();
//            cout << lastWord;
//            cout.flush();
//            int linetotal = stoi(numbers);
//            cout << " total: " << linetotal;
//            cout << '\n';
//            cout.flush();
//        }
        //accumulate total
        total += stoi(numbers);

    }
   return total;
}
