#include "header/TrafficControl.hpp"

TrafficControl::TrafficControl(Light initialLight, sf::Vector2f position, RoadType road, sf::Vector2f blockerSize, sf::Vector2f blockerPosition)
    : light(initialLight), position(position), road(road) {
    lightShape.setRadius(20.0f);
    lightShape.setOrigin(20.0f, 20.0f);
    lightShape.setPosition(position);
    setLight(initialLight); 
    blocker.setPosition(blockerPosition);
    blocker.setSize(blockerSize);
    blocker.setFillColor(sf::Color::Transparent);
}

void TrafficControl::setLight(Light newLight) {
    light = newLight;
    if (light == Light::RED) {
        lightShape.setFillColor(sf::Color::Red);
    } else {
        lightShape.setFillColor(sf::Color::Green);
    }
}

Light TrafficControl::getLight() {
    return light;
}

RoadType TrafficControl::getRoad() {
    return road;
}

void TrafficControl::draw(sf::RenderWindow& window) {
    window.draw(lightShape);
    window.draw(blocker);
}

sf::RectangleShape TrafficControl::getBlocker() {
    return blocker;
}

bool TrafficControl::isRed() {
    return light == Light::RED;
}