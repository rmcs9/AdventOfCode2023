#include <fstream>
#include <iostream>
#include "day16.h"

void day16::energized(std::string fp) {
    std::fstream data(fp);
    do{
        std::string line;
        data >> line;
        map.push_back(line);
    } while(!data.eof());

    untouchableMap = map;

    //part 1
    beam('R', 0, 0);
    std::cout << "energized tiles: " << energyTiles << '\n';
    reset();

    //part 2
    int bigEnergy = 0;
    //top
    for(int i = 0; i < map[0].length(); i++){
        beam('D', i, 0);
        bigEnergy = energyTiles > bigEnergy ? energyTiles : bigEnergy;
        reset();
    }
    //left side
    for(int i = 0; i < map.size(); i++){
        beam('R', 0, i);
        bigEnergy = energyTiles > bigEnergy ? energyTiles : bigEnergy;
        reset();
    }
    //bottom
    for(int i = 0; i < map[map.size() - 1].length(); i++){
        beam('U', i, map.size() - 1);
        bigEnergy = energyTiles > bigEnergy ? energyTiles : bigEnergy;
        reset();
    }
    //right side
    for(int i = 0; i < map.size(); i++){
        beam('L', map[i].length() - 1, i);
        bigEnergy = energyTiles > bigEnergy ? energyTiles : bigEnergy;
        reset();
    }
    std::cout << "largest amount of energized tiles: " << bigEnergy;
}


void day16::beam(char direction, int x, int y) {
    if(x > map[0].length() || y > map.size()){
        return;
    }

    while(x < map[y].length() && y < map.size()){
        char orig = map[y].at(x);
        std::string key = std::to_string(x) + " " + std::to_string(y);
        if(map[y].at(x) == '#'){
            if(splitters[key] == '-'){
                if(direction == 'U' || direction == 'D'){
                    return;
                }
                orig = '-';
            }
            else{
                if(direction == 'R' || direction == 'L'){
                    return;
                }
                orig = '|';
            }
        }

        if(beamedTiles.find(key) == beamedTiles.end()){
            beamedTiles[key] = true;
            energyTiles++;
        }

        switch(orig){
            case '.': {
                if (direction == 'U' || direction == 'D') {
                    y = direction == 'U' ? y - 1 : y + 1;
                } else {
                    x = direction == 'R' ? x + 1 : x - 1;
                }
                break;
            }
            case '\\': {
                if(direction == 'U' || direction == 'D'){
                    x = direction == 'U' ? x - 1 : x + 1;
                    direction = direction == 'U' ? 'L' : 'R';
                }
                else{
                    y = direction == 'R' ? y + 1 : y - 1;
                    direction = direction == 'R' ? 'D' : 'U';
                }
                break;
            }
            case '/': {
                if(direction == 'U' || direction == 'D'){
                    x = direction == 'U' ? x + 1 : x - 1;
                    direction = direction == 'U' ? 'R' : 'L';
                }
                else{
                    y = direction == 'R' ? y - 1 : y + 1;
                    direction = direction == 'R' ? 'U' : 'D';
                }
                break;
            }
            case '-': {
                if(direction == 'U' || direction == 'D'){
                    splitters[key] = '-';
                    map[y].at(x) = '#';
                    beam('L', x - 1, y);
                    x = x + 1;
                    direction = 'R';
                }
                else{
                    x = direction == 'R' ? x + 1 : x - 1;
                }
                break;
            }
            case '|': {
                if(direction == 'U' || direction == 'D'){
                    y = direction == 'U' ? y - 1 : y + 1;
                }
                else{
                    splitters[key] = '|';
                    map[y].at(x) = '#';
                    beam('U', x, y - 1);
                    y = y + 1;
                    direction = 'D';
                }
                break;
            }
        }
    }
}