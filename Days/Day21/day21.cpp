#include "day21.h"
#include <fstream>
#include <iostream>
#include <queue>

std::pair<int, int> directions[] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1},
};	

void day21::steps(std::string fp){
	std::fstream data(fp);
 	std::pair<int, int> start;
	int row = 0;
	bool sfound = false;
	do{
		std::string line;
		data >> line;
		if(!sfound){
			for(int col = 0; col < line.length(); col++){
				if(line.at(col) == 'S'){
					// coordQ.emplace(row, col);
					sfound = true;
					start = std::make_pair(row, col);
				}
			}
		}
		if(!line.empty()){
			map.push_back(line);
		}
		row++;
	} while(!data.eof());

	coordQ.push(start);
	for(int i = 0; i < 64; i++){
		int size = coordQ.size();
		std::unordered_set<std::string> mappings;
		for(int j = 0; j < size; j++){
	 		auto current = coordQ.front();
	 		coordQ.pop();
	 		expand(current.first, current.second, mappings);
	 	}
		mappings.clear();
	}
	std::cout << "p1 total: " << coordQ.size() << "\n";
	coordQ = std::queue<std::pair<int, int>>();
	coordQ2 = std::queue<std::pair<int, int>>();

	long long int y0 = p2Solve(start, 65);
	coordQ = std::queue<std::pair<int, int>>();
	coordQ2 = std::queue<std::pair<int, int>>();
	std::cout << "y0: " << y0 << '\n';

	long long int y1 = p2Solve(start, 196);
	coordQ = std::queue<std::pair<int, int>>();
	coordQ2 = std::queue<std::pair<int, int>>();
	std::cout << "y1: " << y1 << '\n';

	long long int y2 = p2Solve(start, 327);
	coordQ = std::queue<std::pair<int, int>>();
	coordQ2 = std::queue<std::pair<int, int>>();
	std::cout << "y2: " << y2 << '\n';

	long long int a = (y0 - 2 * y1 + y2) / 2;
	std::cout << "a: " << a << '\n';
	long long int b = (-3 * y0 + 4 * y1 - y2) / 2;
	std::cout << "b: " << b << '\n';
	long long int c = y0;
	std::cout << "c: " << c << '\n';

	long long int x = (26501365 - 65) / 131;
	std::cout << "x: " << x << '\n';

	long long int p2steps = (a * (x * x)) + (b * x) + c;

	std::cout << "part 2: " << p2steps << std::endl;
}


long long int day21::p2Solve(std::pair<int, int> start, int n){

	coordQ.push(start);
	for(int i = 0; i < n; i++){
		std::unordered_set<std::string> mappings;
		while(!coordQ.empty()){
			auto current = coordQ.front();
			coordQ.pop();
			expandp2(current.first, current.second, mappings);
		}
		coordQ.swap(coordQ2);
		mappings.clear();
	}

	return coordQ.size();

}

void day21::expand(int row, int col, std::unordered_set<std::string> &mappings){
	for(auto d : directions){
		if(row + d.first < map.size() && row + d.first >= 0 
			&& col + d.second < map[col].length() && col + d.second >= 0){
			if(map[row + d.first].at(col + d.second) != '#'){
				std::string key = std::to_string(row + d.first) + " " + std::to_string(col + d.second);
				if(!mappings.count(key)){
					coordQ.emplace(row + d.first, col + d.second);
					mappings.insert(key);
				}
			}
		}
	}
}


void day21::expandp2(int row, int col, std::unordered_set<std::string> &mappings){
	for(auto d : directions){
		std::string key = std::to_string(row + d.first) + " " + std::to_string(col + d.second);
		if(mappings.count(key) != 1){
			std::pair<int, int> remap = remapCoords(row + d.first, col + d.second);	
			try{
				if(map[remap.first].at(remap.second) != '#'){
					coordQ2.emplace(row + d.first, col + d.second);
					mappings.insert(key);
				}
			}
			catch(...){
				std::cout << "error on coords: " << remap.first << " " << remap.second << '\n';
				std::cout << "rows: " << map.size() << " cols: " << map[0].length() << '\n';
				std::exit(0);
			}

		}
	}
}


std::pair<int, int> day21::remapCoords(int row, int col){
	int newRow = row % (int) map.size();
	int newCol = col % (int) map[0].length();

	newRow = newRow < 0 ? newRow + map.size() : newRow;
	newCol = newCol < 0 ? newCol + map[0].length() : newCol;

	return std::make_pair(newRow, newCol);
}

