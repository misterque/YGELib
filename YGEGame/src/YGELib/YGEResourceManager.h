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

#include "YGETexture.h"
#include "YGESound.h"

namespace YGECore {



/**
 *	singleton class for loading and unloading of resources
 */
class YGEResourceManager {

private:

		YGEResourceManager();
		/**
		 * pointer to the singleton
		 */
		static YGEResourceManager* singleton;

		/**
		 * path to the location of resources
		 * by default, this is set to '../media/'
		 * @see setResourceLocation
		 */
		std::string resourceLocation;

		/**
		 * map containing textures associated with their filenames
		 */
		std::map<std::string, YGETexture*> textures;

		/**
		 * map containing sounds associated with their filenames
		 */
		std::map<std::string, YGEAudio::YGESound*> sounds;


		/**
		 * load a sound from a file and stores it
		 * in the map of sounds;
		 * @throws YGEExceptionFileNotFound
		 */
		void loadSound(const char* filename);
public:
	/**
	 * @return singlton instance
	 */
	static YGEResourceManager* getInstance(){
		if(singleton == 0){
			singleton = new YGEResourceManager();
		}
		return singleton;
	}


	/**
	 * helper function which loads an image from a file
	 * at this time the following formats are supported:
	 * - .bmp
	 * @return SDL_Surface pointer containing image data
	 *
	 * @todo implement support for .png, .jpg via SDL_Image
	 *
	 * @throws YGEExceptionMethodNotImplementedYet
	 * @throws YGEExceptionFileNotFound
	 * @deprecated use the method provided by YGETexture 
	 */
	SDL_Surface* getSurface(const char *filename);

	/**
	 * crawls the resource directory/directories
	 * for resources and stores the location of resources
	 * @note not working atm
	 */
	void crawlResources();

	/**
	 * @return the path of a file with appended resource location
	 */
	std::string YGEResourceManager::absoluteFilename(const char* filename);

	/**
	 * set the resource location
	 * @see resourceLocation
	 */
	void setResourceLocation(const char* path);


	/**
	 * looks for already loaded textures in the map of textures
	 * or loads the texture from file
	 * currently supported formats:
	 * - .tex loads a texture as descriped in a .tex file
	 * - .bmp loads a simple texture from a .bmp file
	 * @todo other formats: .png, .jpg
	 *
	 * @throws YGEExceptionMethodNotImplementedYet
	 * @throws YGEExceptionFileNotFound
	 * @return pointer to YGETexture 
	 *	
	 */
	YGETexture* getTexture(const char* filename);


	
	/**
	 * looks for already loaded sounds in the map of sounds
	 * or loads the sounds from file
	 * currently supported formats:

	 * @todo implement this
	 *
	 * @throws YGEExceptionMethodNotImplementedYet
	 * @throws YGEExceptionFileNotFound
	 * @return pointer to YGESound
	 *	
	 */	
	YGEAudio::YGESound* getSound(const char* filename);

};

}



#endif