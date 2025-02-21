#ifndef ROAD_HPP
#define ROAD_HPP

#include "VehicleQueue.hpp"

class Road {
    private:
        VehicleQueue lane2;
        VehicleQueue lane3;
    
    public:
        Road(VehicleQueue lane2, VehicleQueue lane3);
        float getVehicleAvg(VehicleQueue lane2, VehicleQueue lane3);
};

#endif 