#include "GameState.h"

#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack &stack, Context context) 
	: State(stack, context)
	, mWorld(*context.window)
	, mPlayer(*context.player)
{
	mPlayer.bindWithWorld(context.window, mWorld.getView(), mWorld.getMap());
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	CommandQueue &commands(mWorld.getCommandQueue());
	mPlayer.handleRealtimeInput(commands);
	return true;
}

bool GameState::handleEvent(const sf::Event &event)
{
	CommandQueue &commands(mWorld.getCommandQueue());
	mPlayer.handleEvent(event, commands);
	return true;
}