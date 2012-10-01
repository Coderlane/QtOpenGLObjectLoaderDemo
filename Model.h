#ifndef __OG_MODEL_LOADER__
#define __OG_MODEL_LOADER__

#define PTYPE float

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#include <iostream>

using std::cout;
using std::string;
using std::vector;
using std::ifstream;

//Vertex
typedef struct _oGlVertex
{
	PTYPE x;
	PTYPE y;
	PTYPE z;
	PTYPE w;
}oGlVertex;

//Vertex / Texture Coordinate / Normal 
typedef struct _oGlVTN
{
	int vert;
	int tex;
	int norm;
}oGlVTN;

//face, these represent what actually gets drawn
typedef struct _oGlFace
{
	vector<oGlVTN> vtnPairs;
}oGlFace;


class oGlModel
{
public:
	oGlModel();
	oGlModel(string filename);

	void load(string filename);
 
	vector<string> splitString(string s, char delim);

	vector<oGlVertex> vertexes;
	vector<oGlVertex> textureCoords;
	vector<oGlVertex> normalVectors;
	vector<oGlFace> faces;

	

};



#endif

