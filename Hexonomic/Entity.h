#pragma once

#include "SceneNode.h"

class Entity : public SceneNode
{
public:
private:
	virtual void		updateCurrent(sf::Time dt);
};