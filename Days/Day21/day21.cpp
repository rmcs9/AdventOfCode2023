#include "day21.h"
#include <fstream>
#include <iostream>

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
					coordQ.emplace(row, col);
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

	std::cout << map.size() << " " << map[0].length() << '\n';
	for(auto &line : map){
		std::cout << line << '\n';
	}

	for(int i = 0; i < 64; i++){
		std::cout << "cycle: " << i << '\n';
		int size = coordQ.size();
		std::cout << "size: " << size << '\n';
		std::unordered_set<std::string> mappings;
		for(int j = 0; j < size; j++){
	 		auto current = coordQ.front();
	 		coordQ.pop();
	 		expand(current.first, current.second, mappings);
	 	}
		mappings.clear();
	}
	
	std::cout << "p1 total: " << coordQ.size() << "\n\n\n\n\n\n\n\n\n\n";

	while(!coordQ.empty()){
		coordQ.pop();
	}
	
	//part 2 super slow gonna come back and finish this later
	coordQ.emplace(start.first, start.second);
	for(int i = 0; i < 26501365; i++){
		std::cout << "cycle: " << i << '\n';

		long long int size = coordQ.size();
		std::cout << "size: " << size << '\n';

		std::unordered_set<std::string> mappings;
		for(long long int j = 0; j < size; j++){
			auto current = coordQ.front();
			// std::cout << current.first << " " << current.second << '\n';
			coordQ.pop();
			expandp2(current.first, current.second, mappings);
		}
		mappings.clear();
	}
	
	std::cout << "p2 total: " << coordQ.size() << std::endl;
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
		if(!mappings.count(key)){
			std::pair<int, int> remap = remapCoords(row + d.first, col + d.second);	
			try{
				if(map[remap.first].at(remap.second) != '#'){
					coordQ.emplace(row + d.first, col + d.second);
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
	if(row < map.size() && row >= 0 && col < map[0].length() && col >= 0){
		// std::cout << row << " " << col << '\n';
		return std::make_pair(row, col);
	}

	if(row < 0){
		row += map.size();
	}
	else if(row >= map.size()){
		row -= map.size();
	}

	if(col < 0){
		col += map[0].length();	
	}
	else if(col >= map[0].length()){
		col -= map[0].length();
	}

	return remapCoords(row, col);
}
