

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// UAV class
class UAV
{
public:
    int id;
    double capacity, speed, max_distance;
    double fuel_consumed, total_time;
    double available_capacity;
    pair<double, double> current_position;

    UAV(int id, double capacity, double speed, double max_distance)
        : id(id), capacity(capacity), speed(speed), max_distance(max_distance),
          fuel_consumed(0), total_time(0), current_position({0, 0}), available_capacity(capacity) {}

    double calculateTime(double distance) const
    {
        return distance / speed;
    }

    bool canFulfill(double weight, double distance, double available_time) const
    {
        return weight <= available_capacity && distance <= max_distance && calculateTime(distance) <= available_time;
    }

    void deliver(double distance, double weight, const pair<double, double> &destination)
    {
        fuel_consumed += distance;
        total_time += calculateTime(distance);
        available_capacity -= weight;
        current_position = destination;
    }

    void resetToBase(const pair<double, double> &base_coordinates)
    {
        double distance_to_base = calculateDistance(current_position, base_coordinates);
        fuel_consumed += distance_to_base;
        total_time += calculateTime(distance_to_base);
        current_position = base_coordinates;
        available_capacity = capacity; // Refuel to full capacity.
    }

private:
    static double calculateDistance(const pair<double, double> &coord1, const pair<double, double> &coord2)
    {
        return sqrt(pow(coord2.first - coord1.first, 2) + pow(coord2.second - coord1.second, 2));
    }
};

// Outpost class
class Outpost
{
public:
    int id;
    double deadline, weight_needed;
    pair<double, double> coordinates;

    Outpost(int id, double deadline, double weight_needed, pair<double, double> coordinates)
        : id(id), deadline(deadline), weight_needed(weight_needed), coordinates(coordinates) {}

    double priorityScore() const
    {
        return 1.0 / deadline;
    }
};

// Base class
class Base
{
private:
    pair<double, double> coordinates;
    vector<UAV> uavs;
    vector<Outpost> outposts;

    static double calculateDistance(const pair<double, double> &coord1, const pair<double, double> &coord2)
    {
        return sqrt(pow(coord2.first - coord1.first, 2) + pow(coord2.second - coord1.second, 2));
    }

    void sortOutpostsByPriority()
    {
        sort(outposts.begin(), outposts.end(), [](const Outpost &a, const Outpost &b)
             { return a.priorityScore() > b.priorityScore(); });
    }

public:
    Base(double x, double y) : coordinates({x, y}) {}

    void addUAV(const UAV &uav)
    {
        uavs.push_back(uav);
    }

    void addOutpost(const Outpost &outpost)
    {
        outposts.push_back(outpost);
    }

    void allocateResources()
    {
        sortOutpostsByPriority();

        vector<bool> fulfilled(outposts.size(), false);

        for (Outpost &outpost : outposts)
        {
            if (outpost.weight_needed <= 0)
                continue;

            UAV *selected_uav = nullptr;
            double min_total_time = numeric_limits<double>::max();

            for (UAV &uav : uavs)
            {
                double distance_to_outpost = calculateDistance(uav.current_position, outpost.coordinates);
                double distance_back_to_base = calculateDistance(outpost.coordinates, coordinates);
                double total_distance = distance_to_outpost + distance_back_to_base;

                if (uav.canFulfill(outpost.weight_needed, distance_to_outpost, outpost.deadline - uav.total_time))
                {
                    double potential_time = uav.total_time + uav.calculateTime(total_distance);
                    if (potential_time < min_total_time)
                    {
                        min_total_time = potential_time;
                        selected_uav = &uav;
                    }
                }
            }

            if (selected_uav)
            {
                double distance = calculateDistance(selected_uav->current_position, outpost.coordinates);
                double delivery_weight = min(outpost.weight_needed, selected_uav->available_capacity);
                selected_uav->deliver(distance, delivery_weight, outpost.coordinates);

                cout << fixed << setprecision(2);
                cout << "UAV " << selected_uav->id << " delivered " << delivery_weight
                     << " units to Outpost " << outpost.id << " (Distance: " << distance
                     << " units, Time: " << selected_uav->calculateTime(distance) << " units)." << endl;

                outpost.weight_needed -= delivery_weight;

                if (outpost.weight_needed <= 0)
                {
                    fulfilled[outpost.id] = true;
                    cout << "Outpost " << outpost.id << " fulfilled." << endl;
                }

                selected_uav->resetToBase(coordinates);
                cout << "UAV " << selected_uav->id << " returned to base for refuel/reassignment." << endl;
                cout << "   Remaining Capacity: " << selected_uav->available_capacity << " units" << endl;
                cout << "   Total Fuel Consumed: " << selected_uav->fuel_consumed << " units" << endl;
                cout << "   Total Time Used: " << selected_uav->total_time << " units" << endl;
            }
            else
            {
                cout << "No UAV can fulfill Outpost " << outpost.id << " within the deadline." << endl;
            }
        }
    }
};

int main()
{
    // Base coordinates
    Base base(0.0, 0.0);

    // Adding UAVs
    base.addUAV(UAV(1, 50, 80, 500));
    base.addUAV(UAV(2, 45, 120, 400));
    base.addUAV(UAV(3, 55, 110, 450));
    base.addUAV(UAV(4, 60, 90, 600));

    // Adding outposts with coordinates
    base.addOutpost(Outpost(0, 0.5, 20, {25.0, 10.0}));
    base.addOutpost(Outpost(1, 1.0, 35, {15.0, 25.0}));
    base.addOutpost(Outpost(2, 0.67, 30, {20.0, 10.0}));

    // Allocate resources
    base.allocateResources();

    return 0;
}
