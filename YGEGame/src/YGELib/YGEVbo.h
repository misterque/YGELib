/** @file
* @author Dirk Fortmeier
* @date 2.11.2009
*/

#ifndef _YGE_VBO_H_
#define _YGE_VBO_H_

#include "YGEEntityAsset.h"


#include <SDL_opengl.h>
#include <list>
#include <vector>

#include "YGEPrimitives.h"

namespace YGEGraphics {


	class YGEVbo {

	private:
		GLuint vboId;
		GLuint iboId;

		Mesh *mesh;

		bool uptodate;

	public:
		YGEVbo();
		~YGEVbo();

		virtual void draw(YGEGraphicsContext* context);

		void fillBuffers();

		void setMesh(Mesh *m){
			mesh = m;
			uptodate = false;
		}

		Mesh* getMesh() {
			return mesh;
		}



	};

}
#endif
