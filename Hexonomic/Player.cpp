#include "Player.h"
#include "CommandQueue.h"
#include "Unit.h"
#include "TileMapNode.h"
#include "Map.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

struct UnitMover
{
	UnitMover(int x, int y, int ground)
		: destenation(x, y)
		, groundType(ground)
	{
	}

	void operator() (Unit& unit, sf::Time) const
	{
		sf::Vector2f offsetCoord = calculateHexOffset(destenation.y, destenation.x);
		int columnParity = destenation.x % 2;
		if (checkNeighbor(destenation, unit.getOffsetPosition()) &&
			groundType != 0)
		{
			unit.setPosition(offsetCoord);
			unit.setOffsetPosition(destenation);
		}
	}

	sf::Vector2i destenation;
	int groundType;
};

struct UnitSelecter
{
	UnitSelecter(int x, int y, bool* statChanger)
		: selectedCell(x, y)
		, statusChanger(statChanger)
	{
	}

	void operator() (Unit& unit, sf::Time) const
	{
		if (unit.getOffsetPosition() == selectedCell)
		{
			unit.setSelectStatus(true);
			*statusChanger = true;
		}
	}

	sf::Vector2i selectedCell;
	bool* statusChanger;
};

struct TerritoryGetter
{
	TerritoryGetter(int x, int y, int ground, sf::Color color)
		: destenation(x, y)
		, groundType(ground)
		, cellColor(color)
	{
	}

	void operator() (TileMapNode& map, sf::Time) const
	{
		map.changeTile(1, destenation.y, destenation.x, cellColor);
	}

	sf::Vector2i destenation;
	int groundType;
	sf::Color cellColor;
};

Player::Player() 
	: mZoomFactor(0)
	, mWindow(nullptr)
	, mWorldView(nullptr)
	, mMap(nullptr)
	, mIsUnitSelected(new bool(false))
	, mPlayerCountry(sf::Color::Red)
	, mAddCell(true)
{
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code) {
			case sf::Keyboard::Num1: mPlayerCountry.setCountryColor(sf::Color::Black); break;
			case sf::Keyboard::Num2: mPlayerCountry.setCountryColor(sf::Color::Blue); break;
			case sf::Keyboard::Num3: mPlayerCountry.setCountryColor(sf::Color::Cyan); break;
			case sf::Keyboard::Num4: mPlayerCountry.setCountryColor(sf::Color::Green); break;
			case sf::Keyboard::Num5: mPlayerCountry.setCountryColor(sf::Color::Magenta); break;
			case sf::Keyboard::Num6: mPlayerCountry.setCountryColor(sf::Color::Red); break;
			case sf::Keyboard::Num7: mPlayerCountry.setCountryColor(sf::Color::White); break;
			case sf::Keyboard::Num8: mPlayerCountry.setCountryColor(sf::Color::Yellow); break;
			case sf::Keyboard::Space:
			{
				Command out;
				out.category = Category::SelectedUnit;
				out.action = derivedAction<Unit>([](Unit &unit, sf::Time)
				{
					unit.setSelectStatus(false);
				});
				commands.push(out);
				*mIsUnitSelected = false;
				break;
			}

			case sf::Keyboard::Return:
				mAddCell = !mAddCell;
				break;
		}
	}

	if (event.type == sf::Event::MouseButtonPressed &&
		event.key.code == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*mWindow);
		sf::Vector2f globalPosition = mWindow->mapPixelToCoords(mousePosition, *mWorldView);
		auto coords = pixelToHex(globalPosition.x, globalPosition.y);

		if (*mIsUnitSelected)
		{
			Command out;
			out.category = Category::SelectedUnit;
			out.action = derivedAction<Unit>(UnitMover(coords.x, coords.y,
				mMap->getCellType(coords.x, coords.y)));
			commands.push(out);
		}
		else
		{
			Command out;
			out.category = Category::Units;
			out.action = derivedAction<Unit>(
				UnitSelecter(coords.x, coords.y, mIsUnitSelected.get()));
			commands.push(out);
		}

		if (mMap->getCellType(coords.x, coords.y) >> (8 * 2))
		{
			Command out;
			out.category = Category::Borders;

			if (mAddCell)
			{
				out.action = derivedAction<TileMapNode>(TerritoryGetter(coords.x, coords.y,
					mMap->getCellType(coords.x, coords.y), mPlayerCountry.getCountryColor()));
				commands.push(out);

				mPlayerCountry.addCell(coords.x, coords.y);
			}
			else
			{
				out.action = derivedAction<TileMapNode>(TerritoryGetter(coords.x, coords.y,
					mMap->getCellType(coords.x, coords.y), sf::Color::Transparent));
				commands.push(out);

				mPlayerCountry.removeCell(coords.x, coords.y);
			}

			for (std::pair<int, int> cell : mPlayerCountry.getOwnCellList())
				std::cout << cell.first << ' ' << cell.second << " ||| ";
			std::cout << std::endl;
		}
	}

	if (event.type == sf::Event::MouseWheelMoved)
	{
		if (event.mouseWheel.delta &&
			(mZoomFactor + event.mouseWheel.delta) < 5 &&
			(mZoomFactor + event.mouseWheel.delta) > -5)
		{
			if (event.mouseWheel.delta > 0)
			{
				if (mWorldView != nullptr)
					mWorldView->zoom(1.f/0.9f);
				++mZoomFactor;
			}
			else
			{
				if (mWorldView != nullptr)
					mWorldView->zoom(0.9f);
				--mZoomFactor;
			}
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition();

		if (mScrollMapStep == sf::Vector2i())
			mScrollMapStep = mousePosition;

		sf::Vector2f offset(mousePosition - mScrollMapStep);
		if (offset != sf::Vector2f())
		{
			if (mWorldView != nullptr)
				mWorldView->move(-offset.x, -offset.y);
			mScrollMapStep = mousePosition;
			//std::cout << buff.x << ' ' << buff.y << ' '  << scrollMapStep.x << ' ' << scrollMapStep.y << std::endl;
		}
	}
	else if (mScrollMapStep != sf::Vector2i())
	{
		mScrollMapStep = sf::Vector2i();
	}
}

void Player::bindWithWorld(sf::RenderWindow* window, sf::View* view, const Map* map)
{
	mWindow = window;
	mWorldView = view;
	mMap = map;
}