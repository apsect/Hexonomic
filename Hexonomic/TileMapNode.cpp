#include "TileMapNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

TileMapNode::TileMapNode(Level level)
	: mLevel(level)
{
}

void TileMapNode::load(const sf::Texture& tileset, const std::vector<int>& tiles,
						int mapWidth, int mapHeight, sf::Color mapOverlayColor)
{
	mTileset = &tileset;
	mMapWidth = mapWidth;
	mMapHeight = mapHeight;

	mVertices.setPrimitiveType(sf::Triangles);
	mVertices.resize(mapWidth * mapHeight * 3 * (4 * 3));

	for (int i = 0; i < mapHeight; ++i)
		for (int j = 0; j < mapWidth; ++j)
			changeTile(tiles[j + i * mapHeight], i, j, mapOverlayColor);
		
}

void TileMapNode::changeTile(int tile, int x, int y, sf::Color cellOverlayColor)
{
	int tileNumber = tile >> mLevel * 8;
	tileNumber = LEVEL_MASK & tileNumber;
	if (mLevel < 2 && !tileNumber)
		return;

	int tileTextureX = tileNumber % (mTileset->getSize().x / HEX_WIDTH);
	int tileTextureY = tileNumber / (mTileset->getSize().x / HEX_WIDTH);

	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> verticles;
	sf::Vector2f hexOffset(calculateHexOffset(x, y));

	for (int k = 0; k < 6; k++)
	{
		verticles.push_back(std::make_pair(
			sf::Vector2f(HEX_CONTOUR_X[k] + hexOffset.x, HEX_CONTOUR_Y[k] + hexOffset.y),
			sf::Vector2f(
				static_cast<float>(HEX_CONTOUR_X[k] + (tileTextureX * HEX_WIDTH)),
				static_cast<float>(HEX_CONTOUR_Y[k] + (tileTextureY * HEX_HEIGHT)))));
	}

	for (int k = 0; k < 4; k++)
	{
		sf::Vertex* triangle = &mVertices[k * 3 + (x + y * mMapHeight) * (4 * 3)];
		triangle[0].position = verticles[0].first;
		triangle[1].position = verticles[k + 1].first;
		triangle[2].position = verticles[k + 2].first;

		triangle[0].texCoords = verticles[0].second;
		triangle[1].texCoords = verticles[k + 1].second;
		triangle[2].texCoords = verticles[k + 2].second;

		triangle[0].color = cellOverlayColor;
		triangle[1].color = cellOverlayColor;
		triangle[2].color = cellOverlayColor;
	}
}

void TileMapNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = *&mTileset;
	target.draw(mVertices, states);
}

unsigned int TileMapNode::getCategory() const
{
	switch (mLevel) {
		case 0: return Category::Borders;
		case 1: return Category::UpperMap;
		case 2: return Category::LowerMap;
		default: return Category::None;
	}
}
