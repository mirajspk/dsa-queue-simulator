#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "header/VehicleClass.hpp"
#include "header/LaneTrigger.hpp"
#include "header/VehicleQueue.hpp"
#include "header/TrafficControl.hpp"
#include "header/LightQueue.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>

RoadType laneToRoad(Lane lane) {
    switch (lane) {
        case Lane::A2:
        case Lane::A3:
            return RoadType::A;
        case Lane::B2:
        case Lane::B3:
            return RoadType::B;
        case Lane::C2:
        case Lane::C3:
            return RoadType::C;
        case Lane::D2:
        case Lane::D3:
            return RoadType::D;
        default:
            return RoadType::A;
    }
}

int main() {
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode({1080, 1080}), "simulator");

    sf::Texture texture;
    if (!texture.loadFromFile("assets/map.png")) {
        std::cout << "Failed to load map.png" << std::endl;
        return -1;
    }
    sf::Sprite sprite(texture);
    sf::Clock clock;
    sf::Clock lightUpdateClock;

    sf::TcpSocket socket;
    if (socket.connect("127.0.0.1", 55001) != sf::Socket::Done) {
        std::cout << "Failed to connect to server" << std::endl;
        return -1;
    }
    std::cout << "Connected to server" << std::endl;
    socket.setBlocking(false);

    std::map<Lane, VehicleQueue> queues;
    queues[Lane::A1] = VehicleQueue();
    queues[Lane::A2] = VehicleQueue();
    queues[Lane::A3] = VehicleQueue();
    queues[Lane::B1] = VehicleQueue();
    queues[Lane::B3] = VehicleQueue();
    queues[Lane::C1] = VehicleQueue();
    queues[Lane::C2] = VehicleQueue();
    queues[Lane::C3] = VehicleQueue();
    queues[Lane::D1] = VehicleQueue();
    queues[Lane::D2] = VehicleQueue();
    queues[Lane::D3] = VehicleQueue();

    std::vector<std::unique_ptr<Vehicle>> vehicles;
    std::map<int, std::map<Lane, bool>> flags;
    std::map<int, bool> hasDequeued; 
    LightQueue lightQueue;
    float lightUpdateInterval = 5.0f;
    bool a2Priority = false;

    std::vector<LaneTrigger> laneTriggers;
    laneTriggers.emplace_back(sf::Vector2f(5.0f, 440.0f), sf::Vector2f(430.0f, 30.0f), Lane::D1);
    laneTriggers.emplace_back(sf::Vector2f(5.0f, 480.0f), sf::Vector2f(430.0f, 30.0f), Lane::D2);
    laneTriggers.emplace_back(sf::Vector2f(5.0f, 520.0f), sf::Vector2f(430.0f, 65.0f), Lane::D3);
    laneTriggers.emplace_back(sf::Vector2f(640.0f, 440.0f), sf::Vector2f(435.0f, 65.0f), Lane::C1);
    laneTriggers.emplace_back(sf::Vector2f(640.0f, 520.0f), sf::Vector2f(435.0f, 30.0f), Lane::C2);
    laneTriggers.emplace_back(sf::Vector2f(640.0f, 560.0f), sf::Vector2f(435.0f, 30.0f), Lane::C3);
    laneTriggers.emplace_back(sf::Vector2f(463.0f, 5.0f), sf::Vector2f(71.0f, 410.0f), Lane::A1);
    laneTriggers.emplace_back(sf::Vector2f(544.0f, 5.0f), sf::Vector2f(30.0f, 410.0f), Lane::A2);
    laneTriggers.emplace_back(sf::Vector2f(582.0f, 5.0f), sf::Vector2f(30.0f, 410.0f), Lane::A3);
    laneTriggers.emplace_back(sf::Vector2f(546.0f, 618.0f), sf::Vector2f(70.0f, 455.0f), Lane::B1);
    laneTriggers.emplace_back(sf::Vector2f(465.0f, 618.0f), sf::Vector2f(30.0f, 455.0f), Lane::B2);
    laneTriggers.emplace_back(sf::Vector2f(506.0f, 618.0f), sf::Vector2f(30.0f, 455.0f), Lane::B3);

    std::vector<TrafficControl> trafficControls;
    trafficControls.emplace_back(Light::RED, sf::Vector2f(650.0f, 400.0f), RoadType::A, sf::Vector2f(75.0f, 4.0f), sf::Vector2f(542.0f, 419.0f));
    trafficControls.emplace_back(Light::RED, sf::Vector2f(420.0f, 625.0f), RoadType::B, sf::Vector2f(75.0f, 4.0f), sf::Vector2f(462.0f, 606.0f));
    trafficControls.emplace_back(Light::RED, sf::Vector2f(650.0f, 625.0f), RoadType::C, sf::Vector2f(4.0f, 80.0f), sf::Vector2f(630.0f, 511.0f));
    trafficControls.emplace_back(Light::RED, sf::Vector2f(420.0f, 400.0f), RoadType::D, sf::Vector2f(4.0f, 72.0f), sf::Vector2f(444.0f, 435.0f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();

        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) {
            int id, origin, destination, route;
            float x, y;
            if (packet >> id >> origin >> destination >> route >> x >> y) {
                bool exists = false;
                for (const auto& veh : vehicles) {
                    if (veh->getID() == id) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    auto v = std::make_unique<Vehicle>(id, static_cast<Lane>(origin), static_cast<Lane>(destination), static_cast<Route>(route), 0);
                    v->move(sf::Vector2f(x, y));
                    vehicles.push_back(std::move(v));
                    std::cout << "Received vehicle: " << id << " for lane " << origin << std::endl;
                    if (!hasDequeued[id]) {
                        queues[static_cast<Lane>(origin)].enqueue(*vehicles.back());
                    }
                }
            }
        }

        std::vector<Vehicle> vehicleRefs;
        vehicleRefs.reserve(vehicles.size());
        for (const auto& veh : vehicles) {
            vehicleRefs.push_back(*veh);
        }

        for (size_t i = 0; i < vehicles.size(); ++i) {
            
            bool shouldStop = false;
            for (auto& tc : trafficControls) { 
                sf::FloatRect vehicleBounds = vehicles[i]->getBounds();
                sf::FloatRect stopZone = tc.getBlocker().getGlobalBounds(); 
                if (tc.getLight() == Light::RED && vehicleBounds.intersects(stopZone)) {
                    shouldStop = true;
                    break;
                }
            }
            if (shouldStop) {
                vehicles[i]->stop();
            } else {
                vehicles[i]->resume();
            }

            vehicles[i]->update(deltaTime, vehicleRefs);

            for (size_t j = 0; j < laneTriggers.size(); ++j) {
                Lane lane = laneTriggers[j].getLane();
                if (laneTriggers[j].isVehicleOnLane(*vehicles[i]) && !flags[vehicles[i]->getID()][lane]) {
                    queues[lane].enqueue(*vehicles[i]);
                    flags[vehicles[i]->getID()][lane] = true;
                } else if (!laneTriggers[j].isVehicleOnLane(*vehicles[i]) && flags[vehicles[i]->getID()][lane]) {
                    queues[lane].dequeue();
                    flags[vehicles[i]->getID()][lane] = false;
                }
            }

            bool atDestination = false;
            for (auto& trigger : laneTriggers) { 
                if (trigger.getLane() == vehicles[i]->getDestinationLane() &&
                    trigger.isVehicleOnLane(*vehicles[i])) {
                    atDestination = true;
                    break;
                }
            }

            if (vehicles[i]->hasCompletedRoute() && atDestination) {
                vehicles.erase(vehicles.begin() + i);
                --i;
            }
        }

        if (lightUpdateClock.getElapsedTime().asSeconds() >= lightUpdateInterval) {
            float avgA = (queues[Lane::A2].size() + queues[Lane::A3].size()) / 2.0f;
            float avgB = (queues[Lane::B2].size() + queues[Lane::B3].size()) / 2.0f;
            float avgC = (queues[Lane::C2].size() + queues[Lane::C3].size()) / 2.0f;
            float avgD = (queues[Lane::D2].size() + queues[Lane::D3].size()) / 2.0f;

            if (queues[Lane::A2].size() > 10) {
                a2Priority = true;
            } else if (queues[Lane::A2].size() < 5) {
                a2Priority = false;
            }

            for (auto& tc : trafficControls) {
                tc.setLight(Light::RED);
            }

            RoadType greenRoad;
            float selectedAvg = 0.0f;
            if (a2Priority) {
                greenRoad = RoadType::A;
                selectedAvg = avgA;
            } else {
                lightQueue.sortQueue(avgA, avgB, avgC, avgD, queues[Lane::A2].size());
                greenRoad = lightQueue.dequeue();
                switch (greenRoad) {
                    case RoadType::A:
                        selectedAvg = avgA;
                        break;
                    case RoadType::B:
                        selectedAvg = avgB;
                        break;
                    case RoadType::C:
                        selectedAvg = avgC;
                        break;
                    case RoadType::D:
                        selectedAvg = avgD;
                        break;
                }
            }

            lightUpdateInterval = std::max(1.0f, selectedAvg * 1.0f);

            for (auto& tc : trafficControls) {
                if (tc.getRoad() == RoadType::A && greenRoad == RoadType::A) {
                    tc.setLight(Light::GREEN);
                    break;
                } else if (tc.getRoad() == RoadType::B && greenRoad == RoadType::B) {
                    tc.setLight(Light::GREEN);
                    break;
                } else if (tc.getRoad() == RoadType::C && greenRoad == RoadType::C) {
                    tc.setLight(Light::GREEN);
                    break;
                } else if (tc.getRoad() == RoadType::D && greenRoad == RoadType::D) {
                    tc.setLight(Light::GREEN);
                    break;
                }
            }

            std::cout << "Green light set for Road: " << static_cast<int>(greenRoad) 
                      << " with avg vehicles: " << selectedAvg 
                      << ", new interval: " << lightUpdateInterval << " seconds" << std::endl;
            lightUpdateClock.restart();
        }

        window.clear();
        window.draw(sprite);

        for (auto& trafficControl : trafficControls) {
            trafficControl.draw(window);
        }

        for (auto& laneTrigger : laneTriggers) {
            laneTrigger.draw(window);
        }

        for (auto& vehicle : vehicles) {
            vehicle->draw(window);
        }

        window.display();
    }
}