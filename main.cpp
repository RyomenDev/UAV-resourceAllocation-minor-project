// #include "Base.h"

// int main()
// {
//     Base base(0.0, 0.0);

//     base.addUAV(UAV(1, 50, 80, 500));
//     base.addUAV(UAV(2, 45, 120, 400));
//     base.addUAV(UAV(3, 55, 110, 450));
//     base.addUAV(UAV(4, 60, 90, 600));

//     base.addOutpost(Outpost(0, 0.5, 20, {25.0, 10.0}));
//     base.addOutpost(Outpost(1, 1.0, 35, {15.0, 25.0}));
//     base.addOutpost(Outpost(2, 0.67, 30, {20.0, 10.0}));

//     base.allocateResources();

//     return 0;
// }

#include "Base.h"
#include <iostream>

int main()
{
    double base_x, base_y;
    std::cout << "Enter Base coordinates (x y): ";
    std::cin >> base_x >> base_y;

    Base base(base_x, base_y);

    int num_uavs;
    std::cout << "Enter number of UAVs: ";
    std::cin >> num_uavs;

    for (int i = 0; i < num_uavs; ++i)
    {
        int id;
        double capacity, speed, max_distance;
        std::cout << "Enter UAV " << i + 1 << " details (id capacity speed max_distance): ";
        std::cin >> id >> capacity >> speed >> max_distance;
        base.addUAV(UAV(id, capacity, speed, max_distance));
    }

    int num_outposts;
    std::cout << "Enter number of Outposts: ";
    std::cin >> num_outposts;

    for (int i = 0; i < num_outposts; ++i)
    {
        int id;
        double deadline, weight_needed, x, y;
        std::cout << "Enter Outpost " << i + 1 << " details (id deadline weight_needed x y): ";
        std::cin >> id >> deadline >> weight_needed >> x >> y;
        base.addOutpost(Outpost(id, deadline, weight_needed, {x, y}));
    }

    base.allocateResources();

    return 0;
}

/*

g++ -o uav_system main.cpp UAV.cpp Outpost.cpp Base.cpp
./uav_system

*/