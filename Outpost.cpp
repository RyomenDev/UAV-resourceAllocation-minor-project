// #include "Outpost.h"

// Outpost::Outpost(int id, double deadline, double weight_needed, std::pair<double, double> coordinates)
//     : id(id), deadline(deadline), weight_needed(weight_needed), coordinates(coordinates) {}

// double Outpost::priorityScore() const
// {
//     return 1.0 / deadline;
// }

#include "Outpost.h"

Outpost::Outpost(int id, double deadline, double weight_needed, std::pair<double, double> coordinates)
    : id(id), deadline(deadline), weight_needed(weight_needed), coordinates(coordinates) {}

double Outpost::priorityScore() const
{
    return 1.0 / deadline;
}
