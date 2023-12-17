#include <string>
#ifndef ADVENT_DAY10_H
#define ADVENT_DAY10_H


class day10 {
public:
    void loopSteps(std::string fp);
    void findNest(std::string fp);
private:
    static char findStartDirection(char n, char s, char e, char w);
    void mapMove(int &first, int &second, char &direct, char current);
};


#endif //ADVENT_DAY10_H
