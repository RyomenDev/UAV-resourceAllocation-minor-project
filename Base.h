// #ifndef BASE_H
// #define BASE_H

// #include "UAV.h"
// #include "Outpost.h"
// #include <vector>
// #include <algorithm>
// #include <iostream>
// #include <iomanip>

// class Base
// {
// private:
//     std::pair<double, double> coordinates;
//     std::vector<UAV> uavs;
//     std::vector<Outpost> outposts;

//     static double calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2);

//     void sortOutpostsByPriority();

// public:
//     Base(double x, double y);

//     void addUAV(const UAV &uav);

//     void addOutpost(const Outpost &outpost);

//     void allocateResources();
// };

// #endif

#ifndef BASE_H
#define BASE_H

#include "UAV.h"
#include "Outpost.h"
#include <vector>
#include <iostream>
#include <iomanip>

class Base
{
private:
    std::pair<double, double> coordinates;
    std::vector<UAV> uavs;
    std::vector<Outpost> outposts;

    static double calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2);
    void sortOutpostsByPriority();

public:
    Base(double x, double y);

    void addUAV(const UAV &uav);
    void addOutpost(const Outpost &outpost);
    void allocateResources();
};

#endif
