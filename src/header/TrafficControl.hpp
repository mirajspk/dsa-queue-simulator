#ifndef TRAFFIC_CONTROL_HPP
#define TRAFFIC_CONTROL_HPP

#include "Light.hpp"
#include "RoadType.hpp"
#include <SFML/Graphics.hpp>

class TrafficControl {
private:
    Light light;
    sf::CircleShape lightShape;
    RoadType road;
    sf::Vector2f position;
    sf::RectangleShape blocker;
    sf::Vector2f blockerPosition;
    sf::Vector2f blockerSize;

public:
    TrafficControl(Light initialLight, sf::Vector2f position, RoadType road, sf::Vector2f blockerSize, sf::Vector2f blockerPosition);
    void setLight(Light newLight);
    Light getLight();
    bool isRed();
    void draw(sf::RenderWindow& window);
    sf::RectangleShape getBlocker();
    
};

#endif 