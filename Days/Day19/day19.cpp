#include "day19.h"
#include <fstream>
#include <iostream>

void day19::ratingnums(std::string fp) {
    std::fstream data(fp);
    std::string line;
    data >> line;

    //parse workflows
    while (line.at(0) != '{') {
        std::string tag = line.substr(0, line.find('{'));
        workflows[tag] = line.substr(line.find('{') + 1, line.length() - tag.length() - 2);
        data >> line;
    }

    //parse parts
    while (!data.eof()) {
        std::unordered_map<char, int> part;
        std::string remaining = line.substr(1, line.length() - 2);
        while (!remaining.empty()) {
            std::string current = remaining.substr(0, remaining.find(','));
            part[current.at(0)] = std::stoi(current.substr(2));
            remaining = remaining.find(',') == std::string::npos ? "" : remaining.substr(remaining.find(',') + 1);
        }
        parts.push_back(part);
        data >> line;
    }

    //p1
    int total = 0;
    for (auto &part: parts) {
        std::string worked = work("in", part);
        if (worked == "A") {
            for (auto val: part) {
                total += val.second;
            }
        }
    }
    std::cout << "p1 total: " << total << '\n';
	
    //p2
    std::unordered_map<char, std::pair<int, int>> ranges;
    ranges['x'] = std::make_pair(1, 4001);
    ranges['m'] = std::make_pair(1, 4001);
    ranges['a'] = std::make_pair(1, 4001);
    ranges['s'] = std::make_pair(1, 4001);
    std::cout << "p2 total: " << workp2("in", ranges) << std::endl;
}

std::string day19::work(std::string tag, std::unordered_map<char, int> &part) {
    //base case
    if (tag == "A" || tag == "R") {
        return tag;
    }
    std::string instructions = workflows[tag];
    //while there are more conditions...
    while (instructions.find(',') != std::string::npos) {
        //grab the current condition
        std::string current = instructions.substr(0, instructions.find(','));
        //determine its operation
        if (current.find('<') != std::string::npos) {
            //perform operation
            if (part[current.at(0)] <
                std::stoi(current.substr(current.find('<') + 1, current.find(':') - current.find('<')))) {
                //if condition is true, call on the conditions workflow tag
                return work(current.substr(current.find(':') + 1), part);
            }
        } else if (current.find('>') != std::string::npos) {
            if (part[current.at(0)] >
                std::stoi(current.substr(current.find('>') + 1, current.find(':') - current.find('>')))) {
                return work(current.substr(current.find(':') + 1), part);
            }
        }
        //if the above condition fails, move onto the next one
        instructions = instructions.substr(instructions.find(',') + 1);
    }
    //else case with no condition
    return work(instructions, part);
}

long long int day19::workp2(std::string tag, std::unordered_map<char, std::pair<int, int>> ranges) {
    //base case
    if (tag == "A") {
        //if the current ranges are accepted, multiply the possible ranges
        long long int total = 1;
        for (auto &range: ranges) {
            total *= (range.second.second - range.second.first);
        }
        return total;
    } else if (tag == "R") {
        return 0;
    }

    long long int total = 0;
    std::string instructions = workflows[tag];
    //while there are more conditions...
    while (instructions.find(',') != std::string::npos) {
        std::string current = instructions.substr(0, instructions.find(','));
        std::pair<int, int> lowerRange = ranges[current.at(0)], upperRange = ranges[current.at(0)];
        if (current.find('<') != std::string::npos) {
            int bound = std::stoi(current.substr(current.find('<') + 1, current.find(':') - current.find('<')));
            //split the current range into 2 ranges based on the bound given in the condition
            lowerRange.second = bound;
            upperRange.first = bound;
            //for less than operations, call again on the lower range
            ranges[current.at(0)] = lowerRange;
            total += workp2(current.substr(current.find(':') + 1), ranges);
            //continue the process for the rest of the conditions using the upper range
            ranges[current.at(0)] = upperRange;
        } else if (current.find('>') != std::string::npos) {
            int bound = std::stoi(current.substr(current.find('>') + 1, current.find(':') - current.find('>')));
            lowerRange.second = bound + 1;
            upperRange.first = bound + 1;
            //for greater than operations, call again on the upper range
            ranges[current.at(0)] = upperRange;
            total += workp2(current.substr(current.find(':') + 1), ranges);
            //use the lower range for the remaining conditions
            ranges[current.at(0)] = lowerRange;
        }
        instructions = instructions.substr(instructions.find(',') + 1);
    }
    total += workp2(instructions, ranges);
    return total;
}
