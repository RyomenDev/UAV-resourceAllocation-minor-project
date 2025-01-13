#include "UAV.h"

UAV::UAV(int id, double capacity, double speed, double max_distance)
    : id(id), capacity(capacity), speed(speed), max_distance(max_distance),
      fuel_consumed(0), total_time(0), current_position({0, 0}), available_capacity(capacity) {}

double UAV::calculateTime(double distance) const
{
    return distance / speed;
}

bool UAV::canFulfill(double weight, double distance, double available_time) const
{
    return weight <= available_capacity && distance <= max_distance && calculateTime(distance) <= available_time;
}

void UAV::deliver(double distance, double weight, const std::pair<double, double> &destination)
{
    fuel_consumed += distance;
    total_time += calculateTime(distance);
    available_capacity -= weight;
    current_position = destination;
}

void UAV::resetToBase(const std::pair<double, double> &base_coordinates)
{
    double distance_to_base = calculateDistance(current_position, base_coordinates);
    fuel_consumed += distance_to_base;
    total_time += calculateTime(distance_to_base);
    current_position = base_coordinates;
    available_capacity = capacity;
}

double UAV::calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2)
{
    return std::sqrt(std::pow(coord2.first - coord1.first, 2) + std::pow(coord2.second - coord1.second, 2));
}
