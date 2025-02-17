#ifndef TRAFFIC_CONTROL_HPP
#define TRAFFIC_CONTROL_HPP

#include "Light.hpp"
#include "Road.hpp"
#include <SFML/Graphics.hpp>

class TrafficControl {
private:
    Light light;
    sf::CircleShape lightShape;
    Road road;
    sf::Vector2f position;
    sf::RectangleShape blocker;
    sf::Vector2f blockerPosition;
    sf::Vector2f blockerSize;

public:
    TrafficControl(Light initialLight, sf::Vector2f position, Road road, sf::Vector2f blockerSize, sf::Vector2f blockerPosition);
    void setLight(Light newLight);
    Light getLight();
    void draw(sf::RenderWindow& window);
    
};

#endif // TRAFFIC_CONTROL_HPP