#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mMap(20, 20)
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	mSceneGraph.update(dt, mCommandQueue);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

sf::View* World::getView()
{
	return &mWorldView;
}

const Map* World::getMap() const
{
	return &mMap;
}

void World::loadTextures()
{
	mTextures.load(Textures::LowerGround, "assets/lowerGround.png");
	mTextures.load(Textures::UpperGround, "assets/upperGround.png");
	mTextures.load(Textures::Borders, "assets/border.png");
	mTextures.load(Textures::Units, "assets/units1.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture &lowerTexture(mTextures.get(Textures::LowerGround));
	std::unique_ptr<TileMapNode> lowerMap(new TileMapNode(TileMapNode::LowerGroundLevel));
	lowerMap->load(lowerTexture, mMap.getMap(), mMap.getMapWidth(), mMap.getMapHeight());
	mSceneLayers[LowerGroundLayer]->attachChild(std::move(lowerMap));

	sf::Texture &upperTexture(mTextures.get(Textures::UpperGround));
	std::unique_ptr<TileMapNode> upperMap(new TileMapNode(TileMapNode::UpperGroundLevel));
	upperMap->load(upperTexture, mMap.getMap(), mMap.getMapWidth(), mMap.getMapHeight());
	mSceneLayers[UpperGroundLayer]->attachChild(std::move(upperMap));

	std::vector<int> bordersType(mMap.getMapWidth() * mMap.getMapHeight(), 0);
	//bordersType[0] = 30;
	sf::Texture &bordersTexture(mTextures.get(Textures::Borders));
	std::unique_ptr<TileMapNode> bordersMap(new TileMapNode(TileMapNode::CoutryBorders));
	bordersMap->load(bordersTexture, bordersType, mMap.getMapWidth(), mMap.getMapHeight());
	mSceneLayers[CoutryBorder]->attachChild(std::move(bordersMap));

	std::unique_ptr<Unit> player(new Unit(Unit::Peasant, mTextures, sf::Vector2i(8, 8)));
	mSceneLayers[Units]->attachChild(std::move(player));

	std::unique_ptr<Unit> player1(new Unit(Unit::Pikeman, mTextures, sf::Vector2i(9, 9)));
	mSceneLayers[Units]->attachChild(std::move(player1));

	std::unique_ptr<Unit> player2(new Unit(Unit::Crossbowman, mTextures, sf::Vector2i(10, 10)));
	mSceneLayers[Units]->attachChild(std::move(player2));
}