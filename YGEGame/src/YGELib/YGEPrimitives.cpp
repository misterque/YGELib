#include "YGEPrimitives.h"

namespace YGEGraphics {


	void Mesh::addVertex(const Vertex &v){
		vertexList.push_back(v);
		vertexList.back().index = vertexCounter;
		vertexCounter++;

	}

	void Mesh::addTriangle(const Triangle &t){
		triangleList.push_back(t);

	}

	void Mesh::fillArrays(){

		vertexBufferArray = new Vertex[vertexList.size()];

		vertices = new GLfloat[vertexList.size() * 3];
		uv = new GLfloat[vertexList.size() * 2];

		indices = new GLuint[triangleList.size() * 3];
		int i = 0;
		for(std::vector<Vertex>::iterator iter = vertexList.begin();
			iter != vertexList.end();
			iter++) {

				vertexBufferArray[i] = *iter;

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


	dTriMeshDataID Mesh::getODEMesh(){

		dTriMeshDataID meshId = dGeomTriMeshDataCreate();

		dReal* vertices = new dReal[vertexList.size() * 4];
		int* indices = new int[triangleList.size() * 3];
		int i = 0;

		for(std::vector<Vertex>::iterator iter = vertexList.begin();
			iter != vertexList.end();
			iter++) {

				vertices[i * 4 + 0] = iter->x;
				vertices[i * 4 + 1] = iter->y;
				vertices[i * 4 + 2] = iter->z;

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

		dGeomTriMeshDataBuildSimple ( meshId, (dReal*)vertices, vertexList.size(),
			(dTriIndex*)indices, triangleList.size() * 3 );

		return meshId;

	}




};