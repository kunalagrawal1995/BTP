#include <bits/stdc++.h>
#include "load_obj.h"

using namespace std;



int main(int argc, char const *argv[])
{
	struct Scan scans[100];	// all scan data goes here

	// reading data
	string scan_dir = "test_data/training_scans/";
	for(int i = 0; i < 100; i++){
		char f[256];
		sprintf(f, "%str_scan_%03d.obj", scan_dir.c_str(), i);
		scans[i].filename = f;
		scans[i].person_index = i/10;
		scans[i].scan_index = i%10;
		load_obj_file(scans[i].vertexData, scans[i].filename);
	}
	
	//setup the BlendSCAPE model
	string template_dir = "test_data/skeleton/";
	TemplateMesh template_mesh(template_dir);
	template_mesh.load_template();

	cout << "yay." <<endl;
}