#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}