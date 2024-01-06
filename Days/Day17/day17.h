#include <string>
#include <list>
#include <iostream>
#ifndef ADVENT_DAY17_H
#define ADVENT_DAY17_H

struct direction;

class day17 {
public:
    void leastHeatLoss(std::string fp);
private:
   std::vector<std::vector<int>> map;
   int moddedDijkstras();
   int moddedDijkstrasP2();
   bool inGrid(int row, int col);
   int next4(std::pair<int, int> coords, const direction& direct);
};


#endif //ADVENT_DAY17_H