#include <string>
#include <unordered_map>
#include <vector>
#ifndef ADVENT_DAY16_H
#define ADVENT_DAY16_H


class day16 {
public:
    void energized(std::string fp);
private:
    std::vector<std::string> map;
    std::vector<std::string> untouchableMap;
    int energyTiles = 0;
    void beam(char direction, int x, int y);
    std::unordered_map<std::string, bool> beamedTiles;
    std::unordered_map<std::string, char> splitters;
    void reset(){
        beamedTiles.clear();
        splitters.clear();
        energyTiles = 0;
        map = untouchableMap;
    }
};

#endif //ADVENT_DAY16_H
