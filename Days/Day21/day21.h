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
	std::queue<std::pair<int, int>> coordQ2;
	std::vector<std::string> map;
	long long int p2Solve(std::pair<int, int> start, int n);
	void expand(int row, int col, std::unordered_set<std::string> &mappings);
	void expandp2(int row, int col, std::unordered_set<std::string> &mappings);
	std::pair<int, int> remapCoords(int row, int col);
};

#endif
