#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "header/VehicleClass.hpp"
#include "header/LaneTrigger.hpp"
#include "header/VehicleQueue.hpp"
#include <iostream>
#include <vector>
#include <map>

int main() {
    sf::RenderWindow window(sf::VideoMode({1080, 1080}), "simulator");

    sf::Texture texture;
    if (!texture.loadFromFile("assets/map.png")) {
        return -1;
    }
    sf::Sprite sprite(texture);
    sf::Clock clock;

    std::map<Lane, VehicleQueue> queues;
    queues[Lane::D1] = VehicleQueue();
    queues[Lane::D2] = VehicleQueue();

    std::vector<Vehicle> vehicles;
    vehicles.emplace_back(1, Lane::D1, Lane::C1, Route::MOVE_D_TO_A);
    vehicles.emplace_back(2, Lane::D2, Lane::C2, Route::MOVE_D_TO_C);

    std::vector<LaneTrigger> laneTriggers;
    laneTriggers.emplace_back(sf::Vector2f(0.0f, 440.0f), sf::Vector2f(450.0f, 30.0f), Lane::D1);
    laneTriggers.emplace_back(sf::Vector2f(0.0f, 480.0f), sf::Vector2f(450.0f, 30.0f), Lane::D2);

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
        }

        window.clear();
        window.draw(sprite);

        for (auto& laneTrigger : laneTriggers) {
            laneTrigger.draw(window);
        }

        for (auto& vehicle : vehicles) {
            vehicle.draw(window);
        }

        window.display();
    }

    return 0;
}