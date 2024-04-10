#include <string>
#include <fstream>
#include <queue>
#include <numeric>
#include <unordered_map>
#include <memory>
#include "day8.h"

//objects representing a locations 2 pathways
class fork{
public:
    std::unique_ptr<std::string> left;
    std::unique_ptr<std::string> right;
    fork(std::string l, std::string r){
        left = std::make_unique<std::string>(l);
        right = std::make_unique<std::string>(r);
    }
};


int day8::steps(std::string fp){
    std::fstream data(fp);

    std::string directionsString;
    std::getline(data, directionsString);

    std::unordered_map<std::string, std::unique_ptr<fork>> locationToFork;

    std::string dataline;
    std::getline(data, dataline);
    //read all locations and forks into a hashmap from location->fork
    do{
        std::getline(data, dataline);
        std::string location = dataline.substr(0,3);
        std::string left = dataline.substr(7,3);
        std::string right = dataline.substr(12,3);
        //tried out some smart pointers today
        std::unique_ptr<fork> current = std::make_unique<fork>(left, right);

        locationToFork[location] = std::move(current);

    }while(!data.eof());
    data.close();
    //start at AAA and walk through the map until ZZZ is found
    int steps = 0;
    std::string currentLocation = "AAA";
    std::queue<char> directions;
    while(currentLocation != "ZZZ"){
        for(auto c : directionsString){
            directions.push(c);
        }
        while(!directions.empty()){
            char direction = directions.front();
            directions.pop();

            currentLocation = direction == 'L' ?
                    *(locationToFork[currentLocation].get()->left.get()) :
                    *(locationToFork[currentLocation].get()->right.get());
            steps++;
            if(currentLocation == "ZZZ"){
                break;
            }
        }
    }
    return steps;
}


long long int day8::ghostSteps(std::string fp){
    std::fstream data(fp);

    std::string directionsString;
    std::getline(data, directionsString);

    std::unordered_map<std::string, std::unique_ptr<fork>> locationToFork;

    std::vector<std::string> ghostStarts;

    std::string dataline;
    std::getline(data, dataline);
    //pretty much same as part 1.
    //read all locations->fork data
    do{
        std::getline(data, dataline);
        std::string location = dataline.substr(0,3);
        std::string left = dataline.substr(7,3);
        std::string right = dataline.substr(12,3);
        //this time if a location ends with A save it
        if(location.at(2) == 'A'){
            ghostStarts.push_back(location);
        }

        std::unique_ptr<fork> current = std::make_unique<fork>(left, right);

        locationToFork[location] = std::move(current);

    }while(!data.eof());
    data.close();
    //walk through all ghost locations (locations ending in A)
    //record the number of steps required to reach a location ending in Z
    std::vector<long long int> stepsToZ;
    std::queue<char> directions;
    for(auto &ghost : ghostStarts){
        long long int steps = 0;
        while(ghost.at(2) != 'Z'){
            for(auto c : directionsString){
                directions.push(c);
            }

            while(!directions.empty()){
                char direction = directions.front();
                directions.pop();

                ghost = direction == 'L' ?
                        *(locationToFork[ghost].get()->left.get()) :
                        *(locationToFork[ghost].get()->right.get());
                steps++;
                if(ghost.at(2) == 'Z'){
                    break;
                }
            }
        }
        stepsToZ.push_back(steps);
    }
    /**
     * because of the way this input data was set up, it takes N steps to get to Z and from Z takes another
     * N steps to get back to the same Z. because each ghost step path is cyclical, you can calculate the shortest
     * amount of steps to get all Z's by taking the LCM of all the ghostpath cycles.
     *
     * Shoutout reddit. :-)
     */
    long long int lcm = stepsToZ.front();
    for(auto zstep = stepsToZ.begin() + 1; zstep != stepsToZ.end(); zstep++){
        lcm = std::lcm(lcm , *zstep);
    }
    return lcm;
}
