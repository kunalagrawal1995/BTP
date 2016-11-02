/*
  A program which opens a window and draws the "color cube."

  Use the arrow keys and +/-, PgUp,PgDn, Home,End, Ins,Del 
  keys to make the cube move.

  Use w/W to toggle between wireframe and solid models
  Use c/C to toggle backface culling on/off

  Written by - 
               Parag Chaudhuri
*/
// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>

class Camera{
public:
	glm::vec3 eye;
	glm::vec3 up;
	glm::vec3 lookAt;
};

//State control
bool state = 0;	// 0 for perspective, 1 for ortho view
bool global_state = 1;	//1 for global state, 0 for local state

// Global Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
GLfloat xtrans=0.0, ytrans=0.0, ztrans=0.0;

// Model Parameters
GLfloat model_xrot=0.0,model_yrot=0.0,model_zrot=0.0;
GLfloat model_xtrans=0.0, model_ytrans=0.0, model_ztrans=0.0;
GLfloat model_xscale=1.0, model_yscale=1.0, model_zscale=1.0;

std::vector<Camera> cameras;
int num_cams;
int curr_cam_index = 0;
double KINECT_FOV = 43.0;
Camera global_cam;

GLfloat L=0.0,R=0.0,T=0.0,B=0.0,N=0.0,F=0.0;

//model positions
std::vector<glm::vec4> model_positions;
std::vector<glm::vec4> model_colors;

// frustum positions
std::vector<glm::vec4> frustum_positions;
std::vector<glm::vec4> frustum_colors;

//dcs cordinates
GLfloat Lw = -0.5,Rw=0.5,Tw = 0.5,Bw =-0.5;  

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;

//-------------------------------------------------------------------------


