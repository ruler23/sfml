#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "animation.h"

class Character
{
private:
	enum class AnimationIndex
	{
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		StandingUp,
		StandingDown,
		StandingLeft,
		StandingRight,
		Count
	};

public:
	Character(const sf::Vector2f& pos, std::string sprite_set);
	void Draw(sf::RenderTarget& rt) const;
	void SetDirection(const sf::Vector2f& dir);
	void Update(float dt);
	sf::Vector2f getPostion();

private:
	static constexpr float speed = 100.0f;
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	sf::Sprite sprite;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex curAnimation = AnimationIndex::StandingDown;
};

#endif
