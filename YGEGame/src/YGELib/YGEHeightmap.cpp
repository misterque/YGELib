#include "YGEHeightmap.h"
#include "YGERessourceManager.h"
#include "YGELogger.h"

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
			YGECore::YGERessourceManager::getInstance()->getSurface("hmap.bmp");

		int w = surface->w;
		int h = surface->h;
		mesh = new YGEVbo();

		Mesh* map = new Mesh();

		map->vertices = new GLfloat[3 * w * h];
		map->uv = new GLfloat[ 2 * w * h ];
		map->indices = new GLuint [ 2 * 3 * (w-1) * (h-1) ];
		map->textureID = 0;

		map->numTriangles = (w-1) * (h-1) * 2;
		map->numVertices = w * h;

//		map->textureID = (YGECore::YGERessourceManager::getInstance()->getTexture("mud.bmp"))->textureID;

		SDL_LockSurface(surface);
		for(int x = 0; x < w; x++){
			for(int y = 0; y < h; y++){
				map->vertices[(x + y*w)*3 + 0] = x;
				
				Uint8 height;
				SDL_GetRGB(getpixel(surface, x, y), surface->format, &height, &height, &height);
				//YGECore::YGELogger::getInstance()->log(h);
				
				map->vertices[(x + y*w)*3 + 1] =  (float)height;
				map->vertices[(x + y*w)*3 + 2] = y;
			}
		}
		SDL_UnlockSurface(surface);

		for(int x = 0; x < (w-1); x++){
			for(int y = 0; y < (h-1); y++){
				map->indices[(x + y*(w-1))*6 + 0] = x +     y*w;
				map->indices[(x + y*(w-1))*6 + 1] = x + 1 + y*w;
				map->indices[(x + y*(w-1))*6 + 2] = x +     (y+1)*w;
				map->indices[(x + y*(w-1))*6 + 3] = x + 1 + y*w;
				map->indices[(x + y*(w-1))*6 + 4] = x + 1 + (y+1)*w;
				map->indices[(x + y*(w-1))*6 + 5] = x +     (y+1)*w;
			}
		}

		mesh->setMesh(map);
		
	}

	void YGEHeightmap::draw(YGEGraphicsContext *context){
		mesh->draw(context);

	}
}