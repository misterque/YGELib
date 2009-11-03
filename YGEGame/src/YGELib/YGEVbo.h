/** @file
* @author Dirk Fortmeier
* @date 2.11.2009
*/

#ifndef _YGE_VBO_H_
#define _YGE_VBO_H_

#include "YGEEntityAsset.h"
#include <SDL_opengl.h>

namespace YGEGraphics {


	/**
	 * holds mesh information
	 */
	class Mesh {
	public:
		/**
		* array of vertices, size must be number of
		* vertices * 3
		*/
		GLfloat* vertices;

		/**
		*
		*
		*/

		GLfloat* uv;

		/**
		 * texture ID
		 * @todo add multitexturing
		 */
		GLuint textureID;

	};

	class YGEVbo {

	private:
		GLuint vboId;

		Mesh *mesh;

		bool uptodate;

	public:
		YGEVbo();

		virtual void draw(YGEGraphicsContext* context);

		void fillBuffers();

		void setMesh(Mesh *m){
			mesh = m;
			uptodate = false;
		}



	};

}
#endif
