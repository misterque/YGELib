/**
* @file
* @author Dirk Fortmeier
* @date 17.11.2009
*/

#ifndef _YGE_PRIMITIVES_H_
#define _YGE_PRIMITIVES_H_

#include <SDL_opengl.h>
#include <list>
#include <vector>
#include <ode/ode.h>

namespace YGEGraphics {

	/** 
	 * @brief simple vertex structure
	 * for passing vertices to a vertex buffer object
	 */
	struct Vertex {
		Vertex() : x(0.0f), y(0.0f), z(0.0f) { };

		Vertex(GLfloat X, GLfloat Y, GLfloat Z) : x(X), y(Y), z(Z) { };

		Vertex(GLfloat X, GLfloat Y, GLfloat Z, GLfloat U, GLfloat V) :
		x(X), y(Y), z(Z), u(U), v(V) {

		};



		GLfloat x, y, z;

		GLfloat u, v;

		GLubyte r,g,b,a;

		GLfloat nx, ny, nz;

		int index;

	};

	/**
	 * @brief simple trianle structure
	 */
	struct Triangle {

		Triangle(int A, int B, int C) : a(A), b(B), c(C) { };
		Triangle(){};

		int a,b,c;

	};


	/**
	* @brief holds mesh information to create vertex buffer objects
	*/
	class Mesh {
	private:
		int vertexCounter;
	public:

		Mesh();
		~Mesh();

		std::vector<Vertex> vertexList;
		std::list<Triangle> triangleList;

		void addVertex(const Vertex &v);

		void addTriangle(const Triangle &t);


		void fillArrays();


		/**
		 * create an ode mesh object for collision detection from a mesh
		 */
		dTriMeshDataID getODEMesh();


		Vertex* vertexBufferArray;
		/**
		* array of vertices, size must be number of
		* vertices * 3
		*/
		GLfloat* vertices;

		/**
		* array of uv coords, size must be number of vertics * 2 * sizeof[float]
		*
		*/
		GLfloat* uv;


		/**
		* array
		*/
		GLuint* indices;
		/**
		* texture ID
		* @todo add multitexturing
		*/
		GLuint textureID;



		int numVertices;
		int numTriangles;

	};


}


#endif