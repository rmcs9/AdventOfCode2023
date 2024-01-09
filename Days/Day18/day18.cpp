#include "day18.h"
#include <iostream>
#include <fstream>
#include <stack>

struct plan {
    char dir;
    int meters;
    std::string color;
};

void day18::LAVA(std::string fp) {
    std::fstream data(fp);
    std::vector<plan> plans;
    do {
        plan currentPlan;
        data >> currentPlan.dir;
        data >> currentPlan.meters;
        data >> currentPlan.color;
        currentPlan.color = currentPlan.color.substr(2, currentPlan.color.length() - 3);
        plans.push_back(currentPlan);
    } while (!data.eof());

    //p1 uses a rather large 1000 by 1000 array to physically map the shape of the pit
    // and then uses floodfill() to fill in the shape.
    //the complete shape can be seen in mapfile.txt
    memset(map, '.', sizeof(map));
    int borderTotal = 0;
    map[500][500] = '#';
    int row = 500, col = 500;
    for (const auto &plan: plans) {
        if (plan.dir == 'U' || plan.dir == 'D') {
            for (int i = 0; i < plan.meters; i++) {
                row = plan.dir == 'U' ? row - 1 : row + 1;
                map[row][col] = '#';
                borderTotal++;
            }
        } else {
            for (int i = 0; i < plan.meters; i++) {
                col = plan.dir == 'L' ? col - 1 : col + 1;
                map[row][col] = '#';
                borderTotal++;
            }
        }
    }

    //add the points on the border to the points filled in to get the total
    std::cout << "p1 total: " << borderTotal + floodfill() << '\n';

    //remap the plans to their color instructions
    for (auto &plan: plans) {
        plan.meters = std::stoi(plan.color.substr(0, plan.color.length() - 1), nullptr, 16);
        switch (plan.color.at(plan.color.length() - 1)) {
            case '0':
                plan.dir = 'R';
                break;
            case '1':
                plan.dir = 'D';
                break;
            case '2':
                plan.dir = 'L';
                break;
            case '3':
                plan.dir = 'U';
                break;
        }
    }

    std::cout << "p2 total: " << p2area(plans) << std::endl;
}

int day18::floodfill() {
    int total = 0;
    std::stack<std::pair<int, int>> stack;
    stack.emplace(501, 501);

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();
        if (map[current.first][current.second] != '#') {
            total++;
            map[current.first][current.second] = '#';

            //up
            stack.emplace(current.first - 1, current.second);
            //right
            stack.emplace(current.first, current.second + 1);
            //down
            stack.emplace(current.first + 1, current.second);
            //left
            stack.emplace(current.first, current.second - 1);
        }
    }
    return total;
}

//p1's physical mapping would definitely not work here for p2
long long int day18::p2area(std::vector<plan> &plans) {
    long long int row = 0, col = 0, perimeter = 0;
    long long area = 0;
    //follow sort of the same procedure as p1,
    //keeping track of the row and col positions
    for (const auto &plan: plans) {
        int rowchange;
        if (plan.dir == 'U' || plan.dir == 'D') {
            row = plan.dir == 'U' ? row - plan.meters : row + plan.meters;
            rowchange = plan.dir == 'U' ? plan.meters * -1 : plan.meters;
        } else {
            col = plan.dir == 'L' ? col - plan.meters : col + plan.meters;
            rowchange = 0;
        }
        //the border points can be found by adding on the current instructions meters
        perimeter += plan.meters;
        //shoelace formula
        area += col * rowchange;
    }
    // picks theorum: {[A = i + b/2 - 1] where A = area, i = interior points, b = boundary points}
    // rearrange the formula to solve for i:
    // i = A - b/2 + 1
    // the above formula will strictly give us only the interior points of the shape
    // because we want to include the perimeter points in this case, add b into this equation:
    // i = A + b/2 + 1
    return area + perimeter / 2 + 1;
}