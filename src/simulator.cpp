#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "header/VehicleClass.hpp"

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

    while (window.isOpen())
    {   sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        vehicle.update(deltaTime);
        window.clear();
        window.draw(sprite);
        vehicle.draw(window);
        window.display();
    }
}