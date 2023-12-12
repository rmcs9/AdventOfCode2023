using namespace std;
#include <string>
#include <fstream>
#include <iostream>
#include "day3.h"



int day3::totalParts(std::string filepath) {
    ifstream data(filepath);

    auto partMap = new char[140][140];

    int i = 0;
    string currentline;

    while(getline(data, currentline)){
        int j = 0;

        for(string::iterator pos = currentline.begin(); pos != currentline.end(); pos++){
            partMap[i][j] = *pos;
            j++;
        }
        i++;
    }

    int total = 0;

    for(int i = 0; i < 140; i++){
        for(int j = 0; j < 140; j++){
            //symbol
            if(partMap[i][j] != '.' && isdigit(partMap[i][j]) == 0){
                vector<int> aboves;
                vector<int> belows;
                //above symbol
                for(int top = j - 1; top <= j + 1; top++){
                    //if a number is found in one of the 3 spots above the symbol...
                    if(partMap[i - 1][top] != '.' && isdigit(partMap[i - 1][top]) != 0){
                        //numstart is the initial number that is connected to the symbol
                        int numstart = top;
                        //find the beginning of the number
                        while(partMap[i - 1][numstart - 1] != '.'){
                            numstart--;
                        }
                        char num[3] = {' ', ' ', ' '};
                        int c = 0;
                        //scan the number into num[]
                        while(partMap[i - 1][numstart] != '.'){
                            num[c] = partMap[i - 1][numstart];
                            c++;
                            numstart++;
                        }
                        bool inList = false;
                        int number = stoi(num);
                        for(vector<int>::iterator list = aboves.begin(); list != aboves.end(); list++){
                            inList = *list == number;
                        }
                        if(!inList) {
                            aboves.push_back(number);
                        }
                    }
                }
                //below symbol
                for(int bottom =  j - 1; bottom <= j + 1; bottom++){
                    if(partMap[i + 1][bottom] != '.' && isdigit(partMap[i + 1][bottom]) != 0){
                        int numstart = bottom;

                        while(partMap[i + 1][numstart - 1] != '.'){
                            numstart--;
                        }
                        char num[3] = {' ', ' ', ' '};
                        int c = 0;
                        while(partMap[i + 1][numstart] != '.'){
                            num[c] = partMap[i + 1][numstart];
                            c++;
                            numstart++;
                        }
                        bool inList = false;
                        int number = stoi(num);
                        for(vector<int>::iterator list = belows.begin(); list != belows.end(); list++){
                            inList = *list == number;
                        }
                        if(!inList) {
                            belows.push_back(stoi(num));
                        }
                    }
                }
                //either side of symbol
                int leftside = -1, rightside = -1;
                //right side
                if(isdigit(partMap[i][j + 1])){
                    char num[3] = {' ', ' ', ' '};
                    for(int c = j + 1, x = 0; isdigit(partMap[i][c]); c++, x++){
                        num[x] = partMap[i][c];
                    }
                    rightside = stoi(num);
                }
                //left side
                if(isdigit(partMap[i][j - 1])){
                    char num[3] = {' ', ' ', ' '};
                    int start = j-1;
                    while(isdigit(partMap[i][start - 1])){
                        start--;
                    }
                    int c = 0;
                    while(isdigit(partMap[i][start])){
                        num[c] = partMap[i][start];
                        c++;
                        start++;
                    }
                    leftside = stoi(num);
                }

                for(vector<int>::iterator i = aboves.begin(); i != aboves.end(); i++){
                    total += *i;
                }
                for(vector<int>::iterator i = belows.begin(); i != belows.end(); i++){
                    total += *i;
                }

                if(rightside != -1){
                    total += rightside;
                }
                if(leftside != -1){
                    total += leftside;
                }
            }
        }
    }

    return total;
}



int day3::gearRatios(std::string filepath) {
    ifstream data(filepath);

    auto partMap = new char[140][140];

    int i = 0;
    string currentline;

    while(getline(data, currentline)){
        int j = 0;

        for(string::iterator pos = currentline.begin(); pos != currentline.end(); pos++){
            partMap[i][j] = *pos;
            j++;
        }
        i++;
    }

    int total = 0;


    for(int i = 0; i < 140; i++){
        for(int j = 0; j < 140; j++){
            //symbol
            if(partMap[i][j] == '*'){
                vector<int> aboves;
                vector<int> belows;
                //above symbol
                for(int top = j - 1; top <= j + 1; top++){
                    //if a number is found in one of the 3 spots above the symbol...
                    if(partMap[i - 1][top] != '.' && isdigit(partMap[i - 1][top]) != 0){
                        //numstart is the initial number that is connected to the symbol
                        int numstart = top;
                        //find the beginning of the number
                        while(partMap[i - 1][numstart - 1] != '.'){
                            numstart--;
                        }
                        char num[3] = {' ', ' ', ' '};
                        int c = 0;
                        //scan the number into num[]
                        while(partMap[i - 1][numstart] != '.'){
                            num[c] = partMap[i - 1][numstart];
                            c++;
                            numstart++;
                        }
                        bool inList = false;
                        int number = stoi(num);
                        for(vector<int>::iterator list = aboves.begin(); list != aboves.end(); list++){
                            inList = *list == number;
                        }
                        if(!inList) {
                            aboves.push_back(number);
                        }
                    }
                }
                //below symbol
                for(int bottom =  j - 1; bottom <= j + 1; bottom++){
                    if(partMap[i + 1][bottom] != '.' && isdigit(partMap[i + 1][bottom]) != 0){
                        int numstart = bottom;

                        while(partMap[i + 1][numstart - 1] != '.'){
                            numstart--;
                        }
                        char num[3] = {' ', ' ', ' '};
                        int c = 0;
                        while(partMap[i + 1][numstart] != '.'){
                            num[c] = partMap[i + 1][numstart];
                            c++;
                            numstart++;
                        }
                        bool inList = false;
                        int number = stoi(num);
                        for(vector<int>::iterator list = belows.begin(); list != belows.end(); list++){
                            inList = *list == number;
                        }
                        if(!inList) {
                            belows.push_back(stoi(num));
                        }
                    }
                }
                //either side of symbol
                int leftside = -1, rightside = -1;
                //right side
                if(isdigit(partMap[i][j + 1])){
                    char num[3] = {' ', ' ', ' '};
                    for(int c = j + 1, x = 0; isdigit(partMap[i][c]); c++, x++){
                        num[x] = partMap[i][c];
                    }
                    rightside = stoi(num);
                }
                //left side
                if(isdigit(partMap[i][j - 1])){
                    char num[3] = {' ', ' ', ' '};
                    int start = j-1;
                    while(isdigit(partMap[i][start - 1])){
                        start--;
                    }
                    int c = 0;
                    while(isdigit(partMap[i][start])){
                        num[c] = partMap[i][start];
                        c++;
                        start++;
                    }
                    leftside = stoi(num);
                }
                int totalgears = 0;
                int gearratio = 1;
                for(vector<int>::iterator i = aboves.begin(); i != aboves.end(); i++){
                    gearratio *= *i;
                    totalgears++;
                }
                for(vector<int>::iterator i = belows.begin(); i != belows.end(); i++){
                    gearratio *= *i;
                    totalgears++;
                }

                if(rightside != -1){
                    gearratio *= rightside;
                    totalgears++;
                }
                if(leftside != -1){
                    gearratio *= leftside;
                    totalgears++;
                }

                if(totalgears == 2){
                    total += gearratio;
                }
            }
        }
    }

    return total;
}