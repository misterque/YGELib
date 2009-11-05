/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_RESSOURCEMANAGER_H_
#define _YGE_RESSOURCEMANAGER_H_

#include <SDL.h> 
#include <SDL_opengl.h>

namespace YGECore {


	class Texture {
		int w, h;
		GLuint textureID;
	};

class YGERessourceManager {

private: 
		static YGERessourceManager* singleton;
public:
	static YGERessourceManager* getInstance(){
		if(singleton == 0){
			singleton = new YGERessourceManager();
		}
		return singleton;
	}

	Texture* getTexture(char *filename);

	SDL_Surface* getSurface(char *filename);

};

}



#endif