#include "load_obj.h"

void load_obj_file(std::vector< VertexData > & vertexData, std::string fileName)
{
	std::vector< glm::vec4 > vertices;
	std::vector< glm::vec4 > colors;

	FILE * file = fopen(fileName.c_str(), "r");

	if( file == NULL )
	{
	  printf("Impossible to open the file %s!\n", fileName.c_str());
	  return ;
	}

	char lineHeader[16];
	while(1)
	{
		bzero(lineHeader, 16);
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; //
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			// read vertex pos
			float v1,v2,v3;
			fscanf(file, "%f %f %f\n",  &v1,&v2, &v3 );
			glm::vec4 vertex(v1,v2,v3,1.0f);

			//take default colors
			glm::vec4 vertex_color(1,0,0,1);
			colors.push_back(vertex_color);
			vertices.push_back(vertex);

		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			int vertexIndex[3];
			fscanf(file, "%d %d %d\n", &vertexIndex[0],  &vertexIndex[1], &vertexIndex[2] );
			vertexData.push_back({vertices[vertexIndex[0]-1],colors[vertexIndex[0]-1]});
			vertexData.push_back({vertices[vertexIndex[1]-1],colors[vertexIndex[1]-1]});
			vertexData.push_back({vertices[vertexIndex[2]-1],colors[vertexIndex[2]-1]});
		}
	}
	fclose(file);
	std::cout<<"loaded "<< fileName <<" successfully." << std::endl;
}

TemplateMesh::TemplateMesh(std::string dir){
	template_dir = dir;
}

void TemplateMesh::load_template(){
	std::string parts_fileName = template_dir + "partsTree.out";
	std::string fileName = template_dir + "mesh.obj";


	std::vector< glm::vec4 > vertices;
	std::vector< glm::vec4 > colors;
	std::vector< int > parts;

	FILE * file = fopen(fileName.c_str(), "r");
	FILE * file_parts = fopen(parts_fileName.c_str(), "r");

	if( file == NULL )
	{
	  printf("Impossible to open the file %s!\n", fileName.c_str());
	  return ;
	}

	if( file_parts == NULL )
	{
	  printf("Impossible to open the file %s!\n", parts_fileName.c_str());
	  return ;
	}

	char lineHeader[16];

	// read start of parts file
	int num_points, num_parts, part_num;
	fscanf(file_parts, "%d %d\n", &num_points, &num_parts);
	while(1)
	{
		bzero(lineHeader, 16);
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; //
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			// read vertex pos
			float v1,v2,v3;
			fscanf(file, "%f %f %f\n",  &v1,&v2, &v3 );
			fscanf(file_parts, "%d ",  &part_num );
			glm::vec4 vertex(v1,v2,v3,1.0f);

			//take default colors
			glm::vec4 vertex_color(1,0,0,1);
			colors.push_back(vertex_color);
			vertices.push_back(vertex);
			parts.push_back(part_num);

		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			int vertexIndex[3];
			fscanf(file, "%d %d %d\n", &vertexIndex[0],  &vertexIndex[1], &vertexIndex[2] );
			vertexData.push_back({vertices[vertexIndex[0]-1],colors[vertexIndex[0]-1], parts[vertexIndex[0]-1]});
			vertexData.push_back({vertices[vertexIndex[1]-1],colors[vertexIndex[1]-1], parts[vertexIndex[1]-1]});
			vertexData.push_back({vertices[vertexIndex[2]-1],colors[vertexIndex[2]-1], parts[vertexIndex[2]-1]});
		}
	}
	fclose(file);
	std::cout<<"loaded template file "<< fileName <<" successfully." << std::endl;
}