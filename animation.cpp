#include "animation.h"
#include "texturecodex.h"

Animation::Animation(int x, int y, int width, int height, int nFrames, float holdTime, std::string pfad )
		: holdTime(holdTime)
{
	frames.reserve(nFrames);
	//pTex = TextureCodex::Acquire("resources/professor_walk_cycle_no_hat.png");
	pTex = TextureCodex::Acquire(pfad);
	for (int i = 0; i < nFrames; i++)
	{
		frames.emplace_back(sf::Vector2i{ x,y }, sf::Vector2i{ width,height });
		x += width;
	}
}

void Animation::ApplyToSprite(sf::Sprite& s) const
{
	s.setTexture(*pTex);
	s.setTextureRect(frames[iFrame]);
}

void Animation::Update(float dt)
{
	time += dt;
	while (time >= holdTime)
	{
		time -= holdTime;
		Advance();
	}
}

void Animation::Advance()
{
	if (++iFrame >= int(frames.size()))
	{
		iFrame = 0;
	}
}
