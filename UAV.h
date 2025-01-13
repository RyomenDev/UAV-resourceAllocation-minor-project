// #ifndef UAV_H
// #define UAV_H

// #include <iostream>
// #include <utility>
// #include <cmath>

// class UAV
// {
// public:
//     int id;
//     double capacity, speed, max_distance;
//     double fuel_consumed, total_time;
//     double available_capacity;
//     std::pair<double, double> current_position;

//     UAV(int id, double capacity, double speed, double max_distance);

//     double calculateTime(double distance) const;

//     bool canFulfill(double weight, double distance, double available_time) const;

//     void deliver(double distance, double weight, const std::pair<double, double> &destination);

//     void resetToBase(const std::pair<double, double> &base_coordinates);

// private:
//     static double calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2);
// };

// #endif

#ifndef UAV_H
#define UAV_H

#include <utility>
#include <cmath>

class UAV
{
public:
    int id;
    double capacity, speed, max_distance;
    double fuel_consumed, total_time;
    double available_capacity;
    std::pair<double, double> current_position;

    UAV(int id, double capacity, double speed, double max_distance);

    double calculateTime(double distance) const;
    bool canFulfill(double weight, double distance, double available_time) const;
    void deliver(double distance, double weight, const std::pair<double, double> &destination);
    void resetToBase(const std::pair<double, double> &base_coordinates);

private:
    static double calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2);
};

#endif
