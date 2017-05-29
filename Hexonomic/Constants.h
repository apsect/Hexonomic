#pragma once

#include <SFML/System/Vector2.hpp>

const sf::Vector2u WINDOWS_SIZE(820, 640);
const sf::Vector2i DIRECTION[2][6] =
{
	{
		sf::Vector2i(+1, 0), sf::Vector2i(+1, -1), sf::Vector2i(0, -1),
		sf::Vector2i(-1, -1), sf::Vector2i(-1, 0), sf::Vector2i(0, +1)
	},
	{
		sf::Vector2i(+1, +1), sf::Vector2i(+1, 0), sf::Vector2i(0, -1),
		sf::Vector2i(-1, 0), sf::Vector2i(-1, +1), sf::Vector2i(0, +1)
	}
};

const int HEX_RADIUS = 36;
const int HEX_WIDTH = 2 * HEX_RADIUS;
const int HEX_HEIGHT = 2 * HEX_RADIUS;
const int HEX_SIDE = HEX_RADIUS * 3 / 2;

const int HEX_CONTOUR_X[] = { HEX_RADIUS / 2, HEX_SIDE, HEX_WIDTH, HEX_SIDE, HEX_RADIUS / 2, 0 };
const int HEX_CONTOUR_Y[] = { 0, 0, HEX_HEIGHT / 2, HEX_HEIGHT, HEX_HEIGHT, HEX_HEIGHT / 2 };

const int LEVEL_MASK = 255;
