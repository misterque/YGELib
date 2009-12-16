/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_STATIC_MESH_H_
#define _YGE_STATIC_MESH_H_

#include "YGEGraphicsAsset.h"
#include "YGEVbo.h"

namespace YGEGraphics {

/** 
 * @brief static and unanimated mesh object.
 *
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

	Mesh model;

public:

	YGEStaticMesh();
	~YGEStaticMesh();

	Mesh* getModel(){
		return &model;
	}
		virtual void draw(YGEGraphicsContext* context);

		/**
		 * @brief loads mesh data from an OBJ file.
		 * @todo this should be managed by the YGECore::YGEResourceManager
		 */
		void loadFromOBJ(const char *filename);

};

}

#endif