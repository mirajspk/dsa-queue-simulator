#ifndef VEHICLE_H
#define VEHICLE_H

#include "Route.hpp" 
#include "Lane.hpp"
#include<SFML/Graphics.hpp>

class Vehicle {

private:
    Lane origin;
    Lane destination;                           
    Route route;                
    int id;
    sf::RectangleShape rectangle; 
    sf::Vector2f destinationPosition;
    float speed = 100.0f;


public: 
    Vehicle( int id, Lane origin, Lane destination, Route route);
    int getID();  
    Lane getOriginLane();
    Lane getDestinationLane();               
    Route getRoute(); 
    void move(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    void setRoute(Route route);
    void update(float deltaTime);
    sf::FloatRect getBounds();                 
};

#endif 
