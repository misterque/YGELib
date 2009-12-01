#include "YGEStaticMesh.h"
#include "YGEExceptions.h"
#include "YGERessourceManager.h"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
/**
* stolen from http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
*/
void Tokenize(const string& str,
			  vector<string>& tokens,
			  const string& delimiters = "/")
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}


int vertexIndexFromString(string str){
	std::vector<string> strings;
	Tokenize(str, strings, "/");
	return atoi(strings.front().c_str());
}

int texCoordIndexFromString(string str){
	std::vector<string> strings;
	Tokenize(str, strings, "/");
	return atoi((++strings.begin())->c_str());
}

int vertexNormalIndexFromString(string str){
	std::vector<string> strings;
	Tokenize(str, strings, "/");
	if(strings.size() < 3) return -1;
	return atoi((++(++strings.begin()))->c_str());
}



namespace YGEGraphics {


	typedef string ObjTextureName;
	typedef string ObjTextureFilename;


	typedef std::map<ObjTextureName, ObjTextureFilename> OBJTextures;

	OBJTextures objTextures;

	OBJTextures loadObjTexturesFromMTL(const char *filename){
		OBJTextures textures;

		std::ifstream is;
		is.open(filename);
		if(!is.is_open()) {
			throw YGEExceptionFileNotFound(filename);
		}

		ObjTextureName name;

		while(!is.eof()){
			std::string line, type, in;
			getline(is, line);
			std::istringstream istr(line);

			istr >> type;

			if(type == "newmtl"){
				istr >> name;
			}
			if(type == "map_Kd"){
				ObjTextureFilename filename;
				istr >> filename;
				textures[name] = filename;
			}
		}
		return textures;

	}

	void YGEStaticMesh::loadFromOBJ(const char *filename){



		// then extract the filename of the image
		std::ostringstream s;
		s<<"../media/"<<filename;

		int d = s.str().find_last_of("/\\");
		std::string path = s.str().substr(0,d+1);

		std::ifstream is;
		is.open(s.str().c_str());
		if(!is.is_open()) {
			throw YGEExceptionFileNotFound(s.str());
			return;
		}

		std::vector<Vertex> textureCoords;
		std::vector<Vertex> vertexCoords;
		std::vector<Vertex> vertexNormals;

		OBJTextures textures;

		int vtindex = 0;
		while(!is.eof()){
			std::string line, type, in;
			getline(is, line);
			std::istringstream istr(line);

			istr >> type;

			if(type == "v"){
				Vertex v;
				istr >> v.x;
				istr >> v.y;
				istr >> v.z;

				vertexCoords.push_back(v);
			}
			if(type == "vt") {
				Vertex v;
				istr >> v.u;
				istr >> v.v;

				textureCoords.push_back(v);

			}
			if(type == "vn") {
				Vertex v;
				istr >> v.nx;
				istr >> v.ny;
				istr >> v.nz;

				vertexNormals.push_back(v);

			}

			if(type == "f"){
				int vindex, vtindex, vnindex;
				Triangle v;
				Vertex vv;
				string s;

				for(int j = 0; j<3; j++){
					istr >> s;
					vindex = vertexIndexFromString(s) - 1;
					vtindex = texCoordIndexFromString(s) - 1;
					vnindex = vertexNormalIndexFromString(s) - 1;

					vv.u = textureCoords.at(vtindex).u;
					vv.v = textureCoords.at(vtindex).v;
					vv.x = vertexCoords.at(vindex).x;
					vv.y = vertexCoords.at(vindex).y;
					vv.z = vertexCoords.at(vindex).z;
					if(vnindex >= 0) {
					vv.nx = vertexNormals.at(vnindex).nx;
					vv.ny = vertexNormals.at(vnindex).ny;
					vv.nz = vertexNormals.at(vnindex).nz;
					} else {
						vv.nx = 0;
						vv.ny = 1;
						vv.nz = 0;
					}


					model.vertexList.push_back(vv);

					switch(j){
					case 0:
						v.a = model.vertexList.size() - 1;
						break;
					case 1:
						v.b = model.vertexList.size() - 1;
						break;
					case 2:
						v.c = model.vertexList.size() - 1;
						break;
					}

				}
				model.addTriangle(v);

			}
			if(type=="mtllib"){
				string s;
				istr >> s;
				std::stringstream ss;
				ss << path << s;
				textures = loadObjTexturesFromMTL(ss.str().c_str());
			}

			if(type=="usemtl"){
				string s;
				istr >> s;

				std::stringstream ss;
				ss <<"images/"<< textures[s];

				model.textureID =
					YGECore::YGERessourceManager::getInstance()->getTexture(ss.str().c_str())->textureID;

			}


		}

		model.fillArrays();
		numMeshes = 1;
		meshes = new YGEVbo();
		meshes->setMesh(&model);

	}

	void YGEStaticMesh::draw(YGEGraphicsContext *context){
		meshes->draw(context);
	}

}