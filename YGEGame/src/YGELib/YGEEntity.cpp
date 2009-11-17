#include <SDL_opengl.h>

#include "YGEEntity.h"
#include <cmath>

#define PI 3.1415926

namespace YGETimeSpace{

	void YGEEntity::render(){

		YGEMath::Vector3 pos = this->getPosition();
		YGEMath::Vector3 scale = this->getScale();

		glPushMatrix();
		glTranslatef((GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z);

		YGEMath::Mat3x3 mat = orientation.getRotationMatrix();

		GLfloat m[16] = { (GLfloat)mat[0][0], (GLfloat)mat[0][1], (GLfloat)mat[0][2], 0.0f,
			(GLfloat)mat[1][0], (GLfloat)mat[1][1], (GLfloat)mat[1][2], 0.0f,
			(GLfloat)mat[2][0], (GLfloat)mat[2][1], (GLfloat)mat[2][2], 0.0f,
			0,         0,         0,         1.0f };

		glMultMatrixf(m);

		//glScalef(scale.x, scale.y, scale.z);

		// get every graphical asset and render it
		std::list<YGEGraphics::YGEGraphicsAsset*> assets = this->getGraphicsAssets();
		for(std::list<YGEGraphics::YGEGraphicsAsset*>::iterator iter = assets.begin();
			iter != assets.end();
			iter++){



				(*iter)->draw(NULL);

		}

		// recursive call on all children
		std::list<YGEEntity*> children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children.begin();
			iter != children.end();
			iter++){
				(*iter)->render();

		}
		glPopMatrix();
	};

	void YGEEntity::addChild( YGEEntity* entity ){

		//@todo check for double insertion

		entity->parent = this;
		children.push_back(entity);

	}

	void YGEEntity::addAsset( YGEEntityAsset* asset ){

		//@todo check for double insertion

		assets.push_back(asset);

		// if it is a graphical asset put it in the list of graphicals
		if(asset->getAssetType() == Graphical) {
			graphicAssets.push_back((YGEGraphics::YGEGraphicsAsset*)asset);
		}

	}


	YGEEntity::YGEEntity(){
		scale.x = 1 ;
		scale.y = 1;
		scale.z = 1;

		assets.clear();
		children.clear();
		parent = NULL;

	}

	void YGEEntity::rotateDGR(const YGEMath::Vector3 axis, double degree){

		rotateRAD(axis, degree * PI / 180.0f);
	}

	void YGEEntity::rotateRAD(const YGEMath::Vector3 axis, double radiant){

		YGEMath::Quaternion q;
		q.w = cos(radiant);
		q.x = axis.x * sin(radiant);
		q.y = axis.y * sin(radiant);
		q.z = axis.z * sin(radiant);

		setOrientation(q * getOrientation());


	}




}