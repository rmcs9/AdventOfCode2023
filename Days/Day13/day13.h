#include <string>
#ifndef ADVENT_DAY13_H
#define ADVENT_DAY13_H


class day13 {
public:
    void symmetrySum(std::string fp);
private:
    int findReflect(std::vector<std::string> note);
    std::string getColumn(const std::vector<std::string> &note, int ind);
    int unsmudgeFindReflect(std::vector<std::string> note, int previous);
    bool possibleSmudge(std::string t, std::string b);
};

#endif //ADVENT_DAY13_H
