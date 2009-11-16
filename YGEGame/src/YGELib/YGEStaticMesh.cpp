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

				model.addVertex(v);
			}
			if(type == "vt") {
				Vertex v;
				istr >> v.u;
				istr >> v.v;

				textureCoords.push_back(v);

			}

			if(type == "f"){
				int vtindex;
				Triangle v;
				string s;
				
				istr >> s;
				v.a = vertexIndexFromString(s) - 1;
				vtindex = texCoordIndexFromString(s) - 1;
				model.vertexList.at(v.a).u = textureCoords.at(vtindex).u;
				model.vertexList.at(v.a).v = textureCoords.at(vtindex).v;

				istr >> s;
				v.b = vertexIndexFromString(s) - 1;
				vtindex = texCoordIndexFromString(s) - 1;
				model.vertexList.at(v.b).u = textureCoords.at(vtindex).u;
				model.vertexList.at(v.b).v = textureCoords.at(vtindex).v;


				istr >> s;
				v.c = vertexIndexFromString(s) - 1;
				vtindex = texCoordIndexFromString(s) - 1;
				model.vertexList.at(v.c).u = textureCoords.at(vtindex).u;
				model.vertexList.at(v.c).v = textureCoords.at(vtindex).v;

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
					YGECore::YGERessourceManager::getInstance()->getTexture(ss.str())->textureID;

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