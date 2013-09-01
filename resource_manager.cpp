#include "resource_manager.h"
#include "service_locator.h"
#include "ezolib.h"
#include <fstream>
#include <memory>
#include "collision.h" //for loading textures

bool ResourceManager::loadTexture(const char* filename, const char* tex_name) 
{
    if (Collision::CreateTextureAndBitmask(textures[tex_name], filename))
	{
        servLoc.getLogger()->log(POS, (char*)ezo::string::format("Texture %s loaded properly", tex_name));
        return true;
    }

    //create placeholder with arbitrary size filled with black.
    textures[tex_name].create(100, 100);
    unsigned char* pixels = new unsigned char[100*100*4];
    for(int i = 0; i < 100*100*4; i++)
        pixels[i] = 0x00;
    textures[tex_name].loadFromMemory(pixels, 100*100*4);
    delete[] pixels;

    servLoc.getLogger()->log(POS, (char*)ezo::string::format("Failed to load texture %s!", tex_name),
            LogType::Error, LogOutput::TxtFileAndConsole);
    return false;
}

bool ResourceManager::loadTextures(const char* filename) 
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open())
    {
        servLoc.getLogger()->log(POS, (char*)ezo::string::format("Can't open file %s!!!", filename),
                LogType::Fatal, LogOutput::TxtFileAndConsole);
        return false;
    }

    std::string fname, texname;
    while (!file.eof())
    {
        file >> texname >> fname;
        bool state = loadTexture(fname.c_str(), texname.c_str());
        if (!state)
            return false;
    }
    file.close();
    return true;
}


bool ResourceManager::loadResources(const char* filename) 
{
    std::fstream file;

    //open file
    file.open(filename, std::ios::in);
    if (!file.is_open())
    {
        servLoc.getLogger()->log(POS, (char*)ezo::string::format("Can't open file %s!!!", filename),
                 LogType::Fatal, LogOutput::TxtFileAndConsole);
        return false;
    }

    static char type[80];
    static char path[320];
    while (!file.eof()) 
	{
		memset(type, 0, 80);
        file >> type >> path;
        if (!strcmp(type, "textures:"))
            loadTextures(path);
        else if (!strcmp(type, "images:"))
            loadTextureRects(path);
        else
            return false;
    }
    file.close();
    return true;
}

bool ResourceManager::containsTexture(const std::string& name) 
{ 
	return textures.find(name) != textures.end(); 
}

sf::Texture* ResourceManager::getTexture(const std::string& name)
{ 
	return &textures.find(name)->second; 
}

bool ResourceManager::loadTextureRect(const std::string& name, sf::Texture* tex, sf::IntRect position)
{
	textureRects[name] = TextureRect(tex, position);
	return true;
}

bool ResourceManager::loadTextureRect(const std::string& name, TextureRect textrect)
{
	textureRects[name] = textrect;
	return true;
}

bool ResourceManager::loadTextureRects(const char* filename)
{
	std::fstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        servLoc.getLogger()->log(POS, (char*)ezo::string::format("Can't open file %s!!!", filename),
                LogType::Fatal, LogOutput::TxtFileAndConsole);
        return false;
    }
    std::string name, texname;
	int left, top, width, heigth;
	
    while (!file.eof()) 
	{
        file >> name >> texname >> left >> top >> width >> heigth;
        bool state = loadTextureRect(name, getTexture(texname), sf::IntRect(left, top, width, heigth));
        if (!state)
            return false;
    }
    file.close();
    return true;
}

bool ResourceManager::containsTextureRect(const std::string& name)
{	
	return textureRects.find(name) != textureRects.end(); 	
}

TextureRect ResourceManager::getTextureRect(const std::string& name)
{
	return textureRects.find(name)->second; 
}
