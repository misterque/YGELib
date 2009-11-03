#include "YGEHeightmap.h"
//#include "YGE

namespace YGEGraphics {

	void YGEHeightmap::create(char *filename){
		// get texture
		//YGECore::

		mesh = new YGEVbo();

		Mesh* map = new Mesh();

		map->vertices = new GLfloat[3 * 256 * 256];
		map->uv = new GLfloat[ 2 * 256 * 256 ];
		map->indices = new GLuint [ 2 * 3 * 255 * 255 ];
		map->textureID = 0;

		map->numTriangles = 255 * 255 * 2;
		map->numVertices = 256 * 256;

		for(int x = 0; x < 256; x++){
			for(int y = 0; y < 256; y++){
				map->vertices[(x + y*256)*3 + 0] = x;
				map->vertices[(x + y*256)*3 + 1] = -3;
				map->vertices[(x + y*256)*3 + 2] = y;
			}
		}

		for(int x = 0; x < 255; x++){
			for(int y = 0; y < 255; y++){
				map->indices[(x + y*255)*6 + 0] = x +     y*255;
				map->indices[(x + y*255)*6 + 1] = x + 1 + y*255;
				map->indices[(x + y*255)*6 + 2] = x +     (y+1)*255;
				map->indices[(x + y*255)*6 + 3] = x + 1 + y*255;
				map->indices[(x + y*255)*6 + 4] = x + 1 + (y+1)*255;
				map->indices[(x + y*255)*6 + 5] = x +     (y+1)*255;
			}
		}

		mesh->setMesh(map);
		
	}

	void YGEHeightmap::draw(YGEGraphicsContext *context){
		mesh->draw(context);

	}
}