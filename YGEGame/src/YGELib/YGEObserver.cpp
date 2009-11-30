#include "YGEObserver.h"

namespace YGETimeSpace {

	void YGEObserver::setProjectionMatrix(){
		// set default projection matrix
		switch(cameraMode){
			case CAMERA_PERSPECTIVE:
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();

				gluPerspective(45.0f,640.0f/480.0f,0.1f,1000.0f);


				break;
			case CAMERA_ORTHOGONAL:
				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();

				glOrtho(0.0f,640,480,0.0f,-1.0f,1.0f);


				break;
		}

	}

	YGEObserver::YGEObserver(){
		cameraMode = CAMERA_PERSPECTIVE;
	};
	void YGEObserver::setCameraMatrix(YGEEntity* rootEntity){
		setProjectionMatrix();


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  

		YGEEntity *transformEntity = this;
		while(transformEntity != rootEntity && transformEntity != NULL ){
			YGEMath::Vector3 pos = transformEntity->getPosition();
			YGEMath::Quaternion rot = transformEntity->getOrientation();



			YGEMath::Mat3x3 mat = rot.getConjugate().getRotationMatrix();

			GLfloat m[16] = { (GLfloat)mat[0][0], (GLfloat)mat[1][0], (GLfloat)mat[2][0], 0.0f,
				(GLfloat)mat[0][1], (GLfloat)mat[1][1], (GLfloat)mat[2][1], 0.0f,
				(GLfloat)mat[0][2], (GLfloat)mat[1][2], (GLfloat)mat[2][2], 0.0f,
				0,         0,         0,         1.0f };


			glMultMatrixf(m);
			glTranslatef(-(GLfloat)pos.x, -(GLfloat)pos.y, -(GLfloat)pos.z);


			transformEntity = transformEntity->getParent();
		}
	}
	void YGEObserver::setCameraMatrixRotation(YGEEntity* rootEntity){

		setProjectionMatrix();


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();  

		YGEEntity *transformEntity = this;
		while(transformEntity != rootEntity && transformEntity != NULL ){

			YGEMath::Quaternion rot = transformEntity->getOrientation();

			YGEMath::Mat3x3 mat = rot.getConjugate().getRotationMatrix();

			GLfloat m[16] = { (GLfloat)mat[0][0], (GLfloat)mat[1][0], (GLfloat)mat[2][0], 0.0f,
				(GLfloat)mat[0][1], (GLfloat)mat[1][1], (GLfloat)mat[2][1], 0.0f,
				(GLfloat)mat[0][2], (GLfloat)mat[1][2], (GLfloat)mat[2][2], 0.0f,
				0,         0,         0,         1.0f };

			glMultMatrixf(m);

			transformEntity = transformEntity->getParent();
		}
	}
	void YGEObserver::setCameraMode(int mode){
		cameraMode = mode;
	}

}