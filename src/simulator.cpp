#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "header/VehicleClass.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1500, 1500}), "simulator");

    sf::Texture texture;
    if(!texture.loadFromFile("assets/map.png"))
    {
        return -1;
    }
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {   sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        Vehicle vehicle(1, Lane::B3, Lane::D1, Route::MOVE_B_TO_D, sf::Vector2f(750, 750));
        vehicle.draw(window);
        window.display();
    }
}