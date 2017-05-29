#pragma once

#include "Entity.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

class Unit : public Entity
{
public:
	enum Type
	{
		Peasant,
		Archer,
		Pikeman,
		Crossbowman,
		Swordsman,
		TypeCount
	};

public:
	Unit(Type type, const TextureHolder& textures, sf::Vector2i offsetPos);
	void setOffsetPosition(sf::Vector2i position);
	sf::Vector2i getOffsetPosition();
	virtual unsigned int getCategory() const;
	void setSelectStatus(bool newStatus);
	bool getSelectedStatus();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite		mSprite;
	Type			mType;
	sf::Vector2i	mCurrentPosition;
	bool			mIsSelected;
};