#pragma once

#include "Command.h"
#include "Map.h"
#include "Country.h"

#include <SFML/Window/Event.hpp>

#include <map>
#include <memory>

class CommandQueue;
namespace sf
{
	class RenderWindow;
	class View;
}

class Player
{
public:
	Player();

	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	void bindWithWorld(sf::RenderWindow* window, sf::View* view, const Map* map); 

private:
	int						mZoomFactor;
	sf::Vector2i			mScrollMapStep;
	sf::RenderWindow*		mWindow;
	sf::View*				mWorldView;
	const Map*				mMap;
	std::unique_ptr<bool>	mIsUnitSelected;
	Country					mPlayerCountry;
	bool					mAddCell;
};