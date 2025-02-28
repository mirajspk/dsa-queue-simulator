#include "VehicleClass.hpp"
#include <cmath>

Vehicle::Vehicle(int id, Lane origin, Lane destination, Route route, float spawnOffset)
    : origin(origin), destination(destination), route(route), id(id), isRouteCompleted(false) {
    rectangle.setSize(sf::Vector2f(15, 15));
    rectangle.setFillColor(sf::Color::Red);
    setRoute(route, spawnOffset);
}

int Vehicle::getID() const {
    return id;
}

Lane Vehicle::getOriginLane() const {
    return origin;
}

Lane Vehicle::getDestinationLane() const {
    return destination;
}

Route Vehicle::getRoute() const {
    return route;
}

void Vehicle::move(sf::Vector2f position) {
    rectangle.setPosition(position);
}

void Vehicle::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

void Vehicle::setRoute(Route route, float spawnOffset) {
    float gap = 20.0f;
    waypoints.clear();

    switch (origin) {
        case Lane::D2:
        case Lane::D3:
            waypoints.push_back(sf::Vector2f(-gap * spawnOffset, route == Route::MOVE_D_TO_A ? 445.5 : 485.5));
            break;
        case Lane::A2:
        case Lane::A3:
            waypoints.push_back(sf::Vector2f(route == Route::MOVE_A_TO_C ? 590 : 552.5, -gap * spawnOffset));
            break;
        case Lane::C2:
        case Lane::C3:
            waypoints.push_back(sf::Vector2f(1080 + gap * spawnOffset, route == Route::MOVE_C_TO_B ? 562.5 : 523.5));
            break;
        case Lane::B2:
        case Lane::B3:
            waypoints.push_back(sf::Vector2f(route == Route::MOVE_B_TO_D ? 474.5 : 512.5, 1080 + gap * spawnOffset));
            break;
    }

    switch (route) {
        case Route::MOVE_D_TO_C:
            waypoints.push_back(sf::Vector2f(2000, 485.5));
            break;

        case Route::MOVE_D_TO_B:
            waypoints.push_back(sf::Vector2f(572.5, 485.5));
            waypoints.push_back(sf::Vector2f(572.5, 2000));
            break;

        case Route::MOVE_D_TO_A:
            waypoints.push_back(sf::Vector2f(495.5, 445.5));
            waypoints.push_back(sf::Vector2f(495.5, -2000));
            break;

        case Route::MOVE_A_TO_B:
            waypoints.push_back(sf::Vector2f(552.5, 2000));
            break;

        case Route::MOVE_A_TO_D:
            waypoints.push_back(sf::Vector2f(552.5, 542.5));
            waypoints.push_back(sf::Vector2f(-2000, 542.5));
            break;

        case Route::MOVE_A_TO_C:
            waypoints.push_back(sf::Vector2f(590, 466.5));
            waypoints.push_back(sf::Vector2f(2000, 466.5));
            break;

        case Route::MOVE_C_TO_B:
            waypoints.push_back(sf::Vector2f(580, 562.5));
            waypoints.push_back(sf::Vector2f(580, 2000));
            break;

        case Route::MOVE_C_TO_D:
            waypoints.push_back(sf::Vector2f(-2000, 523.5));
            break;

        case Route::MOVE_C_TO_A:
            waypoints.push_back(sf::Vector2f(503, 523.5));
            waypoints.push_back(sf::Vector2f(503, -2000));
            break;

        case Route::MOVE_B_TO_A:
            waypoints.push_back(sf::Vector2f(512.5, -2000));
            break;

        case Route::MOVE_B_TO_D:
            waypoints.push_back(sf::Vector2f(474.5, 545.5));
            waypoints.push_back(sf::Vector2f(-2000, 545.5));
            break;

        case Route::MOVE_B_TO_C:
            waypoints.push_back(sf::Vector2f(512.5, 465.5));
            waypoints.push_back(sf::Vector2f(2000, 465.5));
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
                if (currentWaypointIndex >= waypoints.size()) {
                    isRouteCompleted = true; 
                }
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

bool Vehicle::hasCompletedRoute() const {
    return isRouteCompleted;
}