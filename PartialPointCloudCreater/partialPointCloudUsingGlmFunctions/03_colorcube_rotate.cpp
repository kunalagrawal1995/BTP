#include "03_colorcube_rotate.hpp"

GLuint shaderProgram;
GLuint vbo,vao;

glm::mat4 global_translation_matrix;
glm::mat4 global_rotation_matrix_x;
glm::mat4 global_rotation_matrix_y;
glm::mat4 global_rotation_matrix_z;
glm::mat4 global_rotation_matrix;

glm::mat4 model_scaling_matrix;
glm::mat4 model_translation_matrix;
glm::mat4 model_rotation_matrix_x;
glm::mat4 model_rotation_matrix_y;
glm::mat4 model_rotation_matrix_z;
glm::mat4 model_rotation_matrix;

glm::mat4 ortho_matrix;
glm::mat4 perspective_matrix;
glm::mat4 modelview_matrix;
glm::mat4 model_matrix;
glm::mat4 wcs_to_vcs_matrix;
glm::mat4 vcs_to_ccs_matrix;
glm::mat4 ccs_to_ndcs_matrix;
glm::mat4 ndcs_to_dcs_matrix;


GLuint uModelViewMatrix;
GLuint state_shader;

//-----------------------------------------------------------------

//loads the pts point cloud file
void load(std::string model, std::vector<glm::vec4> &model_positions, std::vector<glm::vec4> &model_colors){
	char * name=&model[0];
	std::ifstream file_obj;
	file_obj.open(name);
	if(file_obj.is_open()){
		model_positions.clear();
		model_colors.clear();
		float inp_x,inp_y,inp_z,inp_r,inp_g,inp_b;
		glm::vec4 inp_pos,inp_color;
		while(file_obj>>inp_x>>inp_y>>inp_z>>inp_r>>inp_g>>inp_b){
			inp_pos[0] = inp_x;
			inp_pos[1] = inp_y;
			inp_pos[2] = inp_z;
			inp_pos[3] = 1.0f;
			inp_color[0] = inp_r;
			inp_color[1] = inp_g;
			inp_color[2] = inp_b;
			inp_color[3] = 1.0f;
			model_positions.push_back(inp_pos);
			model_colors.push_back(inp_color);
		}
		std::cout<<name<<" is now loaded."<<std::endl;
		file_obj.close(); 
	}
	else{
		std::cout<<"No file exists with name "<< name<<std::endl;
	}
} // load closed


void save_file(){
	std::ofstream scene_saver;
	scene_saver.open("scene.pts", std::ios::out);
	std::cout <<"kunal"<<std::endl;
	int WINSIZE = 512;
	float depth;
	float x,y,z,r,g,b;
	for (int i = 0; i < WINSIZE; ++i)
	{
		for (int j = 0; j < WINSIZE; ++j)
		{
			glReadPixels(i,j,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&depth);
			x = (i-256)/128.0;
			y = (j-256)/128.0;
			z = 4.0*(depth-0.5);
			if(depth == 1){
				continue;
			}
			else{
				r = 0.0; g = 0.0; b = 1.0;
				scene_saver<<x<<" "<<y<<" "<<z<<" "<<r<<" "<<g<<" "<<b<<std::endl;
			}
		}
	}
	std::cout<<"done. depth values calculated."<<std::endl;

	scene_saver.close();

}

void initBuffersGL(void)
{
	std::string model;
	std::ifstream scene_loader;
	scene_loader.open("myscene1.scn");
	if(scene_loader.is_open()){
		scene_loader>>model;
		load(model,model_positions,model_colors);
		scene_loader>>model_xscale>>model_yscale>>model_zscale;
		scene_loader>>model_xrot>>model_xrot>>model_xrot;
		scene_loader>>model_xtrans>>model_ytrans>>model_ztrans;

		scene_loader>>eye[0]>>eye[1]>>eye[2];
		scene_loader>>lookAt[0]>>lookAt[1]>>lookAt[2];
		scene_loader>>up[0]>>up[1]>>up[2];

		scene_loader>>L>>R>>T>>B>>N>>F;
		N=N; F=F;

		L=-L;B=-B;

		wcs_to_vcs_matrix = glm::lookAt(eye, lookAt, up);
		ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,20.0);
		perspective_matrix = glm::perspective(glm::radians(90.0), 1.0, 0.1, 20.0);


		// vcs_to_ccs_matrix[0] = glm::vec4(2*N/(R-L), 0.0f, 0.0f, 0.0f);
		// vcs_to_ccs_matrix[1] = glm::vec4(0.0f, 2*N/(T-B), 0.0f, 0.0f);
		// vcs_to_ccs_matrix[2] = glm::vec4((R+L)/(R-L), (T+B)/(T-B), -(F+N)/(F-N), -1.0f);
		// vcs_to_ccs_matrix[3] = glm::vec4(0.0f, 0.0f, -2*F*N/(F-N), 0.0f);

		// glm::mat4 dcs1;
		// dcs1[0] = glm::vec4((Rw-Lw)/2, 0.0f,0.0f,0.0f);
		// dcs1[1] = glm::vec4(0.0f, (Tw-Bw)/2,0.0f,0.0f);
		// dcs1[2] = glm::vec4(0.0f, 0.0f,0.5f,0.0f);
		// dcs1[3] = glm::vec4(0.0f, 0.0f,0.0f,1.0f);

		// glm::mat4 dcs2;
		// dcs2[0] = glm::vec4(1.0f, 0.0f,0.0f,0.0f);
		// dcs2[1] = glm::vec4(0.0f, 1.0f,0.0f,0.0f);
		// dcs2[2] = glm::vec4(0.0f, 0.0f,1.0f,0.0f);
		// dcs2[3] = glm::vec4((Rw+Lw)/2, (Tw+Bw)/2,0.5f,1.0f);

		// ndcs_to_dcs_matrix = dcs2*dcs1;

	}
	else {
		std::cout<< "could not find file myscene.scn"<<std::endl;
	}

	// Load shaders and use the resulting shader program
	std::string vertex_shader_file("03_vshader.glsl");
	std::string fragment_shader_file("03_fshader.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	glUseProgram( shaderProgram );

	GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	state_shader = glGetUniformLocation( shaderProgram, "state");


	//Ask GL for a Vertex Attribute Object (vao)
	glGenVertexArrays (1, &vao);
	//Ask GL for a Vertex Buffer Object (vbo)
	glGenBuffers (1, &vbo);

	//Set it as the current array to be used by binding it
	glBindVertexArray (vao);
	//Set it as the current buffer to be used by binding it
	glBindBuffer (GL_ARRAY_BUFFER, vbo);

	//Copy the points into the current buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBufferData (GL_ARRAY_BUFFER, model_positions.size()*sizeof(glm::vec4)+ model_colors.size()*sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, model_positions.size()*sizeof(glm::vec4), &model_positions[0]);
	glBufferSubData( GL_ARRAY_BUFFER, model_positions.size()*sizeof(glm::vec4),model_colors.size()*sizeof(glm::vec4), &model_colors[0]);

	glEnableVertexAttribArray( vPosition );
	glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_ALWAYS);
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model_positions.size()*sizeof(glm::vec4)) );
}

