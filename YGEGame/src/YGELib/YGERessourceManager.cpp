#include "YGERessourceManager.h"
#include "YGETextureFunctions.h"
#include "YGEExceptions.h"

#include <sstream>
#include <fstream>
#include <iostream>

namespace YGECore {


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

	void YGERessourceManager::loadTexture(std::string filename){
		// first, check if texture is already loaded
		if(textures.find(filename) != textures.end()) {
			return;
		}

		
		std::string filetype = filename.substr(filename.find_first_of(".")+1);


		// then extract the filename of the image
		std::ostringstream s;
		s<<"../media/"<<filename;



		std::string imagefilename;
		bool mipmap = false;

		if(filetype == "tex") {
		std::ifstream is;
		is.open(s.str().c_str());
		if(!is.is_open()) {
			// @todo ERROR handling
			throw YGEExceptionFileNotFound(s.str());
			return;
		}

		//char imagefilename[200];
		//is.getline(imagefilename, 200);


		while(!is.eof()){
			std::string in;
			is>>in;
			if(in == "file:") {
				is>>imagefilename;
			}
			if(in == "genmipmaps") {
				mipmap = true;
			}


		}

		

		std::cout<<imagefilename<<std::endl;
		} else {
			imagefilename = filename;
		}

		// then create a new texture
		Texture newTexture;
		newTexture.filename = filename;
		SDL_Surface* surface =  getSurface(imagefilename.c_str());
		newTexture.textureID = surfaceToTexture2(surface, mipmap);
		newTexture.h = surface->h;
		newTexture.w = surface->w;


		// and add it to the map of textures
		textures[filename] = newTexture;



	}
	//void unloadTexture(std::string name);

	Texture* YGERessourceManager::getTexture(std::string filename){

		if(textures.find(filename) == textures.end()) {
			loadTexture(filename);
		}

		return &(textures.find(filename)->second);
		
	}

	YGERessourceManager* YGERessourceManager::singleton = NULL;

}