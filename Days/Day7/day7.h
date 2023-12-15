#include <string>
#ifndef ADVENT_DAY7_H
#define ADVENT_DAY7_H


class day7 {
public:
    int totalWinnings(std::string fp);
    int totalWinningsWildcards(std::string fp);
private:
    int getWildcards(std::string cards);
    bool is5OfKind(std::string cards);
    bool is4OfKind(std::string cards);
    bool isFullHouse(std::string cards);
    bool is3ofKind(std::string cards);
    bool is2Pair(std::string cards);
    bool is1Pair(std::string cards);
};


#endif //ADVENT_DAY7_H
