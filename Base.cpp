// #include "Base.h"

// Base::Base(double x, double y) : coordinates({x, y}) {}

// void Base::addUAV(const UAV &uav)
// {
//     uavs.push_back(uav);
// }

// void Base::addOutpost(const Outpost &outpost)
// {
//     outposts.push_back(outpost);
// }

// void Base::sortOutpostsByPriority()
// {
//     sort(outposts.begin(), outposts.end(), [](const Outpost &a, const Outpost &b)
//          { return a.priorityScore() > b.priorityScore(); });
// }

// double Base::calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2)
// {
//     return std::sqrt(std::pow(coord2.first - coord1.first, 2) + std::pow(coord2.second - coord1.second, 2));
// }

// void Base::allocateResources()
// {
//     sortOutpostsByPriority();
//     std::vector<bool> fulfilled(outposts.size(), false);

//     for (Outpost &outpost : outposts)
//     {
//         if (outpost.weight_needed <= 0)
//             continue;

//         UAV *selected_uav = nullptr;
//         double min_total_time = std::numeric_limits<double>::max();

//         for (UAV &uav : uavs)
//         {
//             double distance_to_outpost = calculateDistance(uav.current_position, outpost.coordinates);
//             double distance_back_to_base = calculateDistance(outpost.coordinates, coordinates);
//             double total_distance = distance_to_outpost + distance_back_to_base;

//             if (uav.canFulfill(outpost.weight_needed, distance_to_outpost, outpost.deadline - uav.total_time))
//             {
//                 double potential_time = uav.total_time + uav.calculateTime(total_distance);
//                 if (potential_time < min_total_time)
//                 {
//                     min_total_time = potential_time;
//                     selected_uav = &uav;
//                 }
//             }
//         }

//         if (selected_uav)
//         {
//             double distance = calculateDistance(selected_uav->current_position, outpost.coordinates);
//             double delivery_weight = std::min(outpost.weight_needed, selected_uav->available_capacity);
//             selected_uav->deliver(distance, delivery_weight, outpost.coordinates);

//             std::cout << std::fixed << std::setprecision(2);
//             std::cout << "UAV " << selected_uav->id << " delivered " << delivery_weight
//                       << " units to Outpost " << outpost.id << " (Distance: " << distance
//                       << " units, Time: " << selected_uav->calculateTime(distance) << " units)." << std::endl;

//             outpost.weight_needed -= delivery_weight;

//             if (outpost.weight_needed <= 0)
//             {
//                 fulfilled[outpost.id] = true;
//                 std::cout << "Outpost " << outpost.id << " fulfilled." << std::endl;
//             }

//             selected_uav->resetToBase(coordinates);
//             std::cout << "UAV " << selected_uav->id << " returned to base for refuel/reassignment." << std::endl;
//         }
//         else
//         {
//             std::cout << "No UAV can fulfill Outpost " << outpost.id << " within the deadline." << std::endl;
//         }
//     }
// }


#include <bits/stdc++.h>
#include "Base.h"

Base::Base(double x, double y) : coordinates({x, y}) {}

void Base::addUAV(const UAV &uav)
{
    uavs.push_back(uav);
}

void Base::addOutpost(const Outpost &outpost)
{
    outposts.push_back(outpost);
}

void Base::sortOutpostsByPriority()
{
    std::sort(outposts.begin(), outposts.end(), [](const Outpost &a, const Outpost &b)
              { return a.priorityScore() > b.priorityScore(); });
}

double Base::calculateDistance(const std::pair<double, double> &coord1, const std::pair<double, double> &coord2)
{
    return std::sqrt(std::pow(coord2.first - coord1.first, 2) + std::pow(coord2.second - coord1.second, 2));
}

void Base::allocateResources()
{
    sortOutpostsByPriority();

    for (Outpost &outpost : outposts)
    {
        UAV *selected_uav = nullptr;
        double min_total_time = std::numeric_limits<double>::max();

        for (UAV &uav : uavs)
        {
            double distance = calculateDistance(uav.current_position, outpost.coordinates);
            if (uav.canFulfill(outpost.weight_needed, distance, outpost.deadline - uav.total_time))
            {
                double potential_time = uav.total_time + uav.calculateTime(distance);
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
            selected_uav->deliver(distance, outpost.weight_needed, outpost.coordinates);
            selected_uav->resetToBase(coordinates);

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "UAV " << selected_uav->id << " delivered to Outpost " << outpost.id << ".\n";
        }
        else
        {
            std::cout << "No UAV can fulfill Outpost " << outpost.id << " on time.\n";
        }
    }
}

