/**
* @file
* @author Dirk Fortmeier
* @date 1.12.2009
*/

#ifndef _YGE_TEXTURE_H_
#define _YGE_TEXTURE_H_

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL.h> 
#include <SDL_opengl.h>

namespace YGECore{
	class YGEResourceManager;
}

namespace YGECore {
	/**
	 * @brief texture object
	 *
	 * use the YGECore::YGEResourceManager to load a texture
	 */
	class YGETexture {
	private:
		friend class YGECore::YGEResourceManager;

		/**
		* load a texture from a file
		* @param filename path relative to application
		*        executable
		* @throws YGEExceptionFileNotFound
		* @throws YGEExceptionMethodNotImplementedYet
		*/
		void load(const char* filename);

		void parseTexFile(const char* filename);


		bool hasMipMaps;

		std::string imagefilename;

	public:


		std::string filename;
		int w, h;
		GLuint textureID;

		/**
		 * @brief bind a texture to the opengl context
		 */
		void bind(){
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		/**
		 * sometimes a texture needs to be repeatable (terrain), sometimes not (skymap)
		 */
		void setRepeat(bool repeat);

		/**
		* helper method which loads an image from a file
		* at this time the following formats are supported:
		* - .bmp
		* @return SDL_Surface pointer containing image data
		*
		* @todo implement support for .png, .jpg via SDL_Image
		*
		* @throws YGEExceptionMethodNotImplementedYet
		* @throws YGEExceptionFileNotFound
		*/
		static SDL_Surface* getSurface(const char *filename);

	};

}

#endif