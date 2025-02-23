#include "header/VehicleClass.hpp"
#include <cmath>

Vehicle::Vehicle(int id, Lane origin, Lane destination, Route route, float spawnOffset)
    : origin(origin), destination(destination), route(route), id(id) {
    rectangle.setSize(sf::Vector2f(15, 15));
    rectangle.setFillColor(sf::Color::Red);
    setRoute(route, spawnOffset);
}

Lane Vehicle::getOriginLane() {
    return origin;
}

Lane Vehicle::getDestinationLane() {
    return destination;
}

Route Vehicle::getRoute() {
    return route;
}

int Vehicle::getID() const { 
    return id;
}

void Vehicle::move(sf::Vector2f position) {
    rectangle.move(position);
}

void Vehicle::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

void Vehicle::setRoute(Route route, float spawnOffset) {
    float gap = 20.0f;
    switch (route) {
        case Route::MOVE_D_TO_C:
            rectangle.setPosition(spawnOffset * gap, 485.5);
            waypoints = {sf::Vector2f(1080, 485.5)};
            break;

        case Route::MOVE_D_TO_B:
            rectangle.setPosition(spawnOffset * gap, 485.5);
            waypoints = {sf::Vector2f(572.5, 485.5), sf::Vector2f(572.5, 1080)};
            break;

        case Route::MOVE_D_TO_A:
            rectangle.setPosition(spawnOffset * gap, 445.5);
            waypoints = {sf::Vector2f(495.5, 445.5), sf::Vector2f(495.5, -100)};
            break;

        case Route::MOVE_A_TO_B:
            rectangle.setPosition(552.5, spawnOffset * gap);
            waypoints = {sf::Vector2f(552.5, 1080)};
            break;

        case Route::MOVE_A_TO_D:
            rectangle.setPosition(552.5, spawnOffset * gap);
            waypoints = {sf::Vector2f(552.5, 542.5), sf::Vector2f(-100, 542.5)};
            break;

        case Route::MOVE_A_TO_C:
            rectangle.setPosition(590, spawnOffset * gap);
            waypoints = {sf::Vector2f(590, 466.5), sf::Vector2f(1100, 466.5)};
            break;

        case Route::MOVE_C_TO_B:
            rectangle.setPosition(1100 - spawnOffset * gap, 562.5);
            waypoints = {sf::Vector2f(580, 562.5), sf::Vector2f(580, 1100)};
            break;

        case Route::MOVE_C_TO_D:
            rectangle.setPosition(1100 - spawnOffset * gap, 523.5);
            waypoints = {sf::Vector2f(-100, 523.5)};
            break;

        case Route::MOVE_C_TO_A:
            rectangle.setPosition(1100 - spawnOffset * gap, 523.5);
            waypoints = {sf::Vector2f(503, 523.5), sf::Vector2f(503, -100)};
            break;

        case Route::MOVE_B_TO_A:
            rectangle.setPosition(512.5, 1100 - spawnOffset * gap);
            waypoints = {sf::Vector2f(512.5, -100)};
            break;

        case Route::MOVE_B_TO_D:
            rectangle.setPosition(474.5, 1100 - spawnOffset * gap);
            waypoints = {sf::Vector2f(474.5, 545.5), sf::Vector2f(-100, 545.5)};
            break;

        case Route::MOVE_B_TO_C:
            rectangle.setPosition(512.5, 1100 - spawnOffset * gap);
            waypoints = {sf::Vector2f(512.5, 465.5), sf::Vector2f(1100, 465.5)};
            break;
    }
}

void Vehicle::update(float deltaTime, const std::vector<Vehicle>& allVehicles) {
    if (currentWaypointIndex < waypoints.size() && !isStopped) {
        
        float minGap = 20.0f;
        bool tooClose = false;
        sf::Vector2f currentPos = rectangle.getPosition();
        sf::Vector2f nextWaypoint = waypoints[currentWaypointIndex];

        for (const auto& other : allVehicles) {
            if (other.getID() != id) { 
                sf::Vector2f otherPos = other.rectangle.getPosition();
                float distance = std::sqrt(std::pow(otherPos.x - currentPos.x, 2) + std::pow(otherPos.y - currentPos.y, 2));

                
                bool isAhead = false;
                if (nextWaypoint.x > currentPos.x && otherPos.x > currentPos.x && std::abs(otherPos.y - currentPos.y) < 15.0f) {
                    isAhead = true; 
                } else if (nextWaypoint.x < currentPos.x && otherPos.x < currentPos.x && std::abs(otherPos.y - currentPos.y) < 15.0f) {
                    isAhead = true; 
                } else if (nextWaypoint.y > currentPos.y && otherPos.y > currentPos.y && std::abs(otherPos.x - currentPos.x) < 15.0f) {
                    isAhead = true; 
                } else if (nextWaypoint.y < currentPos.y && otherPos.y < currentPos.y && std::abs(otherPos.x - currentPos.x) < 15.0f) {
                    isAhead = true; 
                }

                if (isAhead && distance < minGap) {
                    tooClose = true;
                    break;
                }
            }
        }

        if (!tooClose) {
            sf::Vector2f direction = nextWaypoint - currentPos;
            float distanceToWaypoint = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distanceToWaypoint > speed * deltaTime) {
                direction /= distanceToWaypoint;
                rectangle.move(direction * speed * deltaTime);
            } else {
                rectangle.setPosition(nextWaypoint);
                currentWaypointIndex++;
            }
        }
    }
}

sf::FloatRect Vehicle::getBounds() {
    return rectangle.getGlobalBounds();
}

void Vehicle::stop() {
    isStopped = true;
    speed = 0.0f;
}

void Vehicle::resume() {
    isStopped = false;
    speed = 100.0f;
}