#include "DataTable.h"
#include "Unit.h"

std::vector<UnitData> initializeUnitData()
{
	std::vector<UnitData> data(Unit::TypeCount);

	data[Unit::Peasant].texture = Textures::Units;
	data[Unit::Peasant].textureRect = sf::IntRect(0, 0, 72, 72);

	data[Unit::Archer].texture = Textures::Units;
	data[Unit::Archer].textureRect = sf::IntRect(72, 0, 72, 72);

	data[Unit::Pikeman].texture = Textures::Units;
	data[Unit::Pikeman].textureRect = sf::IntRect(144, 0, 72, 72);

	data[Unit::Crossbowman].texture = Textures::Units;
	data[Unit::Crossbowman].textureRect = sf::IntRect(216, 0, 72, 72);

	data[Unit::Swordsman].texture = Textures::Units;
	data[Unit::Swordsman].textureRect = sf::IntRect(288, 0, 72, 72);

	return data;
}
