#ifndef VEHICLE_QUEUE_HPP
#define VEHICLE_QUEUE_HPP

#include "./VehicleClass.hpp"
#include <vector>


class VehicleQueue {
    
    private:
        std::vector<Vehicle> queue;

    public:
        void enqueue(Vehicle& vehicle);
        void dequeue();
        int size();      
};

#endif