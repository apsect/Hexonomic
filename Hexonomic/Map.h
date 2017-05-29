#pragma once

#include <vector>

class Map
{
public:
	Map(int mapWidth, int mapHeight);
	int getMapWidth() const;
	int getMapHeight() const;
	int getCellType(int x, int y) const;
	const std::vector<int>& getMap() const;

private:
	int generateItegerWithProbability(const std::vector<int>& probabilityList);

private:
	std::vector<int>	mCellMap;
	int					mMapWidth;
	int					mMapHeight;
};
