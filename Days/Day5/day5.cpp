using namespace std;

#include "day5.h"
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>


struct row {
    unsigned int source;
    unsigned int dest;
    unsigned int range;
};

unsigned int day5::lowestLocation(std::string fp) {
    fstream data(fp);
    int linecount = 0;
    string seedline;
    getline(data, seedline);
    linecount++;

    vector<unsigned int> *seeds = new vector<unsigned int>;

    string::const_iterator i = seedline.cbegin();
    //dispose of "seeds: "
    while (isdigit(*i) == 0) {
        i++;
    }
    //collect seeds
    char *num = new char[10];
    while (i != seedline.cend()) {
        if (isdigit(*i)) {
            int k = 0;
            while (*i != ' ') {
                if (i == seedline.end()) {
                    break;
                }
                num[k] = *i;
                i++;
                k++;
            }
            unsigned int seednum = stoul(num);
            seeds->push_back(seednum);
            num = new char[10];

            if (i == seedline.cend()) {
                break;
            } else {
                i++;
            }
        }
    }
    free(num);

    auto rows = new vector<vector<struct row>>();

    string rowLine;
    getline(data, rowLine);
    linecount++;
    do {
        //"___ to ___" line
        getline(data, rowLine);
        linecount++;

        getline(data, rowLine);
        linecount++;
        auto segVec = new vector<struct row>();
        do {
            istringstream stream(rowLine);
            unsigned int destination;
            stream >> destination;
            unsigned int source;
            stream >> source;
            unsigned int range;
            stream >> range;

            auto currentRow = new struct row();

            currentRow->dest = destination;
            currentRow->source = source;
            currentRow->range = range;


            segVec->push_back(*currentRow);
            if (!data.eof()) {
                getline(data, rowLine);
                linecount++;
            } else {
                break;
            }
        } while (rowLine != "");
        rows->push_back(*segVec);
    } while (!data.eof());

    for (auto seed = seeds->begin(); seed != seeds->end(); seed++) {
        for (auto seg = rows->begin(); seg != rows->end(); seg++) {
            for (auto row = seg->begin(); row != seg->end(); row++) {
                if (*seed > row->source && *seed < row->source + row->range) {
                    *seed += row->dest - row->source;
                    break;
                }
            }
        }
    }

    return *min_element(seeds->begin(), seeds->end());
}

struct seedAndRange {
    unsigned int start;
    unsigned int range;
};

/*
 * I apologize for this portion being kinda messy. I kinda just hacked my way through this one
 * and did not make a generalized solution. more just modified things for my specific data set
 *
 * Ill explain along the way
 */
