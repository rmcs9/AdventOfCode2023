#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include "day13.h"


void day13::symmetrySum(std::string fp) {
    std::fstream data(fp);

    std::vector<std::vector<std::string>> notes;
    do {
        std::vector<std::string> currentNote;
        std::string line;
        getline(data, line);
        while (!line.empty() && !data.eof()) {
            currentNote.push_back(line);
            getline(data, line);
        }
        notes.push_back(currentNote);
    } while (!data.eof());

    int sum = 0;
    int p2sum = 0;
    for (auto current: notes) {
        int rsum;
        bool rtype;

        std::vector<std::string> verticalTransform;
        for (int i = 0; i < current[0].length(); i++) {
            verticalTransform.push_back(getColumn(current, i));
        }

        //p1
        // rtype will be true if a horizontal reflection was found
        // and false if a vertical reflection was found

        // rsum will hold the sum of rows or columns, from the p1 reflection
        int H = findReflect(current);
        if (H != -1) {
            sum += H * 100;
            rsum = H;
            rtype = true;
        } else {

            int V = findReflect(verticalTransform);
            sum += V;
            rsum = V;
            rtype = false;
        }

        //p2
        int H2 = rtype ? unsmudgeFindReflect(current, rsum) : unsmudgeFindReflect(current, -1);
        if (H2 != -1) {
            p2sum += H2 * 100;
        } else {
            int V2 = !rtype ? unsmudgeFindReflect(verticalTransform, rsum) : unsmudgeFindReflect(verticalTransform, -1);
            p2sum += V2 != -1 ? V2 : rsum;
        }
    }
    std::cout << "p1 reflect sum: " << sum << '\n';

    std::cout << "p2 reflect sum: " << p2sum << '\n';
}

//p1 reflection finder
int day13::findReflect(std::vector<std::string> note) {
    std::string prevLine = note.front();
    std::vector<int> pointsOfSymmetry;
    //find all the points of symmetry present in the note
    for (int linenum = 1; linenum < note.size(); linenum++) {
        if (prevLine == note[linenum]) {
            pointsOfSymmetry.push_back(linenum);
        }
        prevLine = note[linenum];
    }
    //for all the points of symmetry, determine if the
    // reflection extends to either bound of the note
    for (auto point: pointsOfSymmetry) {
        bool allIterationsRan = true;
        for (int top = point - 1, bottom = point;
             top >= 0 && bottom < note.size();
             top--, bottom++) {
            if (note[top] != note[bottom]) {
                allIterationsRan = false;
                break;
            }
        }
        // if the reflection extends, return the reflection point
        if (allIterationsRan) {
            return point;
        }
    }
    return -1;
}

//used to translate a column of a note to a string
std::string day13::getColumn(const std::vector<std::string> &note, int ind) {
    std::string column;
    for (auto row: note) {
        column += row.at(ind);
    }
    return column;
}

//p2 reflection finder. all the same ideas, but now making use of possibleSmudge()
int day13::unsmudgeFindReflect(std::vector<std::string> note, int previous) {
    std::string prevLine = note.front();
    std::vector<int> pointsOfSymmetry;
    //same as before, find all points of reflection
    for (int linenum = 1; linenum < note.size(); linenum++) {
        if (prevLine == note[linenum] || possibleSmudge(prevLine, note[linenum])) {
            pointsOfSymmetry.push_back(linenum);
        }
        prevLine = note[linenum];
    }
    //for all the points of symmetry, determine if the
    // reflection extends to either bound of the note
    for (auto point: pointsOfSymmetry) {
        //ignore the the point of symmetry that was initially used in p1
        if(point != previous) {
            bool allIterationsRan = true;
            for (int top = point - 1, bottom = point;
                 top >= 0 && bottom < note.size();
                 top--, bottom++) {
                if (note[top] != note[bottom] && !possibleSmudge(note[top], note[bottom])) {
                    allIterationsRan = false;
                    break;
                }
            }
            if (allIterationsRan) {
                return point;
            }
        }
    }
    return -1;
}

//used to determine if the smudge is present on one of the 2 lines
//passed into the parameters
bool day13::possibleSmudge(std::string t, std::string b) {
    int differences = 0;
    for (int i = 0; i < t.length(); i++) {
        if (t.at(i) != b.at(i)) {
            differences++;
        }
    }
    if (differences == 1) {
        return true;
    }
    return false;
}