void renderGL(void){
	//set up global transformations set by control keys
	global_translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xtrans, ytrans, ztrans));
	global_rotation_matrix_x = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
	global_rotation_matrix_y = glm::rotate(glm::mat4(1.0f), yrot, glm::vec3(0.0f,1.0f,0.0f));
	global_rotation_matrix_z = glm::rotate(glm::mat4(1.0f), zrot, glm::vec3(0.0f,0.0f,1.0f));
	global_rotation_matrix = global_rotation_matrix_z * global_rotation_matrix_y * global_rotation_matrix_x;

	//model transformations
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	model_scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(model_xscale,model_yscale,model_zscale));
	model_translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(model_xtrans,model_ytrans,model_ztrans));
	model_rotation_matrix_x = glm::rotate(glm::mat4(1.0f), model_xrot, glm::vec3(1.0f,0.0f,0.0f));
	model_rotation_matrix_y = glm::rotate(glm::mat4(1.0f), model_yrot, glm::vec3(0.0f,1.0f,0.0f));
	model_rotation_matrix_z = glm::rotate(glm::mat4(1.0f), model_zrot, glm::vec3(0.0f,0.0f,1.0f));
	model_rotation_matrix = model_rotation_matrix_z * model_rotation_matrix_y * model_rotation_matrix_x;

	wcs_to_vcs_matrix = glm::lookAt(glm::vec3(model_rotation_matrix*glm::vec4(eye,1.0)), lookAt, glm::vec3(model_rotation_matrix*glm::vec4(up,1.0)));

	GLfloat matrix_view[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, matrix_view);
	glm::mat4 matrix_view4 = glm::make_mat4(matrix_view);

	GLfloat matrix_pro[16];
	glGetFloatv (GL_PROJECTION_MATRIX, matrix_pro);
	glm::mat4 matrix_pro4 = glm::make_mat4(matrix_pro);

	model_matrix = model_translation_matrix * model_rotation_matrix * model_scaling_matrix;
	if (state==0){
		modelview_matrix = model_matrix;
	}
	else if (state==1){
		modelview_matrix = matrix_pro4 * matrix_view4 * model_matrix;
	}
	else if(state == 2){
		modelview_matrix = inverse(matrix_view4) * inverse(matrix_pro4);
	}
	else if(state == 3){
		modelview_matrix = inverse(model_matrix) * inverse(matrix_view4) * inverse(matrix_pro4);
	}
	// else if (state==2 || state == 3){
	// 	modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix *vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
	// }
	// else if (state==4){
	// 	modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix* ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
	// }
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
	glUniform1i(state_shader,state);

	glBindVertexArray (vao);
	// glDrawArrays(GL_TRIANGLES, 0, model_positions.size());
	glDrawArrays(GL_POINTS, 0, model_positions.size());
}



	int main(int argc, char** argv)
	{
	//! The pointer to the GLFW window
		GLFWwindow* window;

	//! Setting up the GLFW Error callback
		glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
		if (!glfwInit())
			return -1;

	//We want OpenGL 4.0
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//This is for MacOSX - can be omitted otherwise
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//! Create a windowed mode window and its OpenGL context
		window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

	//! Make the window's context current 
		glfwMakeContextCurrent(window);

	//Initialize GLEW
	//Turn this on to get Shader based OpenGL
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			//Problem: glewInit failed, something is seriously wrong.
			std::cerr<<"GLEW Init Failed : %s"<<std::endl;
		}

	//Print and see what context got enabled
		std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
		std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
		std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
		std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

	//Keyboard Callback
		glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
		glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
		csX75::initGL();
		initBuffersGL();

	// Loop until the user closes the window
		while (glfwWindowShouldClose(window) == 0)
		{

			// Render here
			renderGL();

			// Swap front and back buffers
			glfwSwapBuffers(window);
			
			// Poll for and process events
			glfwPollEvents();
		}

		glfwTerminate();
		return 0;
	}

//-------------------------------------------------------------------------