unsigned int day5::lowestLocationpt2BRUTEFORCE(std::string fp) {
    fstream data(fp);
    int linecount = 0;
    string seedline;
    getline(data, seedline);
    linecount++;

    vector<unsigned int> *seeds = new vector<unsigned int>;

    //these blocks just collect the seed numbers
    string::const_iterator i = seedline.cbegin();
    //dispose of "seeds: "
    while (isdigit(*i) == 0) {
        i++;
    }
    //collect seeds
    char *num = new char[10];
    while (i != seedline.cend()) {
        if (isdigit(*i)) {
            int k = 0;
            while (*i != ' ') {
                if (i == seedline.end()) {
                    break;
                }
                num[k] = *i;
                i++;
                k++;
            }
            unsigned int seednum = stoul(num);
            seeds->push_back(seednum);
            num = new char[10];

            if (i == seedline.cend()) {
                break;
            } else {
                i++;
            }
        }
    }
    free(num);

    vector<struct seedAndRange> *ranges = new vector<struct seedAndRange>();
    //this just assembles the seed start and seed ranges into a list of structs
    for (auto i = seeds->begin(); i != seeds->end(); i++) {
        struct seedAndRange *current = new struct seedAndRange();
        current->start = *i;
        i++;
        current->range = *i;
        ranges->push_back(*current);
    }

    auto rows = new vector<vector<struct row>>();

    //this assembles all the almanac info into a list of lists of rows.
    //each row containing the source, destination and range
    string rowLine;
    getline(data, rowLine);
    linecount++;
    do {
        //"___ to ___" line
        getline(data, rowLine);
        linecount++;

        getline(data, rowLine);
        linecount++;
        auto segVec = new vector<struct row>();
        do {
            istringstream stream(rowLine);
            unsigned int destination;
            stream >> destination;
            unsigned int source;
            stream >> source;
            unsigned int range;
            stream >> range;

            auto currentRow = new struct row();

            currentRow->dest = destination;
            currentRow->source = source;
            currentRow->range = range;


            segVec->push_back(*currentRow);
            if (!data.eof()) {
                getline(data, rowLine);
                linecount++;
            } else {
                break;
            }
        } while (rowLine != "");
        rows->push_back(*segVec);
    } while (!data.eof());

    /**
     * My initial idea for a part 2 solution was to start at the lowest possible location value and traverse up
     * the locations until i found a location value that fit into one of the seed ranges. This didnt work tho.
     * I think this is because I would have to check the lowest values at every transfer level, and then if that
     * value matched one of the seed ranges, make sure the value doesnt change as it traverses down the almanac.
     *
     * for example if i find a low light value, i need to make sure that when light->temp doesnt change that value,
     * as well as temp->light doesnt change that value and so on. This becomes increasingly difficult as u move up the
     * almanac.
     *
     * due to the unclearness of this solution, i decided to take a more brute force approach that moved top to bottom
     * or seed to location, rather than location to seed.
     */
//
//    vector <row> locations = rows->at(6);
//    sort(locations.begin(), locations.end(), [](const row& a, const row& b) {
//        return a.dest < b.dest;
//    });
//
//    reverse(rows->begin(), rows->end());
//   for(auto locrow = locations.begin(); locrow != locations.end(); locrow++){
//       for(unsigned int counter = locrow->dest; counter < (locrow->dest + locrow->range); counter++){
//           unsigned int loc = counter;
////todo right now you are only getting the smallest translated location
////todo try getting the smallest value translated at each step and take the smallest of that whole collection?
//           for(auto seg = rows->begin(); seg != rows->end(); seg++){
//               for(auto row = seg->begin(); row != seg->end(); row++){
//                   unsigned int previousval = loc;
//                   if(loc >= row->dest && loc <= row->dest + row->range){
//                       loc += row->source - row->dest;
//                       cout << "change from " << previousval << " to " << loc << '\n';
//                       break;
//                   }
//                    cout << "no change\n";
//               }
//           }
//
//           for(auto seed = ranges->begin(); seed != ranges->end(); seed++){
//               if(loc >= seed->start && loc <= seed->start + seed->range){
//                   cout << loc << " within the range of " << seed->start << " and " << seed->start + seed->range << '\n';
//                   return counter;
//               }
//           }
//           cout << "location " << counter << "/" << locrow->dest + locrow->range;
//       }
//   }


/**
 * with this brute force approach, obviously you could check literally every seed value but that would take an absurd amount of time
 * instead you can just check a smaller subset of the seeds in a given interval and then find the smallest one of those.
 *
 * the result here will be within the range of one of your seed sets.
 */
//    vector<unsigned int> *locations = new vector<unsigned int>();
//
//    for (vector<struct seedAndRange>::iterator seed = ranges->begin(); seed != ranges->end(); seed++) {
//        unsigned int start = seed->start;
//        unsigned int range = seed->range;
//        for (unsigned int counter = start; counter < (start + range); counter += 10000) {
//            unsigned int seedInRange = counter;
//
//
//            for (auto seg = rows->begin(); seg != rows->end(); seg++) {
//                for (auto row = seg->begin(); row != seg->end(); row++) {
//                    if (seedInRange > row->source && seedInRange < (row->source + row->range)) {
//                        seedInRange += row->dest - row->source;
//                        break;
//                    }
//                }
//            }

//            locations->push_back(seedInRange);
////                location of smallest seed:
//            if(seedInRange == 17729743){
////                smallest seed: 4002148012 == counter
//               cout << "original seed: " << counter << '\n';
//            }
//        }
//    }


    //17729743
//    return *min_element(locations->begin(), locations->end());

/**
 * now that i obtained the smallest seed value from the above code block, I just iterate over the seed set
 * that that seed was a member of, and find the smallest location in that seed set
 */
    unsigned int minSeed = std::numeric_limits<unsigned int>::max();
    for(auto seed = ranges->begin(); seed != ranges->end(); seed++){
       unsigned int start = seed->start;
       unsigned int end = seed->start + seed->range;
       if(4002148012 > start && 4002148012 < end){
           unsigned int seednumber = start;
           for (unsigned int counter = start; counter < end; counter += 1) {
               unsigned int seedInRange = counter;


               for (auto seg = rows->begin(); seg != rows->end(); seg++) {
                   for (auto row = seg->begin(); row != seg->end(); row++) {
                       if (seedInRange > row->source && seedInRange < (row->source + row->range)) {
                           seedInRange += row->dest - row->source;
                           break;
                       }
                   }
               }
               cout << "seed " << seednumber << "/" << end << "\n";
               if(seedInRange < minSeed){
                   minSeed = seedInRange;
               }
               seednumber++;
           }

           break;
       }
    }

    return minSeed;
}