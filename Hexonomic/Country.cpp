#include "Country.h"

Country::Country(sf::Color countryColor)
	: mCountryColor(countryColor)
{
}

void Country::addCell(int x, int y)
{
	mOwnCellList.insert(std::make_pair(x, y));
}

void Country::removeCell(int x, int y)
{
	mOwnCellList.erase(std::make_pair(x, y));
}

const std::set<std::pair<int, int>>& Country::getOwnCellList() const
{
	return mOwnCellList;
}

void Country::setCountryColor(sf::Color color)
{
	mCountryColor = color;
}

sf::Color Country::getCountryColor() const
{
	return mCountryColor;
}
