// #ifndef OUTPOST_H
// #define OUTPOST_H

// #include <utility>

// class Outpost
// {
// public:
//     int id;
//     double deadline, weight_needed;
//     std::pair<double, double> coordinates;

//     Outpost(int id, double deadline, double weight_needed, std::pair<double, double> coordinates);

//     double priorityScore() const;
// };

// #endif

#ifndef OUTPOST_H
#define OUTPOST_H

#include <utility>

class Outpost
{
public:
    int id;
    double deadline, weight_needed;
    std::pair<double, double> coordinates;

    Outpost(int id, double deadline, double weight_needed, std::pair<double, double> coordinates);

    double priorityScore() const;
};

#endif
