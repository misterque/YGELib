#include "YGEConsole.h"
#include "YGEEngineCore.h"
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include "YGEText.h"

#include <sstream>

using namespace std;

namespace YGECore {

	/**
	 * @brief helper function for creating a texture for a console line
	 */
	void textToConsoleLine(consoleLine* line){

		std::ostringstream stream;

		stream << "> " << line->text;
		SDL_Surface* surface;

		SDL_Color c;
		c.r=255;
		c.g=0;
		c.b=255;
		surface = renderText(stream.str(), YGEGraphics::YGEText::getFont("VeraMono12"), c);

		if(line->texture > -1) {
			glDeleteTextures( 1, &line->texture	);
		}
		line->width = surface->w;
		line->height = surface->h;
		line->texture = surfaceToTexture(surface);

		SDL_FreeSurface( surface );

	}

	YGEConsole::YGEConsole(){
		for(int i = 0; i<10; i++){
			output[i].text = "...";
		}
		output[9].text = "Engine up and running";

		currentLine.text = "quit";
		inited = false;
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
					textToConsoleLine(&currentLine);
				}
				break;

			case SDLK_SPACE:
				currentLine.text.append(" ");
				textToConsoleLine(&currentLine);
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
		if(!inited) {
			inited = true;
			update();
		}

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

	}

	void YGEConsole::println(const char* line){
		for(int i = 0; i<9; i++){
			output[i] = output[i+1];
		}
		output[9].text = line;

		update();
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