#include "Unit.h"
#include "DataTable.h"
#include "ResourceHolder.h"
#include "Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
	const std::vector<UnitData> Table(initializeUnitData());
}

Unit::Unit(Type type, const TextureHolder& textures, sf::Vector2i offsetPos)
	: mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, mType(type)
	, mCurrentPosition(offsetPos)
	, mIsSelected(false)
{
	sf::Vector2f offsetCoord = calculateHexOffset(offsetPos.y, offsetPos.x);
	setPosition(offsetCoord);
}

void Unit::setOffsetPosition(sf::Vector2i position)
{
	mCurrentPosition = position;
}

sf::Vector2i Unit::getOffsetPosition()
{
	return mCurrentPosition;
}

void Unit::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Unit::getCategory() const
{
	if (mIsSelected)
		return Category::SelectedUnit;
	else
		return Category::Units;
}

void Unit::setSelectStatus(bool newStatus)
{
	mIsSelected = newStatus;
}

bool Unit::getSelectedStatus()
{
	return mIsSelected;
}
