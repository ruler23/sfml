#ifndef TEXTURECODEX_H
#define TEXTURECODEX_H

#include <iostream>
#include <unordered_map>

class TextureCodex
{
public:
	static std::shared_ptr<sf::Texture> Acquire(const std::string& name)
	{
		const auto i = texturePtrs.find(name);
		if (i != texturePtrs.end())
		{
			return i->second;
		}
		else
		{
			auto pTex = std::make_shared<sf::Texture>();
			pTex->loadFromFile(name);
			texturePtrs.insert({ name,pTex });
			return pTex;
		}
	}

	static void MurderOrphans()
	{
		for (auto i = texturePtrs.begin(); i != texturePtrs.end(); )
		{
			if (i->second.unique())
			{
				i = texturePtrs.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturePtrs;
};

#endif
