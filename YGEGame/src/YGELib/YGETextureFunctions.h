
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
		printf("warning: image.bmp's width is not a power of 2\n");
	}

	// Also check if the height is a power of 2
	if ( (surface->h & (surface->h - 1)) != 0 ) {
		printf("warning: image.bmp's height is not a power of 2\n");
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
		printf("warning: the image is not truecolor..  this will probably break\n number of channels %i \n" , nOfColors);
		// this error should not go unhandled
	}

	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );

	printf("init tex %u", texture);

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