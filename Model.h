#ifndef __OG_MODEL_LOADER__
#define __OG_MODEL_LOADER__

#define PTYPE float
#define OGVTF (GLfloat*)&

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <iostream>

using std::map;
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::ios;

//Vertex (protip, can be passed as a GLfloat array by using the OGVTF constant, ie glVertex3fv(OGVTF vert); )
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

typedef struct _oGlMatInfo
{
    string name;
    oGlVertex Ka;
    oGlVertex Kd;
    oGlVertex Ks;
    int illum;
    PTYPE Ns;
}oGlMatInfo;

typedef struct _oGlMatIndex
{
    int fIndex;
    int matIndex;
}oGlMatIndex;

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
    void loadMaterial(string matFile);

	vector<oGlVertex> vertexes;
	vector<oGlVertex> textureCoords;
	vector<oGlVertex> normalVectors;
    vector<oGlFace> faces;
    vector<oGlMatInfo> materials;
    vector<oGlMatIndex> matIndexes;

    oGlVertex calcNormal(oGlVertex a, oGlVertex b, oGlVertex c);

};



#endif

