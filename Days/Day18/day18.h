#include <string>
#include <vector>
#ifndef ADVENT_DAY18_H
#define ADVENT_DAY18_H


struct plan;

class day18 {
public:
    void LAVA(std::string fp);
private:
    int floodfill();
    char map[1000][1000];
    long long int p2area(std::vector<plan> &plans);
};


#endif //ADVENT_DAY18_H
