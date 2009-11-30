/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_RESSOURCEMANAGER_H_
#define _YGE_RESSOURCEMANAGER_H_

#include <SDL.h> 
#include <SDL_opengl.h>
#include <string>
#include <map>

namespace YGECore {


	class Texture {
	public:
		std::string filename;
		int w, h;
		GLuint textureID;

		void bind(){
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		void setRepeat(bool repeat);
	};

class YGERessourceManager {

private: 
		static YGERessourceManager* singleton;

		std::map<std::string, Texture> textures;
public:
	static YGERessourceManager* getInstance(){
		if(singleton == 0){
			singleton = new YGERessourceManager();
		}
		return singleton;
	}



	SDL_Surface* getSurface(const char *filename);

	/**
	 * crawls the ressource directory/directories
	 * for ressources and stores the location of ressources
	 */
	void crawlRessources();


	void loadTexture(std::string filename);
	//void unloadTexture(std::string name);

	Texture* getTexture(std::string filename);

};

}



#endif