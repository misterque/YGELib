#include "YGERessourceManager.h"

#include <sstream>

namespace YGECore {

	Texture* YGERessourceManager::getTexture(char *filename){

		return NULL;
	}

	SDL_Surface* YGERessourceManager::getSurface(char *filename){

		std::ostringstream s;
		s << "../media/images/" << filename;

		SDL_Surface* surface;
		surface = SDL_LoadBMP(s.str().c_str());

		return surface;

	}

YGERessourceManager* YGERessourceManager::singleton = NULL;

}