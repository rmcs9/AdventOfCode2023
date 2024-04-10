#include "day12p2.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>


void day12p2::comboUnfold(std::string fp) {
    std::fstream data(fp);
    std::vector<std::pair<std::string, std::vector<int>>> hotSprings;
    do {
        std::string springs;
        std::string nums;
        data >> springs;
        data >> nums;

        std::string unfoldedSprings = springs;
        std::string unfoldedNums = nums;
        //add 5x everything to the input
        for (int i = 0; i < 4; i++) {
            unfoldedSprings.append("?" + springs);
            unfoldedNums.append("," + nums);
        }
        std::istringstream numstream(unfoldedNums);
        std::vector<int> numList;
        do {
            int num;
            numstream >> num;
            numstream.get();
            numList.push_back(num);
        } while (!numstream.eof());

        hotSprings.emplace_back(unfoldedSprings, numList);
    } while (!data.eof());

    long long int combos = 0;
    for (auto spring: hotSprings) {
        std::unordered_map<std::string, long long int> dict;
        combos += getPossibilities(spring.first, spring.second, dict);
    }

    std::cout << "unfolded combos: " << combos;
}

//part 1's more rough brute force wasn't going to work in this case unfortunately
// P.S thank you reddit
long long int day12p2::getPossibilities(std::string springs, std::vector<int> nums,
                                        std::unordered_map<std::string, long long int> &springsDictionary) {
    long long int combos = 0;
    if (springs.empty()) {
        //if there is no more string and no more nums
        //the string is valid
        if (nums.empty()) {
            return 1;
        }
        return 0;
    }
    if (nums.empty()) {
        //if there is no more nums and there is no more #'s
        //the string is valid
        if (springs.find('#') == std::string::npos) {
            return 1;
        }
        return 0;
    }
    std::string numString;
    for (int num: nums) {
        numString += std::to_string(num) + ",";
    }
    //see if the sub-problem has been solved before solving again
    if (springsDictionary.find(springs + " " + numString) != springsDictionary.end()) {
        return springsDictionary[springs + " " + numString];
    }

    //if entering on a period, just absorb the period and dive onto the next char
    if (springs.at(0) == '.') {
        combos += getPossibilities(springs.substr(1), nums, springsDictionary);
    }
    //if the first char is unknown, branch states
    else if (springs.at(0) == '?') {
        std::string positive = springs;
        positive.at(0) = '#';

        std::string negative = springs;
        negative.at(0) = '.';

        combos += getPossibilities(positive, nums, springsDictionary) +
                  getPossibilities(negative, nums, springsDictionary);
    }
    //# case
    else {
        //if the current string can hold the next chunk of #'s
        if( nums[0] <= springs.length()
        // and there are no periods in the space where the chunk is supposed to go
        &&  std::count(springs.begin(), springs.begin() + nums[0], '.') == 0
        //and the length of the string is the same length as the next chunk
        // OR the character right AFTER the chunk is not a broken spring
        &&  (springs.length() == nums[0] || springs.at(nums[0]) != '#'))
        {
            //hold the length of the current chunk
            int num = nums[0];
            //remove the current chunk from the list
            nums.erase(nums.begin());
            //if there is more string left after this chunk
            if (springs.length() > num) {
                //absorb the chunk and the '.' after the chunk
                springs = springs.substr(num + 1);
            } else {
                // else absorb the chunk
                springs = springs.substr(num);
            }
            return getPossibilities(springs, nums, springsDictionary);
        }
        // if the above conditions fail, this possibility is invalid
        return 0;
    }

    //add the current solution to the map of known solutions
    if (springsDictionary.find(springs + " " + numString) == springsDictionary.end()) {
        springsDictionary[springs + " " + numString] = combos;
    }
    return combos;
}
