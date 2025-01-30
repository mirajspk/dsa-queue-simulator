#include "header/VehicleClass.hpp"

Vehicle::Vehicle(Lane lane, Route route, int id)
    : lane(lane), route(route), id(id){}

Lane Vehicle::getLane() const {
    return lane;
}

Route Vehicle::getRoute() const {
    return route;
}

int Vehicle::getID() const {
    return id;
}

