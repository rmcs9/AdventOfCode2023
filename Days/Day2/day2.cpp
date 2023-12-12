using namespace std;
#include "day2.h"
#include <string>
#include <fstream>
#include <iostream>



int day2::possibleGames(std::string filepath) {
    ifstream data(filepath);

    string currentline;
    int total = 0;
    while(getline(data, currentline)){

        string::iterator line = currentline.begin();
        //skip "Game "
        line += 5;

        char gameid[3];
        int i = 0;
        while(*line != ':'){
            gameid[i] = *line;
            i++;
            line++;
        }

        int id = stoi(gameid);
        //advance past colon and whitespace
        line += 2;

        int red = -1, blue = -1, green = -1;
        bool isPossible = true;
        while(line != currentline.end()){
            char cnum[2] = {' ', ' '};
            int i = 0;
            do{
                cnum[i] = *line;
                i++;
                line++;
            }while(*line != ' ');
            //advance to first char of the color
            line += 1;
            if(*line == 'r'){
                red = stoi(cnum);
                line += 3;
            }
            else if(*line == 'b'){
                blue = stoi(cnum);
                line += 4;
            }
            else if(*line == 'g'){
                green = stoi(cnum);
                line += 5;
            }
            else{
                cout << "something strange happened. char " << *line << " found when expecting color string";
            }

            if(*line == ';'){
                isPossible = red <= 12 && green <= 13 && blue <= 14;
                if(!isPossible){
                    break;
                }
                //reset
                red = -1, green = -1, blue = -1;
            }
            else if(*line == '\0'){
                isPossible = red <= 12 && green <= 13 && blue <= 14;
                break;
            }
            line += 2;
        }
        if(isPossible){
            total += id;
        }
    }

    return total;
}

int day2::powerGames(std::string filepath) {
    ifstream data(filepath);

    string currentline;
    int total = 0;
    while(getline(data, currentline)){

        string::iterator line = currentline.begin();
        //skip "Game "
        line += 5;

        char gameid[3];
        int i = 0;
        while(*line != ':'){
            gameid[i] = *line;
            i++;
            line++;
        }

        int id = stoi(gameid);
        //advance past colon and whitespace
        line += 2;

        int red = -1, blue = -1, green = -1;
        while(line != currentline.end()){
            char cnum[2] = {' ', ' '};
            int i = 0;
            do{
                cnum[i] = *line;
                i++;
                line++;
            }while(*line != ' ');
            //advance to first char of the color
            line += 1;
            int val = stoi(cnum);
            if(*line == 'r'){
                if(val > red) {
                    red = val;
                }
                line += 3;
            }
            else if(*line == 'b'){
                if(val > blue) {
                    blue = val;
                }
                line += 4;
            }
            else if(*line == 'g'){
                if(val > green) {
                    green = val;
                }
                line += 5;
            }
            else{
                cout << "something strange happened. char " << *line << " found when expecting color string";
            }
            if(*line == '\0'){
                break;
            }
            line += 2;
        }

        total += (red * blue * green);
    }

    return total;
}