#include "header/Road.hpp"

Road::Road(VehicleQueue lane2, VehicleQueue lane3): lane2(lane2), lane3(lane3) {}

float Road::getVehicleAvg(VehicleQueue lane2, VehicleQueue lane3){
    return (lane2.size()+lane3.size())/2.0f;
}