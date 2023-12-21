#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "day12p1.h"


void day12p1::comboCount(std::string fp) {
    std::fstream data(fp);
    std::vector<std::pair<std::string, std::vector<int>>> hotSprings;
    do{
        std::string springs;
        std::string nums;
        data >> springs;
        data >> nums;

        std::istringstream numstream(nums);
        std::vector<int> numList;
        do{
            int num;
            numstream >> num;
            numstream.get();
            numList.push_back(num);
        }while(!numstream.eof());

        hotSprings.emplace_back(springs, numList);
    }while(!data.eof());

    int combos = 0;
    //for every line, get every possible combination and then check the validity of each
    for(auto spring : hotSprings){
        auto *currentCombos = new std::vector<std::string>;
        getCombos(spring.first, spring.second, *currentCombos);

        for(const auto& combo : *currentCombos){
            if(validityCheck(combo, spring.second)){
                combos++;
            }
        }
    }

    std::cout << "combination sum: " << combos;

}
//super brute force
//gets all the possible configurations of the string and adds them to a list
void day12p1::getCombos(std::string springs, std::vector<int> &nums, std::vector<std::string> &combos) {
    //find the first unknown spring
    unsigned long unknownLocation = springs.find('?');
    if(unknownLocation != std::string::npos){
        //substitute the first unknown for a '#'
        std::string positive = springs;
        positive.at(unknownLocation) = '#';
        getCombos(positive, nums, combos);

        //substitute the first unknown for a '.'
        std::string negative = springs;
        negative.at(unknownLocation) = '.';
        getCombos(negative, nums, combos);
    }
    else{
        //find the total number of '#' that should be in the string
        int totalSprings = 0;
        for(int num : nums){
            totalSprings += num;
        }
        //find the actual number of '#' in the string
        int octoCount = std::count(springs.begin(), springs.end(), '#');
        //if these 2 dont match, this possibility is invalid, so dont add it to the list
        if(octoCount == totalSprings){
            combos.push_back(springs);
        }
    }
}

//checks the validity of a possibility based on its list of numbers
bool day12p1::validityCheck(std::string springs, const std::vector<int> &nums) {
    std::string currentSeg = springs;
    for(int num : nums){
        //find the start of the first group
        std::string check = currentSeg.substr(currentSeg.find('#'));
        // isolate the group
        check = check.substr(check.find('#'), check.find('.'));
        // ensure that the group matches the number
        if(std::count(check.begin(), check.end(), '#') != num){
            return false;
        }
        // advance to the next group
        currentSeg = currentSeg.substr(currentSeg.find('#') + num);
    }
    return true;
}