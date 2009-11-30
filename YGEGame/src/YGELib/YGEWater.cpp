#include <SDL_opengl.h>

#include "YGEWater.h"

namespace YGEGraphics {


	bool YGEWater::allLessThan(YGEHeightmap* hmap, int x, int y, int w, int h, double waterheight){
		for(int X = x; X < x+w; X++) {
			for(int Y = y; Y < y+h; Y++){
				if(hmap->getZ(X,Y) > waterheight){
					return false;
				}
			}
		}
		return true;

	}

	bool YGEWater::buildMeshRecursive(YGEHeightmap* hmap, int x, int y, int w, int h, double waterheight){
	
		if(	allLessThan(hmap, x, y, w, h,waterheight)){
			
			Vertex v1(x - hmap->getH() / 2 ,waterheight,y  - hmap->getW() / 2 );
			Vertex v2(x+w  - hmap->getH() / 2 ,waterheight,y  - hmap->getW() / 2 );
			Vertex v3(x  - hmap->getH() / 2 ,waterheight,y+h - hmap->getW() / 2 );
			
			Vertex v4(x+w  - hmap->getH() / 2 ,waterheight,y - hmap->getW() / 2 );
			Vertex v5(x+w  - hmap->getH() / 2 ,waterheight,y+h - hmap->getW() / 2 );
			Vertex v6(x - hmap->getH() / 2 ,waterheight,y+h - hmap->getW() / 2 );

			v1.u = x;
			v1.v = y;
			v2.u = x+w;
			v2.v = y;
			v3.u = x;
			v3.v = y+h;
			v4.u = x+w;
			v4.v = y;
			v5.u = x+w;
			v5.v = y+h;
			v6.u = x;
			v6.v = y+h;
			
			
			v1.nx = 0.0f;
			v1.ny = 1.0f;
			v1.nz = 0.0f;
			v2.nx = 0.0f;
			v2.ny = 1.0f;
			v2.nz = 0.0f;
			v3.nx = 0.0f;
			v3.ny = 1.0f;
			v3.nz = 0.0f;
			v4.nx = 0.0f;
			v4.ny = 1.0f;
			v4.nz = 0.0f;
			v5.nx = 0.0f;
			v5.ny = 1.0f;
			v5.nz = 0.0f;
			v6.nx = 0.0f;
			v6.ny = 1.0f;
			v6.nz = 0.0f;

			
			map->addVertex(v1);
			v1 = map->vertexList.back();
			map->addVertex(v2);
			v2 = map->vertexList.back();
			map->addVertex(v3);
			v3 = map->vertexList.back();
			map->addVertex(v4);
			v4 = map->vertexList.back();
			map->addVertex(v5);
			v5 = map->vertexList.back();
			map->addVertex(v6);
			v6 = map->vertexList.back();

			Triangle t1(v1.index, v2.index, v3.index);
			Triangle t2(v4.index, v5.index, v6.index);
			map->addTriangle(t1);
			map->addTriangle(t2);

		} else {
			buildMeshRecursive(hmap, x, y, w/2, h/2, waterheight);
			buildMeshRecursive(hmap, x + w/2, y, w/2, h/2, waterheight);
			buildMeshRecursive(hmap, x + w/2, y+h/2, w/2, h/2, waterheight);
			buildMeshRecursive(hmap, x, y + h/2, w/2, h/2, waterheight);



		}
		return true;
	}


	YGEWater::YGEWater(YGEHeightmap* hmap, double h){

		texture = YGECore::YGERessourceManager::getInstance()->getTexture("textures/water.tex");

		mesh = new YGEVbo();

		map = new Mesh();
		map->textureID = texture->textureID;

		buildMeshRecursive(hmap, 0, 0, hmap->getW(), hmap->getH(), h);

		map->fillArrays();
		mesh->setMesh(map);


	}


	void YGEWater::draw(YGEGraphicsContext* context){

		mesh->draw(context);
/*
				glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		texture->bind();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(2000.0f, 2000.0f);
			glVertex3d(10000.0f, 10.0f, 10000.0f);

			glTexCoord2f(0.0f, 2000.0f);
			glVertex3d(-10000.0f, 10.0f, 10000.0f);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3d(-10000.0f, 10.0f, -10000.0f);

			glTexCoord2f(2000.0f, 0.0f);
			glVertex3d(10000.0f, 10.0f, -10000.0f);
			glEnd();
*/
	}

}