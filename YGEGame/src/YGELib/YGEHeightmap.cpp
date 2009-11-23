#include "YGEHeightmap.h"
#include "YGERessourceManager.h"
#include "YGELogger.h"

#include "YGESpace.h"

/* 
 * Return the pixel value at (x, y) 
 * NOTE: The surface must be locked before calling this! 
 */ 
Uint32 getpixel(SDL_Surface *surface, int x, int y) 
{ 
    int bpp = surface->format->BytesPerPixel; 
    /* Here p is the address to the pixel we want to retrieve */ 
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
        return 0;       /* shouldn't happen, but avoids warnings */ 
    } 
}


namespace YGEGraphics {

	void YGEHeightmap::create(char *filename){


		// get texture
		SDL_Surface* surface = 
			YGECore::YGERessourceManager::getInstance()->getSurface(filename);

		w = surface->w;
		h = surface->h;

		texture = YGECore::YGERessourceManager::getInstance()->getTexture("textures/mud.tex");

		mesh = new YGEVbo();

		Mesh* map = new Mesh();

		map->textureID = texture->textureID;


//		map->textureID = (YGECore::YGERessourceManager::getInstance()->getTexture("mud.bmp"))->textureID;
		pHeightData = new double[w*h];

		SDL_LockSurface(surface);
		for(int x = 0; x < w; x++){
			for(int y = 0; y < h; y++){

				Uint8 height;
				SDL_GetRGB(getpixel(surface, x, y), surface->format, &height, &height, &height);
				pHeightData[x + (y * w)] = height;
				Vertex v;
				v.x = GLfloat(x);
				v.z = GLfloat(y);
				v.y = (float)height / 5.0f;
				v.u = x  / 20.0f;
				v.v = y  / 20.0f;

				map->addVertex(v);
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
		mesh->draw(context);

	}

	void YGEHeightmap::makeSolid(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();
		if(parentSpace != NULL){



//@todo check if space has time not enabled
heightfieldId = dGeomHeightfieldDataCreate ();
dGeomHeightfieldDataBuildDouble (heightfieldId,
                                      pHeightData,
                                      true,
                                      w, h,
                                      w, h,
                                      1, 0, 5, 0);

dGeomID geom = dCreateHeightfield( parentSpace->getDSpaceId(), heightfieldId, false);
			//dGeomSetBody(geom, bodyId);
		}
	}
}