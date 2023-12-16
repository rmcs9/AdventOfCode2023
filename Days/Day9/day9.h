#include <string>
#ifndef ADVENT_DAY9_H
#define ADVENT_DAY9_H


class day9 {
public:
    void extrapolate(std::string fp);
private:
    void getSubSequences(std::vector<std::vector<int>> &sequences);
    int getExtrapolatedValue(std::vector<std::vector<int>> sequences);
    int getReverseExtrapolatedValue(std::vector<std::vector<int>> sequences);
};


#endif //ADVENT_DAY9_H
