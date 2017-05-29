#pragma once

#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

class Unit;

struct UnitData
{
	Textures::ID			texture;
	sf::IntRect			textureRect;
};

std::vector<UnitData>	initializeUnitData();