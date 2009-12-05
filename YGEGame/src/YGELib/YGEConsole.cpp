#include "YGEConsole.h"
#include "YGEEngineCore.h"
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include "YGEText.h"

#include <sstream>

using namespace std;

namespace YGECore {



	YGEConsole::YGEConsole(){
		for(int i = 0; i<10; i++){
			output[i].text = "...";
		}
		output[9].text = "Engine up and running";

		currentLine.text = "quit";
		update();
	}

	void YGEConsole::insertKey(SDL_keysym key){


		if (key.unicode > 33 && key.unicode < 300 ){
			std::ostringstream stream;
			stream << currentLine.text << (char)key.unicode;
			currentLine.text = stream.str();
			update();
		} else {

			switch(key.sym) {
			case SDLK_BACKSPACE:
				if(currentLine.text.length() > 0) {
					currentLine.text.erase(currentLine.text.length()-1);
					update();
				}
				break;

			case SDLK_SPACE:
				currentLine.text.append(" ");
				update();
				break;

			case SDLK_RETURN:
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

		glDisable(GL_LIGHTING);
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		glOrtho(0, 640, 0, 480, -1.0f, 1.0f);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		//glTranslatef(0.0f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
		// Finished Drawing The Triangle

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.2f,0.2f,0.2f,0.8f);
		// Set The Color To Blue One Time Only
		glBegin(GL_QUADS);			
		// Draw A Quad
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f(0.0f, 480.0f, 0.0f);					// Top Left

		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 0.0f, 240.0f, 0.0f);					// Top Right

		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 640.0f,240.0f, 0.0f);					// Bottom Right

		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f(640.0f,480.0f, 0.0f);					// Bottom Left
		glEnd();	


		glEnable(GL_TEXTURE_2D);




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
			glVertex3f( (GLfloat)output[i].width , (GLfloat)(480.0f - output[i].height), 0.0f);					// Bottom Right

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f((GLfloat)output[i].width , 480.0f, 0.0f);					// Bottom Left
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

	SDL_Surface* redImage(int w,int h,SDL_Surface* src) 
	{ 
		SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0,0,0,0); 
		SDL_SetColorKey(surface,SDL_SRCCOLORKEY,SDL_MapRGB(surface->format,0,0,0)); 
		SDL_BlitSurface(src,NULL,surface,NULL); 
		SDL_FreeSurface(src); 
		return surface; 
	} 

	void textToConsoleLine(consoleLine* line){

		std::ostringstream stream;

		stream << "> " << line->text;
		SDL_Surface* surface;
		// 
		//surface = SDL_LoadBMP("../media/images/testalpha256x256.bmp");
		//surface = drawtext(VeraMono, 0, 255, 0, 255, 0, 0, 255, 255, stream.str().c_str(), blended);
		// surface = drawtext(VeraMono, 0, 255, 0, 255, 0, 0, 255, 255, stream.str().c_str(), blended);

		//surface = redImage(1024,32,surface);
		SDL_Color c;
		c.r=255;
		c.g=0;
		c.b=255;
		surface = CreateText(stream.str(), YGEGraphics::YGEText::getFont("VeraMono12"), c);
		/*	SDL_Surface* big = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, 1024, 64, surface->format->BitsPerPixel,surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
		SDL_Rect r;
		r.h= surface->h;
		r.w= surface->w;
		r.x= 0;
		r.y= 0;
		int blitresult = SDL_BlitSurface(surface, NULL, big, NULL);
		printf("blit %i", blitresult);*/
		printf("to delete Texute ID: %i \n", line->texture);

		if(line->texture > -1) {
			glDeleteTextures( 1, &line->texture	);
		}
		line->width = surface->w;
		line->height = surface->h;
		line->texture = surfaceToTexture(surface);

		printf("Texute ID: %i \n", line->texture);
		SDL_FreeSurface( surface );
		//		SDL_FreeSurface( big );
	}

	void YGEConsole::update(){

		std::ostringstream stream;

		for(int i = 0; i < 10; i++){
			textToConsoleLine(&output[i]);

		}
		textToConsoleLine(&currentLine);



	}

	void YGEConsole::evaluateCommand(const char* command){
			core->processCommand(command);

	}
}