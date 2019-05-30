#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include<SFML/Graphics.hpp>
#include <string>
#include <map>

enum class TextureNames : char
{
	BACKGROUND = 0,
	GROUND = 1,
	MAN = 2,
	SOURCES = 3,
	ICON = 4
};

class TextureManager
{

private:

	std::map<TextureNames, sf::Texture*> textures;

public:

	void loadTexture(const TextureNames& texture, const std::string& filename);

	sf::Texture* getRef(const TextureNames& texture);


	TextureManager();
	~TextureManager();
};

#endif //TEXTURE_MANAGER_HPP