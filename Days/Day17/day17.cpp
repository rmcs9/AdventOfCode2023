#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <utility>
#include "day17.h"

void day17::leastHeatLoss(std::string fp) {
    std::fstream data(fp);

    do {
        std::string line;
        data >> line;
        std::vector<int> row;
        for (char i: line) {
            row.push_back(i - '0');
        }
        map.push_back(row);
    } while (!data.eof());

    std::cout << "path: " << moddedDijkstras() << '\n';
    std::cout << "ultra path: " << moddedDijkstrasP2();
}


struct direction {
    //the vector movement for this specified direction
    std::pair<int, int> thisDirection;
    //indexes in the directions array where the opposite directions can be found
    std::vector<int> altDirections;
    //directional identifier
    char d;
};

const direction directions[] = {
        //north
        {
                {-1, 0},
                {1, 3},
                'N'
        },
        //east
        {
                {0,  1},
                {0, 2},
                'E'
        },
        //south
        {
                {1,  0},
                {1, 3},
                'S'
        },
        //west
        {
                {0,  -1},
                {0, 2},
                'W'
        }
};


struct block {
    //the heat loss value of this block
    int val = 0;
    //the amount of blocks that have been travelled in a straight line
    int momentum = 0;
    //the direction the block was traversed into
    direction direct;
    //the graph coordinates of this block
    std::pair<int, int> coords;

    block(int v, int m, direction d, std::pair<int, int> c) {
        val = v;
        momentum = m;
        direct = d;
        coords = c;
    }
};

//defines how blocks are sorted in the priority queues heap
struct heapSorter {
    bool operator()(block &left, block &right) {
        return left.val > right.val;
    }
};

bool day17::inGrid(const int row, const int col) {
    return row >= 0 && row < map.size() && col >= 0 && col < map[0].size();
}

int day17::moddedDijkstras() {
    std::unordered_map<std::string, int> explored;
    std::priority_queue<block, std::vector<block>, heapSorter> Q;
    //push 2 {0,0} blocks to travel south and east
    Q.emplace(0, 0, directions[1], std::make_pair(0, 0));
    Q.emplace(0, 0, directions[2], std::make_pair(0, 0));
    while (!Q.empty()) {
        //pop the block with the smallest heat loss
        block current = Q.top();
        Q.pop();
        //determine if this block has already been explored from the same parent
        std::string key = std::to_string(current.coords.first) +
                          " " + std::to_string(current.coords.second) +
                          " " + std::to_string(current.direct.d) +
                          " " + std::to_string(current.momentum);
        if (explored.find(key) != explored.end()) {
            continue;
        }
        explored.insert(std::make_pair(key, current.val));
        //if this block is the destination, return its value.
        //we can assume this heat loss value will be the smallest due to the use of priority queue.
        if (current.coords.first == map.size() - 1 && current.coords.second == map[0].size() - 1) {
            return current.val;
        }

        //explore this blocks alternate directions and push them into the queue.
        //since you are turning, momentum is reset to 0
        for (auto direct: current.direct.altDirections) {
            std::pair newCoords =
                    std::make_pair(current.coords.first + directions[direct].thisDirection.first,
                                   current.coords.second + directions[direct].thisDirection.second);
            if (inGrid(newCoords.first, newCoords.second)) {
                int newVal = current.val + map[newCoords.first][newCoords.second];
                Q.emplace(newVal, 0, directions[direct], newCoords);
            }
        }

        //if the blocks momentum is under 2, you can keep going straight
        if (current.momentum < 2) {
            std::pair<int, int> newCoords =
                    std::make_pair(current.coords.first + current.direct.thisDirection.first,
                                   current.coords.second + current.direct.thisDirection.second);
            if (inGrid(newCoords.first, newCoords.second)) {
                int newVal = current.val + map[newCoords.first][newCoords.second];
                Q.emplace(newVal, current.momentum + 1, current.direct, newCoords);
            }
        }
    }

    return 0;
}

//pretty much same procedure as part 1.
int day17::moddedDijkstrasP2() {
    std::unordered_map<std::string, int> explored;
    std::priority_queue<block, std::vector<block>, heapSorter> Q;
    Q.emplace(0, 0, directions[1], std::make_pair(0, 0));
    Q.emplace(0, 0, directions[2], std::make_pair(0, 0));
    while (!Q.empty()) {
        block current = Q.top();
        Q.pop();

        std::string key = std::to_string(current.coords.first) +
                          " " + std::to_string(current.coords.second) +
                          " " + std::to_string(current.direct.d) +
                          " " + std::to_string(current.momentum);
        if (explored.find(key) != explored.end()) {
            continue;
        }
        explored.insert(std::make_pair(key, current.val));

        if (current.coords.first == map.size() - 1 && current.coords.second == map[0].size() - 1) {
            return current.val;
        }

        //if you turn you have to travel in the turned direction for at least 4 blocks
        for (auto direct: current.direct.altDirections) {
            std::pair newCoords =
                    std::make_pair(current.coords.first + (directions[direct].thisDirection.first * 4),
                                   current.coords.second + (directions[direct].thisDirection.second * 4));
            if (inGrid(newCoords.first, newCoords.second)) {
                int newVal = current.val + next4(current.coords, directions[direct]);
                Q.emplace(newVal, 4, directions[direct], newCoords);
            }
        }
        //you can keep going straight as long as you haven't gone straight for 10 blocks
        if(current.momentum < 10) {
            std::pair<int, int> newCoords =
                    std::make_pair(current.coords.first + current.direct.thisDirection.first,
                                   current.coords.second + current.direct.thisDirection.second);
            if (inGrid(newCoords.first, newCoords.second)) {
                int newVal = current.val + map[newCoords.first][newCoords.second];
                Q.emplace(newVal, current.momentum + 1, current.direct, newCoords);
            }
        }
    }

    return 0;
}

//accumulates the heat loss for the next 4 blocks in a straight line
int day17::next4(std::pair<int, int> coords, const direction& direct) {
    int val = 0;
    for(int i = 0; i < 4; i++){
        coords.first += direct.thisDirection.first;
        coords.second += direct.thisDirection.second;
        val += map[coords.first][coords.second];
    }
    return val;
}
