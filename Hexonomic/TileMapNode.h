#pragma once

#include "Utility.h"
#include "SceneNode.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>

class TileMapNode : public SceneNode
{
public:
	enum Level
	{
		CoutryBorders,
		UpperGroundLevel,
		LowerGroundLevel,
		LayerCount
	};

public:
	TileMapNode(Level level);
	void load(const sf::Texture& tileset, const std::vector<int>& tiles, 
				int mapWidth, int mapHeight, sf::Color mapOverlayColor = sf::Color::White);
	void changeTile(int tile, int x, int y, sf::Color cellOverlayColor = sf::Color::White);
	virtual unsigned int getCategory() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray		mVertices;
	const sf::Texture*	mTileset;
	Level				mLevel;
	int					mMapWidth;
	int					mMapHeight;
};