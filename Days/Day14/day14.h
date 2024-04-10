#include <string>
#include <unordered_map>
#ifndef ADVENT_DAY14_H
#define ADVENT_DAY14_H


class day14{
public:
    void totalLoad(std::string fp);
private:
    void rollNorth(std::vector<std::string> &map);
    void rollWest(std::vector<std::string> &map);
    void rollSouth(std::vector<std::string> &map);
    void rollEast(std::vector<std::string> &map);
    void spinCycle(std::vector<std::string> &map);
    int calculateLoad(std::vector<std::string> &map);
    std::string vecToString(std::vector<std::string> &map);
    std::unordered_map<std::string, std::vector<std::string>> memo;
    std::unordered_map<std::string, int> cycleMemo;
    void westToNorth(std::vector<std::string> &map);
    void eastToNorth(std::vector<std::string> &map);
};


#endif //ADVENT_DAY14_H
