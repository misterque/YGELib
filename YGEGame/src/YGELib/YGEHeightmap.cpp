#include "YGEHeightmap.h"
#include "YGEResourceManager.h"
#include "YGELogger.h"

#include "YGESpace.h"

#include "YGEPhysics.h"

/* 
* Return the pixel value at (x, y) 
* NOTE: The surface must be locked before calling this! 
*/ 
Uint32 getpixel(SDL_Surface *surface, int x, int y) 
{ 
	int bpp = surface->format->BytesPerPixel; 
	
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp; 

	switch(bpp) { 
	case 1: 
		return *p; 

	case 2: 
		return *(Uint16 *)p; 

	case 3: 
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
			return p[0] << 16 | p[1] << 8 | p[2]; 
		else 
			return p[0] | p[1] << 8 | p[2] << 16; 

	case 4: 
		return *(Uint32 *)p; 

	default: 
		return 0; 
	} 
}


namespace YGEGraphics {

	void YGEHeightmap::create(const char *filename, const char* texturefilename, double width, double depth, double height){



		// get texture
		SDL_Surface* surface = 
			YGECore::YGEResourceManager::getInstance()->getSurface(filename);

		w = surface->w;
		h = surface->h;

		scalex = width / w;
		scalez = depth / h;
		scaley = height / 256.0f;

		texture = YGECore::YGEResourceManager::getInstance()->getTexture( texturefilename);

		mesh = new YGEVbo();

		Mesh* map = new Mesh();

		map->textureID = texture->textureID;


		//		map->textureID = (YGECore::YGEResourceManager::getInstance()->getTexture("mud.bmp"))->textureID;
		pHeightData = new double[w*h];

		SDL_LockSurface(surface);
		for(int x = 0; x < w; x++){
			for(int y = 0; y < h; y++){

				Uint8 height;
				SDL_GetRGB(getpixel(surface, x, y), surface->format, &height, &height, &height);
				pHeightData[x + (y * w)] = (float)height * scaley;
				Vertex v;
				
				v.x = GLfloat(x - w/2) * (float)scalex;
				v.z = GLfloat(y - h/2) * (float)scalez;
				v.y = (float)height * (float)scaley;
				v.u = x  / 20.0f;
				v.v = y  / 20.0f;

				/// create a border
				if(x == 0) {
					v.y = 0;
				}
				if(x == w-1) {
					v.y = 0;

				}
				if(y == 0) {
					v.y = 0;

				}
				if(y == h-1) {
					v.y = 0;

				}



				map->addVertex(v);
			}
		}
		for(int x = 0; x < w; x++){
			for(int y = 0; y < h; y++){
				if(x>0 && y>0 && x<w-1 && y<h-1){
					double b1 = pHeightData[(x-1) + (y * w)] - map->vertexList[(x * h) + (y)].y;
					b1 /= sqrt(b1*b1 + 1);

					double b2 = pHeightData[(x+1) + (y * w)] - map->vertexList[(x * h) + (y)].y;
					b2 /= sqrt(b2*b2 + 1);

					double a1 = pHeightData[(x) + ((y-1) * w)] - map->vertexList[(x * h) + (y)].y;
					a1 /= sqrt(a1*a1 + 1);
					
					double a2 = pHeightData[(x) + ((y+1) * w)] - map->vertexList[(x * h) + (y)].y;
					a2 /= sqrt(a2*a2 + 1);

					GLfloat nx = GLfloat(b1 - b2);
					GLfloat nz = GLfloat(a1 - a2);

					GLfloat length = sqrt(nx*nx + 1*1 + nz*nz);
					map->vertexList[(x * h) + (y)].nx = nx / length;
					map->vertexList[(x * h) + (y)].ny = 1.0f / length;
					map->vertexList[(x * h) + (y)].nz = nz / length;
				} else {
					map->vertexList[(x * h) + (y)].nx = 0.0f;
					map->vertexList[(x * h) + (y)].ny = 1.0f;
					map->vertexList[(x * h) + (y)].nz = 0.0f;
				}
			}
		}
		SDL_UnlockSurface(surface);

		for(int x = 0; x < (w-1); x++){
			for(int y = 0; y < (h-1); y++){

				Triangle t;
				t.a = x +     y*w;
				t.b = x + 1 + y*w;
				t.c = x +     (y+1)*w;
				map->addTriangle(t);
				t.a = x + 1 + y*w;
				t.b = x + 1 + (y+1)*w;
				t.c = x +     (y+1)*w;
				map->addTriangle(t);

			}
		}

		map->fillArrays();
		mesh->setMesh(map);

	}

	void YGEHeightmap::draw(YGEGraphicsContext *context){

		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1.0f, 1.0f, 1.0f);
		mesh->draw(context);

		glBegin(GL_QUADS);
		glNormal3d(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10000, 0, -10000);
		glTexCoord2f(0.0f, 500.0f); glVertex3f(-10000, 0, 10000);
		glTexCoord2f(500.0f, 500.0f); glVertex3f(10000, 0, 10000);
		glTexCoord2f(500.0f, 0.0f); glVertex3f(10000, 0, -10000);
		glEnd();
	
	}

	void YGEHeightmap::makeSolid(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();
		if(parentSpace != NULL){



			//@todo check if space has time not enabled




			heightfieldId = dGeomHeightfieldDataCreate ();
			dGeomHeightfieldDataBuildDouble (heightfieldId,
				pHeightData,
				true,
				w * scalex, h * scalez,
				w, h,
				1, 0, 5, 0);

			dGeomID geom = dCreateHeightfield( parentSpace->getDSpaceId(), heightfieldId, false);
			dGeomSetCategoryBits(geom,YGEPhysics::STATIC_OBJECTS );
			dGeomSetCollideBits(geom, YGEPhysics::ENTITIES );

			geom = dCreatePlane(parentSpace->getDSpaceId(),0,1,0,0);
			dGeomSetCategoryBits(geom,YGEPhysics::STATIC_OBJECTS );
			dGeomSetCollideBits(geom, YGEPhysics::ENTITIES );


		}
	}
	double YGEHeightmap::getZ(int x, int y){
		return pHeightData[(x) + ((y+1) * w)];
	}

}