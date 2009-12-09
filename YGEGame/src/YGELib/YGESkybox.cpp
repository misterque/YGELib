#include "YGESkybox.h"
#include <sstream>

namespace YGEGraphics {

	void YGESkybox::loadTextures(const char* name){

		std::stringstream upfile, downfile, rightfile, leftfile, frontfile, backfile;
		upfile<<"skymaps/"<<name<<"_positive_y.bmp";
		downfile<<"skymaps/"<<name<<"_negative_y.bmp";
		rightfile<<"skymaps/"<<name<<"_positive_x.bmp";
		leftfile<<"skymaps/"<<name<<"_negative_x.bmp";
		frontfile<<"skymaps/"<<name<<"_positive_z.bmp";
		backfile<<"skymaps/"<<name<<"_negative_z.bmp";

		up   = YGECore::YGERessourceManager::getInstance()->getTexture(upfile.str().c_str());
		down = YGECore::YGERessourceManager::getInstance()->getTexture(downfile.str().c_str());
		right  = YGECore::YGERessourceManager::getInstance()->getTexture(rightfile.str().c_str());
		left = YGECore::YGERessourceManager::getInstance()->getTexture(leftfile.str().c_str());
		front   = YGECore::YGERessourceManager::getInstance()->getTexture(frontfile.str().c_str());
		back = YGECore::YGERessourceManager::getInstance()->getTexture(backfile.str().c_str());

		up->setRepeat(false);
		down->setRepeat(false);
		right->setRepeat(false);
		left->setRepeat(false);
		front->setRepeat(false);
		back->setRepeat(false);


	}

	void YGESkybox::draw(){

		glDisable(GL_LIGHTING);

		glDisable(GL_CULL_FACE);


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