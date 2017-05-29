#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

class GameState : public State
{
public:
	GameState(StateStack &stack, Context context);
	void draw();
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event &event);

private:
	World	mWorld;
	Player&	mPlayer;
};