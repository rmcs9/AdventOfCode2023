#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include "day15.h"

/*
 * all of the standard library hashtable implementations
 * are all very vague about how they index keys
 *
 * so i decided that this would be a good time to experiment with some template stuff
 * and run a quick LinkedHashMap implementation that's very minimal and specific
 * to this situation
 */
template <typename f, typename s>
class LinkMap{
public:
    void insert(f key, s val){
        map[key] = val;
        if(std::find(linkOrder.begin(), linkOrder.end(), key) == linkOrder.end()){
            linkOrder.push_back(key);
        }
    }

    void erase(f key){
        if(std::find(linkOrder.begin(), linkOrder.end(), key) != linkOrder.end()
            && map.find(key) != map.end()){
            linkOrder.remove(key);
            map.erase(key);
        }
    }

    s val(f key){
        return map.at(key);
    }

    std::list<f> &links(){
        return linkOrder;
    }

private:
    std::unordered_map<f, s> map;
    std::list<f> linkOrder;
};

//part 1
void day15::hashSum(std::string fp) {
    std::fstream data(fp);

    std::string line;
    getline(data, line);

    int total = 0;
    int sequenceTotal = 0;
    for(char c : line){
        if(c != ','){
            sequenceTotal = ((sequenceTotal + c) * 17) % 256;
        }
        else{
            total += sequenceTotal;
            sequenceTotal = 0;
        }
    }
    total += sequenceTotal;

    std::cout << "hash sum: " << total;
}

//part 2
void day15::focusingPower(std::string fp) {
    std::fstream data(fp);

    std::string line;
    getline(data, line);
    std::istringstream codeStream(line);

    std::map<int, LinkMap<std::string, int>> HASHMAP;

    std::string current;
    while(getline(codeStream, current, ',')){
        int sequenceHash = 0;
        std::string sequence;
        for(char c : current){
            if(c == '='){
                HASHMAP[sequenceHash].insert(sequence, current.at(current.length() - 1) - '0');
            }
            else if(c == '-'){
                HASHMAP[sequenceHash].erase(sequence);
            }
            else{
                sequenceHash = ((sequenceHash + c) * 17) % 256;
                sequence += c;
            }
        }
    }

    int total = 0;
    for(auto &box : HASHMAP){
        auto i = box.second.links().begin();
        for(int lens = 0; lens < box.second.links().size(); lens++, i++){
            int lensTotal = (box.first + 1) * (lens + 1) * box.second.val(*i);
            total += lensTotal;
        }
    }

    std::cout << "focusing power: " << total;
}