#include "Map.h"

#include <SFML/System/Vector2.hpp>

#include <cassert>
#include <iostream>

Map::Map(int mapWidth, int mapHeight)
	: mMapWidth(mapWidth)
	, mMapHeight(mapHeight)
{
	int size = mapWidth * mapHeight;
	mCellMap.reserve(size);
	std::vector<int> lowerTypeProb{ 45, 30, 20, 5 };
	std::vector<std::vector<int>> upperTypeProb{ { 100 },
												 { 30, 15, 18, 10, 2, 5, 5, 10, 5},
												 { 20, 10, 30, 30, 0, 0, 2, 5, 3},
												 { 100 } };
	for (int i = 0, cellType, upperCellType; i < size; ++i)
	{
		cellType = generateItegerWithProbability(lowerTypeProb);
		upperCellType = generateItegerWithProbability(upperTypeProb[cellType]);
		cellType <<= 8;
		cellType += upperCellType;
		cellType <<= 8;
		mCellMap.push_back(cellType);
	}
}

int Map::getMapWidth() const
{
	return mMapWidth;
}

int Map::getMapHeight() const
{
	return mMapHeight;
}

int Map::getCellType(int x, int y) const
{
	return mCellMap[x + y * mMapHeight];
}

const std::vector<int>& Map::getMap() const
{
	return mCellMap;
}

int Map::generateItegerWithProbability(const std::vector<int>& probabilityList)
{
	int checkListValid = 0;
	for (int item : probabilityList)
		checkListValid += item;
	assert(checkListValid == 100);

	int randNum = rand() % 100, returnValue = 0;
	sf::Vector2i limit;
	for (auto iter = probabilityList.begin(); iter != probabilityList.end(); 
		++iter, ++returnValue, limit.x = limit.y)
	{
		limit.y += *iter;
		if (randNum >= limit.x && randNum < limit.y)
			return returnValue;
	}
	return -1;
}
