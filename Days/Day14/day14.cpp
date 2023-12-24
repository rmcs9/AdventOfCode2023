#include <string>
#include <fstream>
#include <iostream>
#include "day14.h"


void day14::totalLoad(std::string fp) {
    std::fstream data(fp);

    std::vector<std::string> map;
    do {
        std::string line;
        data >> line;
        map.push_back(line);
    } while (!data.eof());

    //part 1
    std::vector<std::string> p1map = map;
    rollNorth(p1map);
    int sum = calculateLoad(p1map);
    std::cout << "load sum: " << sum << '\n';

    //part 2
    std::vector<std::string> p2map = map;
    int cycleStart = 0, cycleLength = 0;
    for (int i = 0; i < 1000000000; i++) {
        spinCycle(p2map);
        std::string cycleString = vecToString(p2map);
        // eventually when calculating the spins, they will become cyclical
        // so as soon as you see a cycle that has been repeated
        // you can determine where the cycle started and how many spincycles
        // it took to get back to the same cycle.
        // with this information you can skip a substantial amount of iterations
        if(cycleMemo.find(cycleString) != cycleMemo.end()){
            cycleStart = cycleMemo.find(cycleString)->second;
            cycleLength = i - cycleStart;
            break;
        }
        cycleMemo[cycleString] = i;
    }

    // the amount of cycles needed to get to the end result can be calculated by
    // doing the initial amount of spin cycles to reach the start of the cycle (cycleStart +)
    // then doing the remaining remaining amount of cycles after you break out of the cycle
    // (1000000000 - cycleStart) % cycleLength
    int iterations = cycleStart + (1000000000 - cycleStart) % cycleLength;
    for(int i = 0; i < iterations; i++){
        spinCycle(map);
    }

    int sumP2 = calculateLoad(map);
    std::cout << "p2 load sum: " << sumP2;
}


void day14::spinCycle(std::vector<std::string> &map) {
    std::string origString = vecToString(map);
    if (memo.find(origString) != memo.end()) {
        map = memo.find(origString)->second;
    } else {
        rollNorth(map);
        rollWest(map);
        rollSouth(map);
        rollEast(map);
        memo[origString] = map;
    }
}

void day14::rollNorth(std::vector<std::string> &map) {
    for (int col = 0; col < map[0].length(); col++) {
        int Ocount = 0;
        int rowHolder = 0;
        for (int row = 0; row < map.size(); row++) {
            if (map[row].at(col) == 'O') {
                Ocount++;
                map[row].at(col) = '.';
            } else if (map[row].at(col) == '#') {
                for (int i = rowHolder, j = 0; j < Ocount; i++, j++) {
                    map[i].at(col) = 'O';
                }
                rowHolder = row + 1;
                Ocount = 0;
            }
        }
        if (Ocount != 0) {
            for (int i = rowHolder, j = 0; j < Ocount; i++, j++) {
                map[i].at(col) = 'O';
            }
        }
    }
}

void day14::rollWest(std::vector<std::string> &map) {
    for (int row = 0; row < map.size(); row++) {
        int oCount = 0;
        int colHolder = 0;
        for (int col = 0; col < map[row].length(); col++) {
            if (map[row].at(col) == 'O') {
                oCount++;
                map[row].at(col) = '.';
            } else if (map[row].at(col) == '#') {
                for (int i = colHolder, j = 0; j < oCount; i++, j++) {
                    map[row].at(i) = 'O';
                }
                colHolder = col + 1;
                oCount = 0;
            }
        }
        if (oCount != 0) {
            for (int i = colHolder, j = 0; j < oCount; i++, j++) {
                map[row].at(i) = 'O';
            }
        }
    }
}

void day14::rollSouth(std::vector<std::string> &map) {
    std::reverse(map.begin(), map.end());
    rollNorth(map);
    std::reverse(map.begin(), map.end());
}

void day14::rollEast(std::vector<std::string> &map) {
    for (auto &row: map) {
        std::reverse(row.begin(), row.end());
    }
    rollWest(map);
    for (auto &row: map) {
        std::reverse(row.begin(), row.end());
    }
}

int day14::calculateLoad(std::vector<std::string> &map) {
    int sum = 0;
    int rowVal = map.size();
    for (auto &row: map) {
        sum += rowVal * std::count(row.begin(), row.end(), 'O');
        rowVal--;
    }
    return sum;
}

std::string day14::vecToString(std::vector<std::string> &map) {
    std::string s;
    for (auto row: map) {
        s += row + '\n';
    }
    return s;
}