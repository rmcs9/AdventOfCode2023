#include <string>
#ifndef ADVENT_DAY4_H
#define ADVENT_DAY4_H


class day4 {
public:
   static int winningCards(std::string filepath);
   int winningCards2(std::string filepath);
   int winningCards2Helper(int index, int matches, int* mat);
};

#endif //ADVENT_DAY4_H
