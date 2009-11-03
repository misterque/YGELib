/** @file
 * @author Dirk Fortmeier
 * @date 2.11.2009
 */

#ifndef _YGE_VBO_H_
#define _YGE_VBO_H_

#include "YGEEntityAsset.h"

namespace YGEGraphics {


	struct Vertex {
		YGEMath::Vector3 position;
		YGEMath::Vector2 texCoords;
		double r,g,b,a;
	};

	class Mesh {
		/**
		 * array of vertices, size must be number of
		 * vertices * 3
		 */
		Glfloat* vertices;

		/**
		 *
		 *
		 */
		Glfloat* uv;

		Gluint textureID;

	}

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
