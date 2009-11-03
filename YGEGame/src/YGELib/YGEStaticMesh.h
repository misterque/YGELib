/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_STATIC_MESH_H_
#define _YGE_STATIC_MESH_H_

#include "YGEGraphicsAsset.h"

namespace YGEGraphics {

/** 
 * static and unanimated mesh object.
 * Mesh data can be loaded from an OBJ file
 * and will be stored in YGEVbo Vertex Buffer
 * Objects for fast drawing.
 */
class YGEStaticMesh : public YGEGraphicsAsset {
private:
	/** 
	 * number of meshes
	 */
	int numMeshes;

	/**
	 * VBO array holding the meshes
	 */
	YGEVbo *meshes;

public:
		virtual void draw(YGEGraphicsContext* context);

		/**
		 * loads mesh data from an OBJ file.
		 */
		void loadFromOBJ(char *filename);

};

}

#endif