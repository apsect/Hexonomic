#include "Utility.h"

#include <cmath>

sf::Vector2f calculateHexOffset(int vertHex, int horHex)
{
	return sf::Vector2f(static_cast<float>(horHex * HEX_SIDE),
		static_cast<float>(HEX_HEIGHT * (2 * vertHex + (horHex % 2)) / 2));
}

sf::Vector2i pixelToHex(int x, int y, int offsetX, int offsetY)
{
	x += offsetX;
	y += offsetY;

	int mainCoordsX = (int)floor((float) x / HEX_SIDE);
	int localCoordsX = x - (int) HEX_SIDE * mainCoordsX;

	int baseCellOffset = y - (mainCoordsX % 2) * (int) HEX_HEIGHT / 2;
	int mainCoordsY = (int) floor((float) baseCellOffset / HEX_HEIGHT);
	int localCoordsY = baseCellOffset - (int) HEX_HEIGHT * mainCoordsY;

	if (localCoordsX > abs(HEX_RADIUS / 2 - HEX_RADIUS * localCoordsY / HEX_HEIGHT))
		return sf::Vector2i(mainCoordsX, mainCoordsY);
	else
		return sf::Vector2i(mainCoordsX - 1, mainCoordsY + (mainCoordsX % 2) -
		(localCoordsY < HEX_HEIGHT / 2));
}

bool checkNeighbor(sf::Vector2i destenation, sf::Vector2i current)
{
	int columnParity = destenation.x % 2;
	for (int i = 0; i < 6; ++i)
	{
		sf::Vector2i neighbor = DIRECTION[columnParity][i];
		if ((destenation.x + neighbor.x) == current.x &&
			(destenation.y + neighbor.y) == current.y)
			return true;
	}
	return false;
}