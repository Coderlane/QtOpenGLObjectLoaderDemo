#include "Model.h"

oGlModel::oGlModel()
{
	
}

oGlModel::oGlModel(string filename)
{
	load(filename);
}

void oGlModel::load(string filename)
{
	string line;
	vector<string> lineItems;
	ifstream objFile(filename.c_str());

    objFile.seekg (0, ios::end);
    int length = objFile.tellg();
    objFile.seekg (0, ios::beg);

    vertexes.reserve((int)length / 25);
    faces.reserve((int)length / 25);
    textureCoords.reserve((int)length / 25);

	while(objFile.good())
	{
		getline(objFile, line);

		lineItems = splitString(line, ' ');

		if(lineItems[0] == "v")
		{
			oGlVertex v;
			
			v.x = atof(lineItems[1].c_str());
			v.y = atof(lineItems[2].c_str());
			v.z = atof(lineItems[3].c_str());
						
			vertexes.push_back(v);	
		}
		else if (lineItems[0] == "vn")
		{
			oGlVertex v;
			
			v.x = atof(lineItems[1].c_str());
			v.y = atof(lineItems[2].c_str());
			v.z = atof(lineItems[3].c_str());
			
			normalVectors.push_back(v);
		}
		else if(lineItems[0] == "vt")
		{
			oGlVertex v;
			
			v.x = atof(lineItems[1].c_str());
			v.y = atof(lineItems[2].c_str());
			v.z = atof(lineItems[3].c_str());
			
			textureCoords.push_back(v);
			
		}
		else if(lineItems[0] == "f")
		{
			oGlFace face;
			for(int i = 1; i < lineItems.size(); i++)
			{
				vector<string> faceVs = splitString(lineItems[i],'/');
				oGlVTN vtn;
                if(lineItems[i] == "")
                    continue;
				switch(faceVs.size())
				{
					case 3:
						vtn.norm = atoi(faceVs[2].c_str());	
						vtn.vert = atoi(faceVs[0].c_str());
						vtn.tex = atoi(faceVs[1].c_str());
						if(faceVs[1] == "")
							vtn.tex = -1;
						break;
					case 2:	
						vtn.vert = atoi(faceVs[0].c_str());
						vtn.tex = atoi(faceVs[1].c_str());
						vtn.norm = -1;
						break;
					case 1:
						vtn.vert = atoi(faceVs[0].c_str());
						vtn.norm = -1;
						vtn.tex = -1;
						break;
				}
				face.vtnPairs.push_back(vtn);
			}	
			faces.push_back(face);
		}
        else if(lineItems[0] == "mtllib")
        {
            material = lineItems[1];
        }
	}
}

vector<string> oGlModel::splitString(string s, char delim)
{
	vector<string> retTok;
	
	string temp;
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] != delim)
			temp += s[i];
		else
		{	
			retTok.push_back(temp);
			temp = "";
		}

	}
	retTok.push_back(temp);
    return retTok;

}

oGlVertex oGlModel::calcNormal(oGlVertex a, oGlVertex b, oGlVertex c)
{
    /*
    So for a triangle p1, p2, p3, if the vector U = p2 - p1 and the vector V = p3 - p1 then the normal N = U X V and can be calculated by:

    Nx = UyVz - UzVy

    Ny = UzVx - UxVz

    Nz = UxVy - UyVx
            */

    oGlVertex norm;
    oGlVertex U;
    oGlVertex V;

    U.x = b.x  - a.x;
    U.y = b.y  - a.y;
    U.z = b.z  - a.z;

    V.x = c.x  - a.x;
    V.y = c.y  - a.y;
    V.z = c.z  - a.z;

    norm.x = (U.y * V.z) - (U.z * V.y);
    norm.y = (U.z * V.x) - (U.x * V.z);
    norm.z = (U.x * V.y) - (U.y * V.x);


    //norm.x = (U.z * V.y) - (U.y * V.z);
    //norm.y = (U.x * V.z) - (U.z * V.x);
    //norm.z = (U.y * V.x) - (U.x * V.y);

    return norm;
}
