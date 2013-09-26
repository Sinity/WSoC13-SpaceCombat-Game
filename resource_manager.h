#pragma once
#include <map>
#include "textureRect.h"
#include "object.h"
#include <SFML/Audio.hpp>

class ResourceManager : public ezo::Object
{
public:
    sf::Texture* getTexture(const std::string& name);
    bool containsTexture(const std::string& name);

    TextureRect getTextureRect(const std::string& name);
    bool containsTextureRect(const std::string& name);

    sf::SoundBuffer* getSound(const std::string& name);
    bool containsSound(const std::string& name);

    bool loadResources(const char* filename);

    bool loadTexture(const char* filename, const char* tex_name);
    bool loadTextures(const char* filename);

    bool loadSound(const char* filename, const char *soundName);
    bool loadSounds(const char* filename);

    bool loadTextureRects(const char* filename);
    bool loadTextureRect(const std::string& name, sf::Texture* atlas, sf::IntRect position);
    bool loadTextureRect(const std::string& name, TextureRect textrect);

private:
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, TextureRect> textureRects;
  std::map<std::string, sf::SoundBuffer> sounds;
};
