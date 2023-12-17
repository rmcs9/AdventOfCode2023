#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include "day10.h"


void day10::loopSteps(std::string fp) {
    std::fstream data(fp);

    std::string line;
    std::vector<std::string> pipes;

    do {
        getline(data, line);
        pipes.push_back(line);
    } while (!data.eof());
    data.close();

    std::pair<int, int> current;
    int piperow = 0;
    for (auto row: pipes) {
        int loc = row.find('S');
        if (loc != std::string::npos) {
            current = std::make_pair(piperow, loc);
        } else {
            piperow++;
        }
    }

    int steps = 0;
    char previousDirection = findStartDirection(
            pipes[current.first - 1].at(current.second),
            pipes[current.first + 1].at(current.second),
            pipes[current.first].at(current.second + 1),
            pipes[current.first].at(current.second - 1));

    switch(previousDirection){
        case 'N':
            current.first -= 1;
            break;
        case 'S':
            current.first += 1;
            break;
        case 'E':
            current.second += 1;
            break;
        case 'W':
            current.second -= 1;
            break;
    }

    do {
        mapMove(current.first, current.second, previousDirection, pipes[current.first].at(current.second));
        steps++;
    } while (pipes[current.first].at(current.second) != 'S');

    std::cout << "farthest away: " << (steps / 2) + 1 << std::endl;
}

void day10::findNest(std::string fp) {
    std::fstream data(fp);

    std::string line;
    std::vector<std::string> pipes;

    do {
        getline(data, line);
        pipes.push_back(line);
    } while (!data.eof());
    data.close();

    std::pair<int, int> current;
    int piperow = 0;
    for (auto row: pipes) {
        int loc = row.find('S');
        if (loc != std::string::npos) {
            current = std::make_pair(piperow, loc);
        } else {
            piperow++;
        }
    }

    int steps = 0;
    char previousDirection = findStartDirection(
            pipes[current.first - 1].at(current.second),
            pipes[current.first + 1].at(current.second),
            pipes[current.first].at(current.second + 1),
            pipes[current.first].at(current.second - 1));

    switch(previousDirection){
        case 'N':
            current.first -= 1;
            break;
        case 'S':
            current.first += 1;
            break;
        case 'E':
            current.second += 1;
            break;
        case 'W':
            current.second -= 1;
            break;
    }

//// CREATED pathMap.txt TO VISUALIZE THE PATH. DIDNT REALLY HELP TOO MUCH
//    do {
//        int prevFirst = current.first, prevSecond = current.second;
//        mapMove(current.first, current.second, previousDirection, pipes[current.first].at(current.second));
//        pipes[prevFirst].at(prevSecond) = 'X';
//        steps++;
//    } while (pipes[current.first].at(current.second) != 'S');
//
//    std::ofstream map("../Days/Day10/pathMap.txt");
//    for(auto line : pipes){
//        map << line + '\n';
//    }
//    map.close();

    /**
     * from u/hi_im_new_to_this:
     *
     * lets say you have an enclosed shape, and you want to color every pixel inside of it.
     * How do you know if a given pixel is inside the shape or not? Well, it turns out:
     * if you shoot a ray in any direction from the pixel and it crosses the boundary an odd number of times, it's inside.
     * if it crosses an even number of times, it's outside.
     * Works for all enclosed shapes, even self-intersecting and non-convex ones.
     *
     * ENDQUOTE
     *
     * say you had a square with point *:
     * if you shot a ray in any direction from * and cross a boundary
     * an odd number of times, you are inside the shape:
     *      ---------------
     *      |             |
     *      |      *----->X
     *      |             |
     *      |             |
     *      ---------------
     *
     *  now consider a different point *:
     *
     *       ---------------
     *       |             |
     *  *----X------------>X
     *       |             |
     *       |             |
     *       ---------------
     *
     * in this case, the ray crosses the boundary an even number of times,
     * so * is not inside the shape.
     */

    //map to hold all of the points along the pipe loop
    std::unordered_map<std::string, bool> pathPoints;
    do{
        //previous path coordinates
        int prevFirst = current.first, prevSecond = current.second;
        //advance to the next pipe in the path
        mapMove(current.first, current.second, previousDirection, pipes[current.first].at(current.second));
        //create coordinate string for map
        std::string mapString = std::to_string(prevFirst) + " " + std::to_string(prevSecond);
        pathPoints[mapString] = true;

    } while(pipes[current.first].at(current.second) != 'S');

    int pointsInside = 0;
    //for every x and y find whether yx is inside the loop
    for(int y = 0; y < pipes.size(); y++){
        auto line = pipes[y];
        for(int x = 0; x < line.length(); x++){
            std::string mapPoint = std::to_string(y) + " " + std::to_string(x);

            bool inMap = true;
            try{pathPoints.at(mapPoint);}
            catch(...){inMap = false;}
            //if y,x is in the path, skip it
            if(inMap){
                continue;
            }
            //copy the coordinates into the starting ray coordinates
            int yRay = y, xRay = x;
            int pathCrosses = 0;
            //while the ray is still within the maps bounds
            while(yRay < pipes.size() && xRay < line.length()){
                char pipeAtPoint = pipes[yRay].at(xRay);

                mapPoint = std::to_string(yRay) + " " + std::to_string(xRay);

                inMap = true;
                try{pathPoints.at(mapPoint);}
                catch(...){inMap = false;}
                //if the ray hits a point that is on the loop, and is not a corner.
                //increase the times the ray has crossed the loop
                if(inMap && pipeAtPoint != 'L' && pipeAtPoint != '7'){
                    pathCrosses++;
                }
                //advance the ray.
                // these rays are traveling towards the bottom right corner of the map
                yRay++;
                xRay++;
            }
            //if the times the ray crossed the path are odd,
            //the point must be inside
            if(pathCrosses % 2 == 1){
                pointsInside++;
            }
        }
    }

    std::cout << "points inside path: " << pointsInside;

}

void day10::mapMove(int &first, int &second, char &direct, char current) {
    switch(current){
        case '|':
            if(direct == 'N'){
                first -= 1;
            }
            else if(direct == 'S'){
                first += 1;
            }
            break;
        case '-':
            if(direct == 'E'){
                second += 1;
            }
            else if(direct == 'W'){
                second -= 1;
            }
            break;
        case 'L':
            if(direct == 'S'){
                second += 1;
                direct = 'E';
            }
            else if(direct == 'W'){
                first -= 1;
                direct = 'N';
            }
            break;
        case 'J':
            if(direct == 'S'){
                second -= 1;
                direct = 'W';
            }
            else if(direct == 'E'){
                first -= 1;
                direct = 'N';
            }
            break;
        case '7':
            if(direct == 'N'){
                second -= 1;
                direct = 'W';
            }
            else if(direct == 'E'){
                first += 1;
                direct = 'S';
            }
            break;
        case 'F':
            if(direct == 'N'){
                second += 1;
                direct = 'E';
            }
            else if(direct == 'W'){
                first += 1;
                direct = 'S';
            }
            break;
    }
}


char day10::findStartDirection(char n, char s, char e, char w){
    if(n == '|' || n == '7' || n == 'F'){
        return 'N';
    }
    else if(s == '|' || s == 'L' || s == 'J') {
        return 'S';
    }
    else if(e == '-' || e == 'J' || e == '7'){
        return 'E';
    }
    else if(w == '-' || w == 'F' || w == 'L'){
        return 'W';
    }
}


