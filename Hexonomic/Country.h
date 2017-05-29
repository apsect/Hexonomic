#pragma once

#include <SFML/Graphics/Color.hpp>

#include <set>

class Country
{
public:
	Country(sf::Color countryColor);
	void addCell(int x, int y);
	void removeCell(int x, int y);
	const std::set<std::pair<int, int>>& getOwnCellList() const;
	void setCountryColor(sf::Color color);
	sf::Color getCountryColor() const;

private:
	sf::Color						mCountryColor;
	std::set<std::pair<int, int>>	mOwnCellList;
};
