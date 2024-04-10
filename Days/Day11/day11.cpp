#include "day11.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>




void day11::lengthSum(std::string fp) {
    std::fstream data(fp);

    std::string line;
    std::vector<std::string> galaxies;
    do{
        data >> line;
        if(line.find('#') == std::string::npos){
            //add empty row to map
            std::string space;
            for(auto c : line){
                space += '.';
            }
            galaxies.push_back(space);
        }
        galaxies.push_back(line);
    }while(!data.eof());

    int linelength = line.length();
    for(int i = 0; i < linelength; i++){
        if(std::all_of(galaxies.begin(), galaxies.end(), [i](std::string line){
           return line.at(i) == '.';
        })){
            //add empty column to map
            for(auto &l : galaxies){
                l.insert(i, 1, '.');
            }
            i += 2;
            linelength++;
        }
    }

    //find all the stars
    std::vector<std::pair<int, int>> stars;
    int y = galaxies.size();
    for(auto l : galaxies){
        int length = l.length();
        for(int x = 0; x < length; x++){
            if(l.at(x) == '#'){
                stars.emplace_back(x,y);
            }
        }
        y--;
    }

    int sum = 0;
    while(!stars.empty()) {
        auto star1 = stars.back();
        for(auto star2 : stars){
            if(star1.first == star2.first && star1.second == star2.second){
                continue;
            }
            //distance between 2 points = x2 - x1 + y2 - y1
            sum += std::abs(star2.first - star1.first) + std::abs(star2.second - star1.second);
        }
        stars.pop_back();
    }

    std::cout << "total sum: " << sum << "\n";
}


void day11::lengthSumFARAWAY(std::string fp) {
    std::fstream data(fp);

    std::string line;
    std::vector<std::string> galaxies;
    do{
        data >> line;
        galaxies.push_back(line);
    }while(!data.eof());

    //instead of modding the map, just remember where the dead space is
    int linelength = line.length();
    std::vector<int> blackHoleColumns;
    for(int i = 0; i < linelength; i++){
        if(std::all_of(galaxies.begin(), galaxies.end(), [i](std::string line){
            return line.at(i) == '.';
        })){
            blackHoleColumns.push_back(i);
        }
    }
    //same idea for the rows here
    std::vector<int> blackHoleRows;
    int columnInd = galaxies.size();
    for(auto l :galaxies){
        if(l.find('#') == std::string::npos){
            blackHoleRows.push_back(columnInd);
        }
        columnInd--;
    }

    std::vector<std::pair<int, int>> stars;
    int y = galaxies.size();
    for(auto l : galaxies){
        int length = l.length();
        for(int x = 0; x < length; x++){
            if(l.at(x) == '#'){
                stars.emplace_back(x,y);
            }
        }
        y--;
    }

    long long int sum = 0;
    while(!stars.empty()) {
        auto star1 = stars.back();
        for(auto star2 : stars){
            if(star1.first == star2.first && star1.second == star2.second){
                continue;
            }
            //if the path between the 2 points passes through dead space, add on a million
            long long int deadSpace = 0;
            for(auto row : blackHoleRows){
                if(std::max(star1.second, star2.second) > row && std::min(star1.second, star2.second) < row){
                    deadSpace += 999999;
                }
            }
            for(auto column : blackHoleColumns){
                if(std::max(star1.first, star2.first) > column && std::min(star1.first, star2.first) < column){
                    deadSpace += 999999;
                }
            }
            sum += std::abs(star2.first - star1.first) + std::abs(star2.second - star1.second) + deadSpace;
        }
        stars.pop_back();
    }

    std::cout << "total sum with dead space: " << sum << "\n";

}
