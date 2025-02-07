#include "header/LaneTrigger.hpp"

LaneTrigger::LaneTrigger(sf::Vector2f position, sf::Vector2f size, Lane lane)
    : position(position), size(size), lane(lane) {
    laneArea.setSize(size);
    laneArea.setPosition(position);
    laneArea.setFillColor(sf::Color(0, 255, 0, 100)); 
}

bool LaneTrigger::isVehicleOnLane(Vehicle& vehicle) {
    return laneArea.getGlobalBounds().intersects(vehicle.getBounds());
}

Lane LaneTrigger::getLane() {
    return lane;
}

void LaneTrigger::draw(sf::RenderWindow& window) {
    window.draw(laneArea);
}