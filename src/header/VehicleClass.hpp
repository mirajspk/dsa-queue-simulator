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

public: 
    Vehicle( int id, Lane origin, Lane destination, Route route, sf::Vector2f position);
    int getID();  
    Lane getOriginLane();
    Lane getDestinationLane();               
    Route getRoute(); 
    void move(sf::Vector2f position);
    void draw(sf::RenderWindow& window);

    
                     
};

#endif 
