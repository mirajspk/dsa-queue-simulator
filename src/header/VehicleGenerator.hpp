#ifndef VEHICLE_GENERATOR_HPP
#define VEHICLE_GENERATOR_HPP

#include "VehicleClass.hpp"
#include <vector>

class VehicleGenerator {
private:
    int nextId;
    float spawnInterval; 
    sf::Clock spawnClock;

public:
    VehicleGenerator();
    void update(std::vector<Vehicle>& vehicles, float deltaTime);
};

#endif