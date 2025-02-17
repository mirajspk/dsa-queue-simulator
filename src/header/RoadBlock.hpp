#ifndef ROAD_BLOCK_HPP
#define ROAD_BLOCK_HPP

#include <SFML/Graphics.hpp>

class RoadBlock {
    private:
        sf::Vector2f position;
        sf::Vector2f size;
    public:
        RoadBlock(sf::Vector2f position, sf::Vector2f size);
};

#endif