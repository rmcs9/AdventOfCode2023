#include <array>
#include "day6.h"
#include <string>
#include <fstream>
#include <sstream>

/**
 * after the brute forcing i did for day 5, this one was a piece of cake.
 *
 * the solutions for parts 1 and 2 are pretty much the same thing.
 *
 *
 * I know there are def cooler
 * ways to solve this using clever math skills which i severely lack...
 *
 * however because the data sets for this day are so small, and given how far behind i am,
 * i opted to skip the math on this one and just checked all possible values of x
 *
 * where x = the number of seconds you hold down the button
 * and
 * y = the distance the boat travels in r = race time
 *
 * y = x * (r - x)
 *
 */



struct race{
    int time;
    int recordDistance;
};

int day6::marginOfError(std::string fp) {

    std::fstream data(fp);

    std::array<struct race, 4> races;

    std::string times;
    getline(data, times);
    std::string records;
    getline(data, records);

    times = times.substr(5);
    records = records.substr(9);

    std::istringstream timesStream(times);
    std::istringstream recordsStream(records);

    int c = 0;
    while(!timesStream.eof()){
        races[c] = *new struct race();
        timesStream >> races[c].time;
        recordsStream >> races[c].recordDistance;
        c++;
    }

    int totalMargin = 1;
    for(int i = 0; i < races.size(); i++){
        int raceWinners = 0;
        for(int x = 0; x < races[i].time; x++){
            int y = x * (races[i].time - x);
            if(y > races[i].recordDistance){
                raceWinners++;
            }
        }
        totalMargin *= raceWinners;
    }

    return totalMargin;
}

int day6::oneRace(std::string fp){
    std::fstream data(fp);

    std::string timeLine;
    getline(data, timeLine);
    std::string recordLine;
    getline(data, recordLine);

    std::istringstream timeStream(timeLine.substr(5));
    std::istringstream recordStream(recordLine.substr(9));

    std::string timestr;
    std::string recordstr;

    while(!timeStream.eof()){
        std::string t;
        timeStream >> t;
        std::string r;
        recordStream >> r;

        timestr += t;
        recordstr += r;
    }

    long long time = std::stoul(timestr);
    long long record = std::stoul(recordstr);

    int raceWinners = 0;
    for(long long int x = 0; x < time; x++){
        long long int y = x * (time - x);
        if(y > record){
            raceWinners++;
        }
    }

    return raceWinners;
}
