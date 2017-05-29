#pragma once

#include "Constants.h"

sf::Vector2f calculateHexOffset(int vertHex, int horHex);
sf::Vector2i pixelToHex(int x, int y, int offsetX = 0, int offsetY = 0);
bool checkNeighbor(sf::Vector2i destenation, sf::Vector2i current);