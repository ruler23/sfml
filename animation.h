#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, int nFrames, float holdTime, std::string pfad);

	void ApplyToSprite(sf::Sprite& s) const;
	void Update(float dt);
private:
	void Advance();

private:
	float holdTime;
	std::shared_ptr<sf::Texture> pTex;
	std::vector<sf::IntRect> frames;
	int iFrame = 0;
	float time = 0.0f;
};

#endif
