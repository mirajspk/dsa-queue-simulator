#ifndef LANE_TRIGGER_HPP
#define LANE_TRIGGER_HPP

#include <SFML/Graphics.hpp>
#include "Lane.hpp"
#include "VehicleClass.hpp"

class LaneTrigger {
    private:
        sf::RectangleShape laneArea;
        Lane lane;
        sf::Vector2f position;
        sf::Vector2f size;

    public:
        LaneTrigger(sf::Vector2f position, sf::Vector2f size, Lane lane);
        bool isVehicleOnLane(Vehicle& vehicle);
        Lane getLane();
        void draw(sf::RenderWindow& window);  
};

#endif