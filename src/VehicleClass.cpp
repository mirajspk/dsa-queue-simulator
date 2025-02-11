#include "header/VehicleClass.hpp"

Vehicle::Vehicle(int id, Lane origin, Lane destination, Route route)
    : origin(origin), destination(destination), route(route), id(id)
    {
    rectangle.setSize(sf::Vector2f(15, 15));
    rectangle.setFillColor(sf::Color::Red);
    setRoute(route);

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

void Vehicle::setRoute(Route route) {
    switch (route) {
        case Route::MOVE_D_TO_C:
            rectangle.setPosition(0, 485.5);
            waypoints = {sf::Vector2f(1080, 485.5)}; 
            break;
        case Route::MOVE_D_TO_A:
            rectangle.setPosition(0, 445.5);
            waypoints = {sf::Vector2f(495.5, 445.5), sf::Vector2f(495.5, -100)}; 
            break;
    }
}

void Vehicle::update(float deltaTime) {
    if (currentWaypointIndex < waypoints.size()) {
        sf::Vector2f direction = waypoints[currentWaypointIndex] - rectangle.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > speed * deltaTime) {
            direction /= distance;
            rectangle.move(direction * speed * deltaTime);
        } else {
            rectangle.setPosition(waypoints[currentWaypointIndex]);
            currentWaypointIndex++; 
        }
    }
}

sf::FloatRect Vehicle::getBounds() {
    return rectangle.getGlobalBounds();
}