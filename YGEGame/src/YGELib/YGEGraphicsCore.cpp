#include "YGEGraphicsCore.h"
#include <SDL_opengl.h>
#include "YGESpace.h"
#include "YGEObserver.h"





namespace YGECore {
	void YGEGraphicsCore::renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer){

			// draw a skybox
			if(space->hasSkybox()){
				observer->setCameraMatrixRotation(space->getRootEntity());

				space->getSkybox()->draw();
			}

			//draw the scene
			observer->setCameraMatrix(space->getRootEntity());
			context.saveAsGlCameraRotation();
			space->getSunlight()->draw();

					glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);

		
		 renderEntity(space->getRootEntity());

	}

	
	void YGEGraphicsCore::renderEntity(YGETimeSpace::YGEEntity* entity){

	
		glEnable(GL_LIGHTING);

		YGEMath::Vector3 pos = entity->getPosition();
		YGEMath::Vector3 scale = entity->getScale();

		glPushMatrix();
		
		glTranslatef(entity->interpolatedPosition.x, entity->interpolatedPosition.y, entity->interpolatedPosition.z);

		YGEMath::Mat3x3 mat = entity->interpolatedOrientation.getRotationMatrix();

		GLfloat m[16] = { (GLfloat)mat[0][0], (GLfloat)mat[1][0], (GLfloat)mat[2][0], 0.0f,
			(GLfloat)mat[0][1], (GLfloat)mat[1][1], (GLfloat)mat[2][1], 0.0f,
			(GLfloat)mat[0][2], (GLfloat)mat[1][2], (GLfloat)mat[2][2], 0.0f,
			0,         0,         0,         1.0f };


		glMultMatrixf(m);

		//glScalef(scale.x, scale.y, scale.z);

		// get every graphical asset and render it
		std::list<YGEGraphics::YGEGraphicsAsset*>* assets = entity->getGraphicsAssets();
		for(std::list<YGEGraphics::YGEGraphicsAsset*>::iterator iter = assets->begin();
			iter != assets->end();
			iter++){



				(*iter)->draw(&context);

		}
		glPopMatrix();
		
		// recursive call on all children
		std::list<YGETimeSpace::YGEEntity*>* children = entity->getChildren();
		for(std::list<YGETimeSpace::YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				 renderEntity(*iter);

		}
}
}