#include "character.h"

Character::Character(const sf::Vector2f& pos, std::string sprite_set)
		: pos(pos)
{
	animations[(int)AnimationIndex::WalkingUp] = Animation(64, 0, 64, 64, 8, 0.1f, sprite_set);
	animations[(int)AnimationIndex::WalkingLeft] = Animation(64, 64, 64, 64, 8, 0.1f, sprite_set);
	animations[(int)AnimationIndex::WalkingDown] = Animation(64, 128, 64, 64, 8, 0.1f, sprite_set);
	animations[(int)AnimationIndex::WalkingRight] = Animation(64, 192, 64, 64, 8, 0.1f, sprite_set);
	animations[(int)AnimationIndex::StandingUp] = Animation(0, 0, 64, 64, 1, 10.1f, sprite_set);
	animations[(int)AnimationIndex::StandingLeft] = Animation(0, 64, 64, 64, 1, 10.1f, sprite_set);
	animations[(int)AnimationIndex::StandingDown] = Animation(0, 128, 64, 64, 1, 10.1f, sprite_set);
	animations[(int)AnimationIndex::StandingRight] = Animation(0, 192, 64, 64, 1, 10.1f, sprite_set);
}

void Character::Draw(sf::RenderTarget& rt) const
{
	rt.draw(sprite);
}

void Character::SetDirection(const sf::Vector2f& dir)
{
	if (dir.x > 0.0f)
	{
		curAnimation = AnimationIndex::WalkingRight;
	}
	else if (dir.x < 0.0f)
	{
		curAnimation = AnimationIndex::WalkingLeft;
	}
	else if (dir.y < 0.0f)
	{
		curAnimation = AnimationIndex::WalkingUp;
	}
	else if (dir.y > 0.0f)
	{
		curAnimation = AnimationIndex::WalkingDown;
	}
	else
	{
		if (vel.x > 0.0f)
		{
			curAnimation = AnimationIndex::StandingRight;
		}
		else if (vel.x < 0.0f)
		{
			curAnimation = AnimationIndex::StandingLeft;
		}
		else if (vel.y < 0.0f)
		{
			curAnimation = AnimationIndex::StandingUp;
		}
		else if (vel.y > 0.0f)
		{
			curAnimation = AnimationIndex::StandingDown;
		}
	}
	vel = dir * speed;
}

void Character::Update(float dt)
{
	pos += vel * dt;
	animations[int(curAnimation)].Update(dt);
	animations[int(curAnimation)].ApplyToSprite(sprite);
	sprite.setPosition(pos);
}

sf::Vector2f Character::getPostion()
{
	return sprite.getPosition();
}
