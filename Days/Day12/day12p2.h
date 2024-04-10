#include <string>
#include <unordered_map>
#include <vector>
#ifndef ADVENT_DAY12P2_H
#define ADVENT_DAY12P2_H


class day12p2 {
public:
    void comboUnfold(std::string fp);
private:
    long long int getPossibilities(std::string springs, std::vector<int> nums, std::unordered_map<std::string, long long int> &springsDictionary);
};


#endif //ADVENT_DAY12P2_H
