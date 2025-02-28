#ifndef VEHICLE_CLASS_HPP
#define VEHICLE_CLASS_HPP

#include "Route.hpp" 
#include "Lane.hpp"
#include <SFML/Graphics.hpp>

class Vehicle {
private:
    Lane origin;
    Lane destination;                           
    Route route;                
    int id;
    sf::RectangleShape rectangle; 
    std::vector<sf::Vector2f> waypoints;
    size_t currentWaypointIndex;
    float speed = 100.0f;
    bool isStopped = false; 
    bool isRouteCompleted = false; 

public: 
    Vehicle(int id, Lane origin, Lane destination, Route route, float spawnOffset);
    int getID() const;
    Lane getOriginLane() const;
    Lane getDestinationLane() const; 
    Route getRoute() const; 
    void move(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    void setRoute(Route route, float spawnOffset);
    void update(float deltaTime, const std::vector<Vehicle>& allVehicles);
    sf::FloatRect getBounds();                 
    void stop(); 
    void resume(); 
    bool hasCompletedRoute() const; 
};

#endif