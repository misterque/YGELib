/** @file
* @author Dirk Fortmeier
* @date 4.11.2009
*/

#ifndef _YGE_OBSERVER_H_
#define _YGE_OBSERVER_H_

#include "YGEEntityAsset.h"
#include "YGEEntity.h"
#include <SDL_opengl.h>

namespace YGETimeSpace {


	/**
	* Observer class.
	* Observers are thrown into a world of entities
	* and are able to.. observe it. Meaning they perceive
	* the enitites through their assets by different senses.
	* These senses are vision (consider the observer as a camera)
	* or hearing (...).
	* An observer itself is an entity.
	*/
	class YGEObserver : public YGEEntity {

	public:
		void setCameraMatrix(YGEEntity* rootEntity){

			YGEEntity *transformEntity = this;
			while(transformEntity != rootEntity && transformEntity != NULL ){
				YGEMath::Vector3 pos = transformEntity->getPosition();
				YGEMath::Quaternion rot = transformEntity->getOrientation();



				YGEMath::Mat3x3 mat = rot.getConjugate().getRotationMatrix();

				float m[16] = { mat[0][0], mat[0][1], mat[0][2], 0.0f,
								mat[1][0], mat[1][1], mat[1][2], 0.0f,
								mat[2][0], mat[2][1], mat[2][2], 0.0f,
								0,         0,         0,         1.0f };

				glMultMatrixf(m);
				glTranslatef(-pos.x, -pos.y, -pos.z);


				transformEntity = transformEntity->getParent();
			}
		}


	};

}

#endif