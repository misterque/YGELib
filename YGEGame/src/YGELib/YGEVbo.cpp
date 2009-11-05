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
			YGECore::YGELogger::getInstance()->logToConsole("EXTENSION NOT AVAIBLE");

		}


	}

	void YGEVbo::draw(YGEGraphicsContext *context){


		//YGECore::YGELogger::getInstance()->log(mesh->vertices[ 1]);

		//glTranslatef(-20.0f, -20.0f, -140.0f);
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		// fallback
		if(false){
		for(int i = 0; i < mesh->numTriangles; i++){
			glBegin(GL_TRIANGLES);

			int iV1 = mesh->indices[i*3 + 0] * 3;
			int iV2 = mesh->indices[i*3 + 1] * 3;
			int iV3 = mesh->indices[i*3 + 2] * 3;

			
			glVertex3f(	mesh->vertices[iV1 + 0],
						mesh->vertices[iV1 + 1],
						mesh->vertices[iV1 + 2] );


			glVertex3f(	mesh->vertices[iV2 + 0],
						mesh->vertices[iV2 + 1],
						mesh->vertices[iV2 + 2] );

			glVertex3f(	mesh->vertices[iV3 + 0],
						mesh->vertices[iV3 + 1],
						mesh->vertices[iV3 + 2] );
			
			glEnd();



		}
		}

		if(!uptodate){
			fillBuffers();
			uptodate = true;
		} 

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iboId);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		//glDrawArrays( GL_TRIANGLES, 0, mesh->numVertices );
		glDrawElements(GL_TRIANGLES, mesh->numTriangles*3, GL_UNSIGNED_INT, 0);

		// reset
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
		

		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	}

	void YGEVbo::fillBuffers(){


		glGenBuffersARB(1, &vboId);

		// fill the buffer with vertex data
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, mesh->numVertices*3*sizeof(float), mesh->vertices, GL_STATIC_DRAW_ARB);

		glGenBuffersARB(1, &iboId);
		// fill the buffer with index data
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iboId);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->numTriangles*3*sizeof(float), mesh->indices, GL_STATIC_DRAW_ARB);

	}


}