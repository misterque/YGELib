#include "YGEResourceManager.h"
#include "YGEExceptions.h"

#include <sstream>
#include <fstream>
#include <iostream>

namespace YGECore {

	YGEResourceManager::YGEResourceManager(){
		resourceLocation = "../media/";

	}

	SDL_Surface* YGEResourceManager::getSurface(const char *filename){

		std::ostringstream s;
		s << "../media/" << filename;

		SDL_Surface* surface;
		surface = SDL_LoadBMP(s.str().c_str());
		if(surface == NULL){
			throw YGEExceptionFileNotFound(s.str());
		}

		return surface;

	}

	void YGEResourceManager::crawlResources(){

	}

	std::string YGEResourceManager::absoluteFilename(const char* filename) {
		std::ostringstream s;
		s<<resourceLocation<<filename;
		return s.str();
	}
	//void unloadTexture(std::string name);

	YGETexture* YGEResourceManager::getTexture(const char* filename){

		if(textures.find(filename) == textures.end()) {
			YGETexture* texture = new YGETexture ();
			texture->load(absoluteFilename(filename).c_str());
			textures[filename] = texture;
		}

		return (textures.find(filename)->second);

	}

	YGEAudio::YGESound* YGEResourceManager::getSound(const char* filename){

		if(sounds.find(filename) == sounds.end()) {
			YGEAudio::YGESound* sound = new YGEAudio::YGESound ();
			sound->load(absoluteFilename(filename).c_str());
			sounds[filename] = sound;
		}

		return (sounds.find(filename)->second);

	}



	YGEResourceManager* YGEResourceManager::singleton = NULL;


}