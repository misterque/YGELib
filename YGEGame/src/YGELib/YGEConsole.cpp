#include "YGEConsole.h"
#include "YGEEngineCore.h"
#include <SDL_ttf.h>
#include <SDL_opengl.h>

#include <sstream>


TTF_Font* VeraMono;

/**
* stolen from http://gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering
*/
TTF_Font* loadfont(char* file, int ptsize)
{
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL){
		printf("Unable to load font: %s %s \n", file, TTF_GetError());
		SDL_Delay(1000);
		// Handle the error here.
	}
	return tmpfont;
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


/**
* stolen from http://gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering
*/
enum textquality {solid, shaded, blended};

/**
* stolen from http://gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering
*/
SDL_Surface *drawtext(TTF_Font *fonttodraw, char fgR, char fgG, char fgB, char fgA, 
					  char bgR, char bgG, char bgB, char bgA, const char* text, textquality quality)
{
	SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
	SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
	SDL_Surface *resulting_text;

	if (quality == solid) resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
	else if (quality == shaded) resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
	else if (quality == blended) resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);

	return resulting_text;
}

namespace YGECore {



	YGEConsole::YGEConsole(){
		for(int i = 0; i<10; i++){
			output[i].text = ">";
		}
		output[9].text = "YGE up and running";

		currentLine.text = "bla";
		VeraMono = loadfont("../media/fonts/VeraMono.ttf", 12);
		update();
	}

	void YGEConsole::insertKey(SDL_keysym key){

		println((char*)&key.unicode);

		if (key.unicode > 33 && key.unicode < 300 ){
			std::ostringstream stream;
			stream << currentLine.text << (char)key.unicode;
			printf("%i",key.unicode);
			currentLine.text = stream.str();
			update();
		} else {

			switch(key.sym) {
			case SDLK_BACKSPACE:
				println("erase");
				if(currentLine.text.length() > 0) {
				currentLine.text.erase(currentLine.text.length()-1);
				update();
				}
				break;
			
			case SDLK_RETURN:
				println("return");
				if(currentLine.text.length() > 0) {
					println(currentLine.text.c_str());
					evaluateCommand(currentLine.text.c_str());
					currentLine.text = "";
				update();
				}
				break;
			}

		}

	}


	void YGEConsole::draw(){

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		glOrtho(0, 640, 0, 480, -1.0f, 1.0f);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		//glTranslatef(0.0f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
		// Finished Drawing The Triangle
		glColor3f(0.2f,0.2f,0.2f);	
		glDisable(GL_TEXTURE_2D);
		// Set The Color To Blue One Time Only
		glBegin(GL_QUADS);			
		// Draw A Quad
		glTexCoord2i( 0.0f, 0.0f );
		glVertex3f(0.0f, 480.0f, 0.0f);					// Top Left

		glTexCoord2i( 0.0f, 1.0f );
		glVertex3f( 0.0f, 240.0f, 0.0f);					// Top Right

		glTexCoord2i( 1.0f, 1.0f );
		glVertex3f( 640.0f,240.0f, 0.0f);					// Bottom Right

		glTexCoord2i( 1.0f, 0.0f );
		glVertex3f(640.0f,480.0f, 0.0f);					// Bottom Left
		glEnd();	


		glEnable(GL_TEXTURE_2D);


		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		for(int i=0; i<11; i++){
			if(i < 10) {
				glBindTexture(GL_TEXTURE_2D, output[i].texture);
			} else {

				glBindTexture(GL_TEXTURE_2D, currentLine.texture);
			}

			glColor3f(1.0f,1.0f,1.0f);							// Set The Color To Blue One Time Only
			glBegin(GL_QUADS);			
			// Draw A Quad
			glTexCoord2f( 0.0f, 0.0f );
			glVertex3f(0.0f, 480.0f, 0.0f);					// Top Left

			glTexCoord2f( 0.0f, 1.0f );
			glVertex3f( 0.0f, 480.0f - output[i].height, 0.0f);					// Top Right

			glTexCoord2f( 1.0f,1.0f );
			glVertex3f( output[i].width , 480.0f - output[i].height, 0.0f);					// Bottom Right

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f(output[i].width , 480.0f, 0.0f);					// Bottom Left
			glEnd();
			glTranslatef(0.0f, -15.0f, 0.0f);
		}



	}




	void YGEConsole::init(YGEEngineCore *core){

		this->core = core;
		update();

	}

	void YGEConsole::println(const char* line){
		for(int i = 0; i<9; i++){
			output[i] = output[i+1];
		}
		output[9].text = line;

		update();
	}


	void textToConsoleLine(consoleLine* line){

		std::ostringstream stream;

		stream << "> " << line->text;
		SDL_Surface* surface;
		surface = drawtext(VeraMono, 0, 255, 0, 255, 0, 0, 255, 255, stream.str().c_str(), blended);
		glDeleteTextures( 1, &line->texture	);
		line->width = surface->w;
		line->height = surface->h;
		line->texture = surfaceToTexture(surface);

		SDL_FreeSurface( surface );
	}

	void YGEConsole::update(){

		std::ostringstream stream;

		for(int i = 0; i < 10; i++){
			textToConsoleLine(&output[i]);

		}
		textToConsoleLine(&currentLine);



	}

	void YGEConsole::evaluateCommand(const char* command){
		if(std::string(command) == "quit") {
			core->shutdown();
		}

	}
}