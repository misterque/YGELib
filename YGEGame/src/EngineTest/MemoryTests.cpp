#include "tests.h"
#include "YGEPrimitives.h"
#include "YGEVector.h"

void memoryTests(){

	YGEGraphics::Mesh* mesh = new YGEGraphics::Mesh();
	delete mesh;

	mesh = new YGEGraphics::Mesh();
	mesh->addVertex(YGEGraphics::Vertex(0,0,0));
	mesh->fillArrays();
	delete mesh;

}