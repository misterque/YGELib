#include "YGEResourceManager.h"
#include "YGELogger.h"
#include "YGETextureFunctions.h"
#include "YGEExceptions.h"



/**
 * stolen from http://gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering or somewhere else?
 *
 */
GLuint surfaceToTexture2(SDL_Surface *surface, bool mipmap){


	GLuint texture;			// This is a handle to our texture object
	GLenum texture_format;
	GLint  nOfColors;


	// Check that the image's width is a power of 2
	if ( (surface->w & (surface->w - 1)) != 0 ) {
		//@todo error handling
	}

	// Also check if the height is a power of 2
	if ( (surface->h & (surface->h - 1)) != 0 ) {
		//@todo error handling
	}

	// get the number of channels in the SDL surface
	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nOfColors == 3)     // no alpha channel
	{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		//@todo error handling
	}

	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );


	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );

	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		if(mipmap) {
			gluBuild2DMipmaps(GL_TEXTURE_2D, nOfColors, surface->w, surface->h, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		} else {

			glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels );

		}


	return texture;
}


namespace YGECore{

	void YGETexture ::setRepeat(bool repeat){

		glBindTexture(GL_TEXTURE_2D, textureID);
		if(repeat) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		} else {

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		}
	}


	void YGETexture ::load(const char* filename){

		hasMipMaps = false;

		this->filename = filename;

		imagefilename = filename;

		std::string filestring(filename);

		std::string filetype = filestring.substr(filestring.find_first_of(".", 2)+1);

		if(filetype == "tex") {
			parseTexFile(filename);
		}



		SDL_Surface* surface =  getSurface(imagefilename.c_str());
		textureID = surfaceToTexture2(surface, hasMipMaps);
		h = surface->h;
		w = surface->w;




	}

	void YGETexture ::parseTexFile(const char* filename){

		std::ifstream is;
		is.open(filename);
		if(!is.is_open()) {
			throw YGEExceptionFileNotFound(filename);
			return;
		}

		while(!is.eof()){
			std::string in;
			is>>in;
			if(in == "file:") {
				is>>imagefilename;
				imagefilename = YGECore::YGEResourceManager::getInstance()->absoluteFilename(imagefilename.c_str());
			}
			if(in == "genmipmaps") {
				hasMipMaps = true;
				debugout(".. mipmaps will be generated");
			}


		}
	}


	SDL_Surface* YGETexture ::getSurface(const char *filename){

		SDL_Surface* surface;
		surface = SDL_LoadBMP(filename);
		if(surface == NULL){
			throw YGEExceptionFileNotFound(filename);
		}

		return surface;

	}

}