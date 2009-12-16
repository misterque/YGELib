/**
* @file
* @author Dirk Fortmeier
* @date 27.11.2009
*/

#ifndef _YGE_TEXT_H_
#define _YGE_TEXT_H_

#include "YGEGraphicsAsset.h"
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include <string>
#include <map>




/**
* stolen from http://www.gamedev.net/community/forums/topic.asp?topic_id=422993
*/
SDL_Surface *renderText(std::string text, TTF_Font *font, SDL_Color textColor);

/**
* stolen from http://gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering or somewhere else?
*/
GLuint surfaceToTexture(SDL_Surface *surface);


namespace YGEGraphics {
	/**
	 * @brief text rendering class, mainly used for HUDs and menues
	 */
	class YGEText : public YGEGraphicsAsset {
	private:
		typedef std::map<std::string, TTF_Font*> FontList;
		std::string text;
		static FontList fonts;
		int size;
		bool hasTexture;
		bool hasToBeCreated;
		SDL_Color color;

		float red;
		float green;
		float blue;

		int w;
		int h;

		TTF_Font* font;

		GLuint textureId;

		void createText();


	public:
		YGEText(std::string t);
		YGEText(std::string t, const char* f);

		void setText(std::string t);
		void setFont(const char* f);

		void setColor(float r, float g, float b);

		/**
		 * @brief a font first has to be registered/created to be usable
		 *
		 * for this, a name has to be chosen, a filename to a ttf must be given
		 * and a font size as well.
		 */
		static void registerFont(const char* fontname, const char* filename, int s);

		/**
		 * initialize all font rendering
		 */
		static void init();


		static TTF_Font* getFont(const char* fontname);

		/**
		 * draw the font
		 */
		virtual void draw(YGEGraphicsContext* context);

	};
}


#endif