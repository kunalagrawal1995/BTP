/*
  A program which opens a window and draws the "color cube."

  Use the arrow keys and +/-, PgUp,PgDn, Home,End, Ins,Del 
  keys to make the cube move.

  Use w/W to toggle between wireframe and solid models
  Use c/C to toggle backface culling on/off

  Written by - 
               Parag Chaudhuri
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

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


//State control
GLint state = 0;

// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
// Translation Parameters
glm::vec3 trans(0.0f);

// Transition Parameters
GLfloat xrot1=0.0,yrot1=0.0,zrot1=0.0;
glm::vec3 trans1(0.0f);
glm::vec3 scale1(0.0f);

GLfloat xrot2=0.0,yrot2=0.0,zrot2=0.0;
glm::vec3 trans2(0.0f);
glm::vec3 scale2(0.0f);

GLfloat xrot3=0.0,yrot3=0.0,zrot3=0.0;
glm::vec3 trans3(0.0f);
glm::vec3 scale3(0.0f);

glm::vec3 eye(0.0f);
glm::vec3 up(0.0f);
glm::vec3 lookAt(0.0f);

GLfloat L=0.0,R=0.0,T=0.0,B=0.0,N=0.0,F=0.0;

//model positions
std::vector<glm::vec4> model1_positions;
std::vector<glm::vec4> model1_colors;

std::vector<glm::vec4> model2_positions;
std::vector<glm::vec4> model2_colors;

std::vector<glm::vec4> model3_positions;
std::vector<glm::vec4> model3_colors;

// frustum positions
std::vector<glm::vec4> frustum_positions;
std::vector<glm::vec4> frustum_colors;

//dcs cordinates
GLfloat Lw = -0.5,Rw=0.5,Tw = 0.5,Bw =-0.5;  

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;

void save_file();

//-------------------------------------------------------------------------

#endif

