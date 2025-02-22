#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "header/VehicleClass.hpp"
#include "header/LaneTrigger.hpp"
#include "header/VehicleQueue.hpp"
#include <iostream>
#include <vector>
#include <map>
#include "header/TrafficControl.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1080, 1080}), "simulator");

    sf::Texture texture;
    if (!texture.loadFromFile("assets/map.png")) {
        return -1;
    }
    sf::Sprite sprite(texture);
    sf::Clock clock;

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

    std::vector<Vehicle> vehicles;
    vehicles.emplace_back(1, Lane::D2, Lane::C1, Route::MOVE_D_TO_C);
    vehicles.emplace_back(2, Lane::D2, Lane::B1, Route::MOVE_D_TO_B);
    vehicles.emplace_back(3, Lane::D3, Lane::C1, Route::MOVE_D_TO_A);

    vehicles.emplace_back(4, Lane::A2, Lane::B1, Route::MOVE_A_TO_B);
    vehicles.emplace_back(5, Lane::A2, Lane::D1, Route::MOVE_A_TO_D);
    vehicles.emplace_back(6, Lane::A3, Lane::C1, Route::MOVE_A_TO_C);

    vehicles.emplace_back(7, Lane::C2, Lane::B1, Route::MOVE_C_TO_B);
    vehicles.emplace_back(8, Lane::C2, Lane::A1, Route::MOVE_C_TO_A);
    vehicles.emplace_back(9, Lane::C3, Lane::D1, Route::MOVE_C_TO_D);

    vehicles.emplace_back(10, Lane::B2, Lane::A1, Route::MOVE_B_TO_A);
    vehicles.emplace_back(11, Lane::B2, Lane::C1, Route::MOVE_B_TO_C);
    vehicles.emplace_back(12, Lane::B3, Lane::D1, Route::MOVE_B_TO_D);

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

    std::vector <TrafficControl> trafficControls;
    trafficControls.emplace_back(Light::RED, sf::Vector2f(650.0f, 625.0f), RoadType::A, sf::Vector2f(75.0f,4.0f), sf::Vector2f(542.0f,419.0f));
    trafficControls.emplace_back(Light::RED, sf::Vector2f(420.0f, 400.0f), RoadType::B,sf::Vector2f(75.0f,4.0f), sf::Vector2f(462.0f,606.0f));
    trafficControls.emplace_back(Light::RED, sf::Vector2f(420.0f, 625.0f), RoadType::C, sf::Vector2f(4.0f,80.0f), sf::Vector2f(630.0f,511.0f));
    trafficControls.emplace_back(Light::GREEN, sf::Vector2f(650.0f, 400.0f), RoadType::D, sf::Vector2f(4.0f,72.0f), sf::Vector2f(444.0f,435.0f));

    std::map<int, std::map<Lane, bool>> flags;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
    
        for (size_t i = 0; i < vehicles.size(); ++i) {
            vehicles[i].update(deltaTime);
    
            for (size_t j = 0; j < laneTriggers.size(); ++j) {
                Lane lane = laneTriggers[j].getLane();
                if (laneTriggers[j].isVehicleOnLane(vehicles[i]) && !flags[vehicles[i].getID()][lane]) {
                    std::cout << "Enqueue " << vehicles[i].getID() << " to " << static_cast<int>(lane) << std::endl;
                    queues[lane].enqueue(vehicles[i]);
                    std::cout << "Queue size for lane " << static_cast<int>(lane) << ": " << queues[lane].size() << std::endl;
                    flags[vehicles[i].getID()][lane] = true;
                } else if (!laneTriggers[j].isVehicleOnLane(vehicles[i]) && flags[vehicles[i].getID()][lane]) {
                    queues[lane].dequeue();
                    std::cout << "Dequeue " << vehicles[i].getID() << " from " << static_cast<int>(lane) << std::endl;
                    std::cout << "Queue size for lane " << static_cast<int>(lane) << ": " << queues[lane].size() << std::endl;
                    flags[vehicles[i].getID()][lane] = false;
                }
            }
    
            bool stopped = false;
            for (auto& trafficControl : trafficControls) {
                if (vehicles[i].getBounds().intersects(trafficControl.getBlocker().getGlobalBounds())&& trafficControl.isRed()) {
                    vehicles[i].stop();
                    stopped = true;
                }
            }
    
            if (!stopped) {
                vehicles[i].resume();
            }
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
            vehicle.draw(window);
        }
    
        window.display();
    }
}