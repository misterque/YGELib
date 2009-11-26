#include "YGESkybox.h"

namespace YGEGraphics {

	void YGESkybox::loadTextures(){
		up   = YGECore::YGERessourceManager::getInstance()->getTexture("skymaps/waterscape_positive_y.bmp");
		down = YGECore::YGERessourceManager::getInstance()->getTexture("skymaps/waterscape_negative_y.bmp");
		right  = YGECore::YGERessourceManager::getInstance()->getTexture("skymaps/waterscape_positive_x.bmp");
		left = YGECore::YGERessourceManager::getInstance()->getTexture("skymaps/waterscape_negative_x.bmp");
		front   = YGECore::YGERessourceManager::getInstance()->getTexture("skymaps/waterscape_positive_z.bmp");
		back = YGECore::YGERessourceManager::getInstance()->getTexture("skymaps/waterscape_negative_z.bmp");
		

	}

	void YGESkybox::draw(){

						glDisable(GL_LIGHTING);


		//@todo make texture clamp not repeat..
			// draw the skymap
			glDisable(GL_DEPTH_TEST);
					glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f,1.0f,1.0f);	


		up->bind();
		glBegin(GL_QUADS);								// Draw A Quad

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 10.0f, 10.0f,-10.0f);					// Top Right Of The Quad (Top)
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f,-10.0f);					// Top Left Of The Quad (Top)
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);					// Bottom Left Of The Quad (Top)
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 10.0f, 10.0f, 10.0f);					// Bottom Right Of The Quad (Top)
		
		glEnd();
		
		
		down->bind();
		glBegin(GL_QUADS);	
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f( 10.0f,-10.0f, 10.0f);					// Top Right Of The Quad (Bottom)
			
			glTexCoord2f(0.0f, 0.0f);			
			glVertex3f(-10.0f,-10.0f, 10.0f);					// Top Left Of The Quad (Bottom)
			
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-10.0f,-10.0f,-10.0f);					// Bottom Left Of The Quad (Bottom)
			
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f( 10.0f,-10.0f,-10.0f);					// Bottom Right Of The Quad (Bottom)
		glEnd();




		front->bind();

		glBegin(GL_QUADS);

		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 10.0f, 10.0f, 10.0f);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);					// Top Left Of The Quad (Front)
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f,-10.0f, 10.0f);					// Bottom Left Of The Quad (Front)
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 10.0f,-10.0f, 10.0f);					// Bottom Right Of The Quad (Front)
		
		glEnd();

		
		back->bind();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f( 10.0f,-10.0f,-10.0f);					// Top Right Of The Quad (Back)

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-10.0f,-10.0f,-10.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-10.0f, 10.0f,-10.0f);	

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f( 10.0f, 10.0f,-10.0f);					// Bottom Right Of The Quad (Back)
	glEnd();											// Done Drawing The Quad


		left->bind();

		glBegin(GL_QUADS);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);					// Top Right Of The Quad (Left)

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f,-10.0f);					// Top Left Of The Quad (Left)
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f,-10.0f,-10.0f);					// Bottom Left Of The Quad (Left)

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-10.0f,-10.0f, 10.0f);					// Bottom Right Of The Quad (Left)
	glEnd();											// Done Drawing The Quad

		right->bind();

		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f( 10.0f, 10.0f,-10.0f);					// Top Right Of The Quad (Right)

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f( 10.0f, 10.0f, 10.0f);					// Top Left Of The Quad (Right)
		
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f( 10.0f,-10.0f, 10.0f);					// Bottom Left Of The Quad (Right)
		
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f( 10.0f,-10.0f,-10.0f);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad


			glEnable(GL_DEPTH_TEST);

	}

}