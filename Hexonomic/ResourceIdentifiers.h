#pragma once

namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID 
	{
		LowerGround,
		UpperGround, 
		Borders,
		Units,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;