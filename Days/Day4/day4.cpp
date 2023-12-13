using namespace std;
#include <string>
#include <fstream>
#include <iostream>
#include "day4.h"



int day4::winningCards(std::string filepath) {

    fstream data(filepath);

    int totalpoints = 0;
    string currentline;
    while(getline(data, currentline)){

        string::iterator i = currentline.begin();

        //advance to colon
        while(*i != ':'){
            i++;
        }
        //skip colon and space
        i += 2;

        unordered_map<int, int> winningNums;
        char num[2] ={' ', ' '};
        int initrun = 0;
        while(*i != '|'){
            if(isdigit(*i)){
                if(num[0] == ' '){
                    num[0] = *i;
                }
                else{
                    num[1] = *i;
                }
                i++;
            }
            else{
                i++;
                if(num[0] != ' '){
                    winningNums[stoi(num)] = 1;
                    initrun++;
                }
                num[0] = ' ';
                num[1] = ' ';
            }
        }

        cout << initrun << '\n';

        num[0] = ' ';
        num[1] = ' ';
        i += 2;
        int rowPoints = 0;
        initrun = 0;
        while(i != currentline.end()){
            if(isdigit(*i)){
                if(num[0] == ' '){
                    num[0] = *i;
                }
                else{
                    num[1] = *i;
                }
                i++;
            }
            else{
                if(num[0] != ' '){
                    initrun++;
                    cout << stoi(num) << ' ';
                    cout.flush();
                    if(winningNums[stoi(num)]){
                        if(rowPoints == 0){
                            rowPoints = 1;
                        }
                        else{
                            rowPoints *= 2;
                        }
                    }
                }
                i++;
                num[0] = ' ';
                num[1] = ' ';
            }
        }
        if(num[0] != ' '){
            initrun++;
            cout << stoi(num) << ' ';
            cout.flush();
            if(winningNums[stoi(num)]){
                if(rowPoints == 0){
                    rowPoints = 1;
                }
                else{
                    rowPoints *= 2;
                }
            }
        }
        cout << "\n";

        cout << initrun << '\n';

        totalpoints += rowPoints;
    }

    return totalpoints;
}


int day4::winningCards2(std::string filepath) {

    fstream data(filepath);
    int *matches = new int[198];
    for(int i = 0; i < 198; i++){
        matches[i] = 0;
    }

    string currentline;
    int linenum = 0;
    while(getline(data, currentline)){

        string::iterator i = currentline.begin();

        //advance to colon
        while(*i != ':'){
            i++;
        }
        //skip colon and space
        i += 2;

        unordered_map<int, int> winningNums;
        char num[2] ={' ', ' '};
        while(*i != '|'){
            if(isdigit(*i)){
                if(num[0] == ' '){
                    num[0] = *i;
                }
                else{
                    num[1] = *i;
                }
                i++;
            }
            else{
                i++;
                if(num[0] != ' '){
                    winningNums[stoi(num)] = 1;
                }
                num[0] = ' ';
                num[1] = ' ';
            }
        }


        num[0] = ' ';
        num[1] = ' ';
        i += 2;
        while(i != currentline.end()){
            if(isdigit(*i)){
                if(num[0] == ' '){
                    num[0] = *i;
                }
                else{
                    num[1] = *i;
                }
                i++;
            }
            else{
                if(num[0] != ' '){
                    if(winningNums[stoi(num)]){
                        matches[linenum]++;
                    }
                }
                i++;
                num[0] = ' ';
                num[1] = ' ';
            }
        }
        if(num[0] != ' '){
            if(winningNums[stoi(num)]){
               matches[linenum]++;
            }
        }
        linenum++;
    }

    int totalCards = 0;
    for(int i = 0; i < 198; i++){
        totalCards++;
        totalCards += winningCards2Helper(i, matches[i], matches);
    }

    return totalCards;
}

int day4::winningCards2Helper(int index, int match, int *mat){
    int cards = 0;
    for(int i = index + 1; i < index + match + 1; i++){
        cards++;
        cards += winningCards2Helper(i, mat[i], mat);
    }
    return cards;
}