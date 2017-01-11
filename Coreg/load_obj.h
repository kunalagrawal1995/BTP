#include "glm/vec4.hpp"
#include <bits/stdc++.h>


struct VertexData
{
	glm::vec4 position;
	glm::vec4 color;
};

struct TVertexData
{
	glm::vec4 position;
	glm::vec4 color;
	int part;
};

struct Scan{
	int person_index;
	int scan_index;
	std::string fileName;
	std::vector< VertexData> vertexData;
};

class TemplateMesh{
public:
	std::vector< TVertexData> vertexData;
	std::string template_dir;

	TemplateMesh(std::string dir);
	void load_template();
};

void load_obj_file(std::vector< VertexData > & vertexData, std::string fileName);