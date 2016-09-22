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

// Global Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
// Global Translation Parameters
GLfloat xtrans=0.0, ytrans=0.0, ztrans=0.0;

// Transition Parameters
GLfloat model_xrot=0.0,model_yrot=0.0,model_zrot=0.0;
GLfloat model_xtrans=0.0, model_ytrans=0.0, model_ztrans=0.0;
GLfloat model_xscale=1.0, model_yscale=1.0, model_zscale=1.0;

glm::vec3 eye(0.0f);
glm::vec3 up(0.0f);
glm::vec3 lookAt(0.0f);

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

#endif

