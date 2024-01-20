#include <string>
#include <queue>
#include <unordered_set>

#ifndef ADVENT_DAY21_H
#define ADVENT_DAY21_H

class day21{
public:
	void steps(std::string fp);
private:
	std::queue<std::pair<int, int>> coordQ;
	std::vector<std::string> map;
	void expand(int row, int col, std::unordered_set<std::string> &mappings);
	void expandp2(int row, int col, std::unordered_set<std::string> &mappoings);
	std::pair<int, int> remapCoords(int row, int col);
};

#endif
