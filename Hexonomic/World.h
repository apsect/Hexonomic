#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "TileMapNode.h"
#include "Map.h"
#include "Unit.h"
#include "CommandQueue.h"
#include "Command.h"
#include "Country.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>

namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
		
	CommandQueue& getCommandQueue();
	sf::View* getView();
	const Map* getMap() const;

private:
	void loadTextures();
	void buildScene();

private:
	enum Layer
	{
		LowerGroundLayer,
		UpperGroundLayer,
		CoutryBorder,
		Units,
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue						mCommandQueue;

	Map									mMap;
};