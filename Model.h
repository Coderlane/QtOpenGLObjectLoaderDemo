#ifndef __OG_MODEL_LOADER__
#define __OG_MODEL_LOADER__

#define PTYPE float

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

typedef struct _oGlMatInfo
{
    string name;
    oGlVertex Ka;
    oGlVertex Kd;
    oGlVertex Ks;
    int illum;
    PTYPE Ns;
    /*
    newmtl shinyred
    Ka  0.1986  0.0000  0.0000
    Kd  0.5922  0.0166  0.0000
    Ks  0.5974  0.2084  0.2084
    illum 2
    Ns 100.2237*/
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

