#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "day9.h"


void day9::extrapolate(std::string fp) {
    std::fstream data(fp);

    std::vector<std::vector<int>> histories;

    do{
        std::string historyline;
        getline(data, historyline);

        std::vector<int> *history = new std::vector<int>;
        std::istringstream stream(historyline);
        do{
            int record;
            stream >> record;
            history->push_back(record);
        }while(!stream.eof());

        histories.push_back(*history);
    }while(!data.eof());

    int totalExtrapolations = 0;
    int totalReverseExtrapolations = 0;
    for(auto &history : histories){
        std::vector<std::vector<int>> *current = new std::vector<std::vector<int>>;
        current->push_back(history);
        getSubSequences(*current);
        totalExtrapolations += getExtrapolatedValue(*current);
        totalReverseExtrapolations += getReverseExtrapolatedValue(*current);
    }
    std::cout << "extrapolated total: " << totalExtrapolations << '\n';
    std::cout << "reverse extrapolated total: " << totalReverseExtrapolations << '\n';
}


//takes in a vector of int vectors and adds a vector representing each descending step
void day9::getSubSequences(std::vector<std::vector<int>> &sequences) {
    //sub sequence is a vector for the next descending step
    std::vector<int> *subSequence = new std::vector<int>;
    //current sequence is the previous step/original history line(if you just entered the function
    std::vector<int> currentSequence = sequences.back();
    //calculate the next step row
    for(auto item = currentSequence.begin(); item != currentSequence.end() - 1; item++){
        subSequence->push_back(*(item + 1) - *item);
    }
    //determine if all steps are done(function has reached a row of all zeros)
    bool done = true;
    for(auto item : *subSequence){
        if(item != 0){
            done = false;
        }
    }
    //push the current step into the sequence
    sequences.push_back(*subSequence);
    //if done return, if not get the next row of step
    if(done){
        return;
    }
    else{
        getSubSequences(sequences);
    }
}


int day9::getExtrapolatedValue(std::vector<std::vector<int>> sequences) {
    int previousRow = 0;
    std::reverse(sequences.begin(), sequences.end());
    for(auto row = sequences.begin(); row != sequences.end() - 1; row++){
        previousRow = (row + 1)->back() + previousRow;
    }
    return previousRow;
}

int day9::getReverseExtrapolatedValue(std::vector<std::vector<int>> sequences) {
    int previousRow = 0;
    std::reverse(sequences.begin(), sequences.end());
    for(auto row = sequences.begin(); row != sequences.end() - 1; row++){
        previousRow = (row + 1)->front() - previousRow;
    }
    return previousRow;
}