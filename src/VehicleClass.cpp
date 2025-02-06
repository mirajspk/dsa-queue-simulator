#include "header/VehicleClass.hpp"

Vehicle::Vehicle(int id, Lane origin, Lane destination, Route route, sf::Vector2f position)
    : origin(origin), destination(destination), route(route), id(id)
    {
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(position);
    }


Lane Vehicle::getOriginLane() {
    return origin;
}

Lane Vehicle::getDestinationLane(){
    return destination;
}

Route Vehicle::getRoute(){
    return route;
}

int Vehicle::getID(){
    return id;
}

void Vehicle::move(sf::Vector2f position){
    rectangle.move(position);
}

void Vehicle::draw(sf::RenderWindow& window){
    window.draw(rectangle);
}

