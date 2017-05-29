#pragma once

#include "Category.h"
#include "Constants.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>

struct Command;
class CommandQueue;

class SceneNode : public  sf::Transformable, public sf::Drawable,
				  private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
	SceneNode(Category::Type category = Category::None);
	void attachChild(Ptr child);
	Ptr  detachChild(const SceneNode& node);

	void update(sf::Time dt, CommandQueue& commands);

	sf::Vector2f  getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	void onCommand(const Command& command, sf::Time dt); 
	virtual std::size_t getCategory() const;

private:
	virtual void updateCurrent (sf::Time dt, CommandQueue& commands);
			void updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void draw			(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent	(sf::RenderTarget& target, sf::RenderStates states) const;
			void drawChildren	(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
	Category::Type		mDefaultCategory;
};