#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "header/VehicleClass.hpp"
#include "header/LaneTrigger.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1080, 1080}), "simulator");

    sf::Texture texture;
    if(!texture.loadFromFile("assets/map.png"))
    {
        return -1;
    }
    sf::Sprite sprite(texture);
    sf::Clock clock;
    Vehicle vehicle(1, Lane::D2, Lane::C1, Route::MOVE_D_TO_C);
    LaneTrigger laneTrigger(sf::Vector2f(0.0f, 480.0f), sf::Vector2f(450.0f, 30.0f), Lane::D2);

    while (window.isOpen())
    {   sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        vehicle.update(deltaTime);

        if (laneTrigger.isVehicleOnLane(vehicle)) {
            std::cout << "Vehicle is on lane " << static_cast<int>(laneTrigger.getLane()) << std::endl;
        }else{
            std::cout<<"Vehicle is not on lane"<<std::endl;
        }

        window.clear();
        window.draw(sprite);
        laneTrigger.draw(window);
        vehicle.draw(window);
        window.display();
    }
}

