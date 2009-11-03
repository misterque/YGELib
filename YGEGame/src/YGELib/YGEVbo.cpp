#include "GLee.h"
#include "YGEVbo.h"


#include "YGELogger.h"

namespace YGEGraphics {

	YGEVbo::YGEVbo(){

		uptodate = false;

		if (GLEE_ARB_vertex_buffer_object)    //is multitexture support available?
		{
			YGECore::YGELogger::getInstance()->logToConsole("EXTENSION AVAIBLE");

		}
		else
		{
			YGECore::YGELogger::getInstance()->logToConsole("EXTENSION AVAIBLE");

		}


	}

	void YGEVbo::draw(YGEGraphicsContext *context){




		if(!uptodate){
			fillBuffers();
			uptodate = true;
		} 

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iboId);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glDrawElements(GL_TRIANGLES, mesh->numTriangles * 3, GL_FLOAT, 0);

		// reset
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	}

	void YGEVbo::fillBuffers(){


		glGenBuffersARB(1, &vboId);

		// fill the buffer with vertex data
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, mesh->numVertices, mesh->vertices, GL_STATIC_DRAW_ARB);

		glGenBuffersARB(1, &iboId);
		// fill the buffer with index data
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iboId);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->numTriangles*3, mesh->indices, GL_STATIC_DRAW_ARB);

	}


}