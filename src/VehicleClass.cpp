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

void Vehicle::setRoute(Route route){
    switch(route){
        case Route::MOVE_D_TO_C:
            rectangle.setPosition(0, 485.5);
            destinationPosition = sf::Vector2f(1080, 485.5);
            break;
    }
}

void Vehicle::update(float deltaTime) {
        if (rectangle.getPosition() != destinationPosition) {
            sf::Vector2f direction = destinationPosition - rectangle.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance > speed * deltaTime) {
                direction /= distance; 
                rectangle.move(direction * speed * deltaTime);
            } else {
                rectangle.setPosition(destinationPosition); 
            }
        }
    }
