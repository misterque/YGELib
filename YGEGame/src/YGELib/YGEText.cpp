#include "YGEText.h"
#include "YGEExceptions.h"


using namespace std;

//Your constant ColorKey colors
const int COLORKEY_RED = 0xFF;
const int COLORKEY_GREEN = 0x00;
const int COLORKEY_BLUE = 0xFF;


/**
* stolen from http://www.gamedev.net/community/forums/topic.asp?topic_id=422993
*/
SDL_Surface *CreateText(std::string text, TTF_Font *font, SDL_Color textColor)
{
	//Make text as normal...
	SDL_Surface* TextSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	SDL_Surface *NewSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 1024, 32, 32, 
		0xFF000000, 0x00FF0000, 0x0000FF00, 0);

	//Create a rectangle for coloring the empty image
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = NewSurface->w;
	rect.h = NewSurface->h;

	//Fill the new image with your colorkey color
	//  SDL_FillRect(NewSurface, &rect, SDL_MapRGB(NewSurface->format, COLORKEY_RED, COLORKEY_GREEN, COLORKEY_BLUE));

	//Place your text onto the new surface
	SDL_BlitSurface(TextSurface, NULL, NewSurface, &rect);

	//Free the old surface
	SDL_FreeSurface(TextSurface);

	//Set the colorkey on the empty surface to make the COLORKEY_ color clear
	//  Uint32 colorkey = SDL_MapRGB(NewSurface->format, COLORKEY_RED, COLORKEY_GREEN, COLORKEY_BLUE);
	//    SDL_SetColorKey(NewSurface, SDL_RLEACCEL|SDL_SRCCOLORKEY, colorkey);

	//Return your new surface, with dimensions of a power of two.
	return NewSurface;
}


/**
* stolen from http://gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering or somewhere else?
*/
GLuint surfaceToTexture(SDL_Surface *surface){


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

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
		texture_format, GL_UNSIGNED_BYTE, surface->pixels );


	return texture;
}


namespace YGEGraphics {

	YGEText::YGEText(std::string t) : hasTexture(false), hasToBeCreated(true){
		setFont("VeraMono12");
		setText(t);


		color.r=255;
		color.g=255;
		color.b=255;

		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;

	}

	YGEText::YGEText(std::string t, const char* f):hasTexture(false), hasToBeCreated(true){
		setFont(f);
		setText(t);

		color.r=255;
		color.g=255;
		color.b=255;

		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;
	}

	void YGEText::createText(){
		if(hasTexture){
			hasTexture = false;
			glDeleteTextures(1, &textureId);
		}

		SDL_Surface* surface = CreateText(
			text,
			font,
			color
			);
		textureId = surfaceToTexture(surface);

		w = surface->w;
		h = surface->h;

		SDL_FreeSurface(surface);
		hasTexture = true;
		hasToBeCreated = false;

	}
	void YGEText::setText(std::string t){
		text = t;
		//@todo free texture if hasTexture
		hasToBeCreated = true;

	}
	void YGEText::setFont(const char* f){
		font = getFont(f);
	}

	void YGEText::setColor(float r, float g, float b){
		red = r;
		green = g;
		blue = b;
	}

	void YGEText::registerFont(const char* fontname, const char* filename, int s){
		TTF_Font* font;
		font = TTF_OpenFont(filename, s);
		if (font == NULL){
			YGEExceptionFileNotFound(std::string(TTF_GetError()));

		}
		fonts[fontname] = font;
	}


	void YGEText::init(){
		registerFont("VeraMono12", "../media/fonts/VeraMono.ttf", 12);
	}

	TTF_Font* YGEText::getFont(const char* fontname){
		if(fonts.empty()) {
			init();
		}
		if(fonts.find(fontname) == fonts.end()) {
			return fonts.begin()->second;
		} else {
			return fonts.find(fontname)->second;
		}
		//return NULL;
	}


	void YGEText::draw(YGEGraphicsContext* context){
		if(hasToBeCreated){
			createText();
		}
		if(!this->enabled) return;
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor3f(red, green, blue);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0,0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(0,h);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(w,h);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(w,0);
		glEnd();



	}

	YGEText::FontList YGEText::fonts = YGEText::FontList();

}