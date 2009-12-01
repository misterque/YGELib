#include "YGERessourceManager.h"
#include "YGEExceptions.h"

#include <sstream>
#include <fstream>
#include <iostream>

namespace YGECore {

	YGERessourceManager::YGERessourceManager(){
		ressourceLocation = "../media/";

	}

	SDL_Surface* YGERessourceManager::getSurface(const char *filename){

		std::ostringstream s;
		s << "../media/" << filename;

		SDL_Surface* surface;
		surface = SDL_LoadBMP(s.str().c_str());
		if(surface == NULL){
			throw YGEExceptionFileNotFound(s.str());
		}

		return surface;

	}

	void YGERessourceManager::crawlRessources(){

	}

	std::string YGERessourceManager::absoluteFilename(const char* filename) {
		std::ostringstream s;
		s<<ressourceLocation<<filename;
		return s.str();
	}
	//void unloadTexture(std::string name);

	Texture* YGERessourceManager::getTexture(const char* filename){

		if(textures.find(filename) == textures.end()) {
			Texture* texture = new Texture();
			texture->load(absoluteFilename(filename).c_str());
			textures[filename] = texture;
		}

		return (textures.find(filename)->second);
		
	}

	YGERessourceManager* YGERessourceManager::singleton = NULL;


}