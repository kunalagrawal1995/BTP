#include "gl_framework.hpp"
#include "glm/vec3.hpp"

extern GLfloat xrot,yrot,zrot;
extern GLfloat xtrans, ytrans, ztrans;

// extern GLfloat model_xrot,model_yrot,model_zrot;
// extern GLfloat model_xtrans, model_ytrans, model_ztrans;

extern bool state;
extern bool global_state;
extern int num_cams;
extern int curr_cam_index;
extern void save_all();

namespace csX75
{
	//! Initialize GL State
	void initGL(void)
	{
		//Set framebuffer clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//Set depth buffer furthest depth
		glClearDepth(1.0);
		//Set depth test to less-than
		glDepthFunc(GL_LESS);
		//Enable depth testing
		glEnable(GL_DEPTH_TEST);
		}

		//!GLFW Error Callback
		void error_callback(int error, const char* description)
		{
		std::cerr<<description<<std::endl;
		}

		//!GLFW framebuffer resize callback
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
		//!Resize the viewport to fit the window size - draw to entire window
		glViewport(0, 0, width, height);
		}

		//!GLFW keyboard callback
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		  glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		  state = !state;  // default perspective view (toggles perspective and ortho views)
		else if (key == GLFW_KEY_G && action == GLFW_PRESS)
		  global_state = !global_state;  // default perspective view (toggles perspective and ortho views)
		else if (key == GLFW_KEY_L && action == GLFW_PRESS)	//camera index toggle
		  curr_cam_index = (curr_cam_index + 1)%num_cams;
		else if (key == GLFW_KEY_J && action == GLFW_PRESS){	//camera index toggle
			curr_cam_index = curr_cam_index - 1;
			if(curr_cam_index<0){
				curr_cam_index += num_cams;
			}
			// curr_cam_index = curr_cam_index%num_cams;
		}

		else if (key == GLFW_KEY_LEFT)
		yrot -= 0.1;
		else if (key == GLFW_KEY_RIGHT)
		yrot += 0.1;
		else if (key == GLFW_KEY_UP)
		xrot += 0.1;
		else if (key == GLFW_KEY_DOWN)
		xrot -= 0.1;
		else if (key == GLFW_KEY_PAGE_UP)
		zrot += 0.1;
		else if (key == GLFW_KEY_PAGE_DOWN)
		zrot -= 0.1;
		else if(key == GLFW_KEY_A)
		xtrans += 0.1;
		else if(key == GLFW_KEY_D)
		xtrans -= 0.1;
		else if(key == GLFW_KEY_W)
		ytrans += 0.1;
		else if(key == GLFW_KEY_S)
		ytrans -= 0.1;
		else if(key == GLFW_KEY_Z)
		ztrans += 0.1;
		else if(key == GLFW_KEY_X)
		ztrans -= 0.1;
		else if(key == GLFW_KEY_K && action == GLFW_PRESS)
		{
			save_all();
		}
	}
};  
  



