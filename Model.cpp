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
