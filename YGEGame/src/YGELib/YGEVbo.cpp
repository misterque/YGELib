#include "GLee.h"
#include "YGEVbo.h"


#include "YGELogger.h"

namespace YGEGraphics {

	YGEVbo::YGEVbo(){

		uptodate = false;

		//if (GLEE_ARB_vertex_buffer_object)    //is multitexture support available?
		{
			YGECore::YGELogger::getInstance()->logToConsole("EXTENSION AVAIBLE");

		}
		//else
		{
			YGECore::YGELogger::getInstance()->logToConsole("EXTENSION NOT AVAIBLE");

		}


	}

	void YGEVbo::draw(YGEGraphicsContext *context){


		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);

		glColor3f(1,1,1);
		// fallback
		if(false){
			for(int i = 0; i < mesh->numTriangles; i++){
				glBegin(GL_TRIANGLES);

				int iV1 = mesh->indices[i*3 + 0] * 3;
				int iV2 = mesh->indices[i*3 + 1] * 3;
				int iV3 = mesh->indices[i*3 + 2] * 3;

				int iT1 = mesh->indices[i*3 + 0] * 2;
				int iT2 = mesh->indices[i*3 + 1] * 2;
				int iT3 = mesh->indices[i*3 + 2] * 2;


				glTexCoord2d(mesh->uv[iT1 + 0], mesh->uv[iT1 + 1]); 
				glVertex3f(	mesh->vertices[iV1 + 0],
					mesh->vertices[iV1 + 1],
					mesh->vertices[iV1 + 2] );

				glTexCoord2d(mesh->uv[iT2 + 0], mesh->uv[iT2 + 1]); 
				glVertex3f(	mesh->vertices[iV2 + 0],
					mesh->vertices[iV2 + 1],
					mesh->vertices[iV2 + 2] );

				glTexCoord2d(mesh->uv[iT3 + 0], mesh->uv[iT3 + 1]); 
				glVertex3f(	mesh->vertices[iV3 + 0],
					mesh->vertices[iV3 + 1],
					mesh->vertices[iV3 + 2] );

				glEnd();



			}
		} else {

			if(!uptodate){
				fillBuffers();
				uptodate = true;
			} 

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iboId);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);

		glClientActiveTexture(GL_TEXTURE0);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*) (sizeof(GLfloat) * 3));
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		


			//glDrawArrays( GL_TRIANGLES, 0, mesh->numVertices );
			glDrawElements(GL_TRIANGLES, mesh->numTriangles*3, GL_UNSIGNED_INT, 0);

			// reset
			glDisableClientState(GL_VERTEX_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);


			//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
	}

	void YGEVbo::fillBuffers(){


		glGenBuffersARB(1, &vboId);

		// fill the buffer with vertex data
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
		
		
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, mesh->numVertices*sizeof(Vertex), mesh->vertexBufferArray, GL_STATIC_DRAW_ARB);

		glGenBuffersARB(1, &iboId);
		// fill the buffer with index data
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iboId);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mesh->numTriangles*3*sizeof(GLuint), mesh->indices, GL_STATIC_DRAW_ARB);

	}


}