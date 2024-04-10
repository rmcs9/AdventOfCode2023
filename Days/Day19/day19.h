#include <string>
#include <unordered_map>
#include <list>
#ifndef ADVENT_DAY19_H
#define ADVENT_DAY19_H


class day19 {
public:
    void ratingnums(std::string fp);
private:
    std::list<std::unordered_map<char, int>> parts;
    std::unordered_map<std::string, std::string> workflows;
    std::string work(std::string tag, std::unordered_map<char, int> &part);
    long long int workp2(std::string tag, std::unordered_map<char, std::pair<int, int>> ranges);
};


#endif //ADVENT_DAY19_H
