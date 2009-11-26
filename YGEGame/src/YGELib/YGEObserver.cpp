#include "YGEObserver.h"

namespace YGETimeSpace {


	void YGEObserver::setCameraMatrix(YGEEntity* rootEntity){

		// set default projection matrix
		// @todo make this configurable
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		gluPerspective(45.0f,640.0f/480.0f,0.1f,10000.0f);


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  

		YGEEntity *transformEntity = this;
		while(transformEntity != rootEntity && transformEntity != NULL ){
			YGEMath::Vector3 pos = transformEntity->getPosition();
			YGEMath::Quaternion rot = transformEntity->getOrientation();



			YGEMath::Mat3x3 mat = rot.getConjugate().getRotationMatrix();

			GLfloat m[16] = {	(GLfloat)mat[0][0], (GLfloat)mat[0][1], (GLfloat)mat[0][2], 0.0f,
				(GLfloat)mat[1][0], (GLfloat)mat[1][1], (GLfloat)mat[1][2], 0.0f,
				(GLfloat)mat[2][0], (GLfloat)mat[2][1], (GLfloat)mat[2][2], 0.0f,
				0,				  0,				    0,				    1.0f };

			glMultMatrixf(m);
			glTranslatef(-(GLfloat)pos.x, -(GLfloat)pos.y, -(GLfloat)pos.z);


			transformEntity = transformEntity->getParent();
		}
	}
	void YGEObserver::setCameraMatrixRotation(YGEEntity* rootEntity){

		// set default projection matrix
		// @todo make this configurable
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  

		YGEEntity *transformEntity = this;
		while(transformEntity != rootEntity && transformEntity != NULL ){

			YGEMath::Quaternion rot = transformEntity->getOrientation();

			YGEMath::Mat3x3 mat = rot.getConjugate().getRotationMatrix();

			GLfloat m[16] = {	(GLfloat)mat[0][0], (GLfloat)mat[0][1], (GLfloat)mat[0][2], 0.0f,
				(GLfloat)mat[1][0], (GLfloat)mat[1][1], (GLfloat)mat[1][2], 0.0f,
				(GLfloat)mat[2][0], (GLfloat)mat[2][1], (GLfloat)mat[2][2], 0.0f,
				0,				  0,				    0,				    1.0f };

			glMultMatrixf(m);

			transformEntity = transformEntity->getParent();
		}
	}
}