#include <string>
#ifndef ADVENT_DAY12_H
#define ADVENT_DAY12_H


class day12p1 {
public:
    void comboCount(std::string fp);
private:
    void getCombos(std::string springs, std::vector<int> &nums, std::vector<std::string> &combos);
    bool validityCheck(std::string springs, const std::vector<int> &nums);
};


#endif //ADVENT_DAY12_H
