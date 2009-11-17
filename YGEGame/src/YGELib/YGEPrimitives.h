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

namespace YGEGraphics {


	struct Vertex {
		Vertex() : x(0.0f), y(0.0f), z(0.0f) { };

		Vertex(GLfloat X, GLfloat Y, GLfloat Z) : x(X), y(Y), z(Z) { };

		Vertex(GLfloat X, GLfloat Y, GLfloat Z, GLfloat U, GLfloat V) :
		x(X), y(Y), z(Z), u(U), v(V) {

		};


		int index;

		GLfloat x, y, z;

		GLfloat u, v;

		GLubyte r,g,b,a;
	};

	struct Triangle {

		Triangle(int A, int B, int C) : a(A), b(B), c(C) { };
		Triangle(){};

		int a,b,c;

	};


	/**
	* holds mesh information
	*/
	class Mesh {
	private:
		int vertexCounter;
	public:

		Mesh(): vertexCounter(0) {};

		std::vector<Vertex> vertexList;
		std::list<Triangle> triangleList;

		void addVertex(const Vertex &v){
			vertexList.push_back(v);
			vertexList.back().index = vertexCounter;
			vertexCounter++;

		}

		void addTriangle(const Triangle &t){
			triangleList.push_back(t);

		}

		void fillArrays(){
			vertices = new GLfloat[vertexList.size() * 3];
			uv = new GLfloat[triangleList.size() * 2];

			indices = new GLuint[triangleList.size() * 3];
			int i = 0;
			for(std::vector<Vertex>::iterator iter = vertexList.begin();
				iter != vertexList.end();
				iter++) {
					vertices[i * 3 + 0] = iter->x;
					vertices[i * 3 + 1] = iter->y;
					vertices[i * 3 + 2] = iter->z;

					uv[i * 2 + 0] = iter->u;
					uv[i * 2 + 1] = iter->v;

					i++;
			}

			i = 0;
			for(std::list<Triangle>::iterator iter = triangleList.begin();
				iter != triangleList.end();
				iter++) {

					indices[i * 3 + 0] = iter->a;
					indices[i * 3 + 1] = iter->b;
					indices[i * 3 + 2] = iter->c;
					i++;

			}
			numVertices = vertexList.size();
			numTriangles = triangleList.size();

		}
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