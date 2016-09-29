#include "gl_framework.hpp"
#include "glm/vec3.hpp"

// extern GLfloat xrot,yrot,zrot;
// extern GLfloat xtrans, ytrans, ztrans;

extern GLfloat model_xrot,model_yrot,model_zrot;
extern GLfloat model_xtrans, model_ytrans, model_ztrans;

extern GLint state;
extern void save_file();

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
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      state = 0;  // default perspective view
  else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      state = 1;  //ortho view
  
  else if (key == GLFW_KEY_LEFT)
    model_yrot -= 0.1;
  else if (key == GLFW_KEY_RIGHT)
    model_yrot += 0.1;
  else if (key == GLFW_KEY_UP)
    model_xrot += 0.1;
  else if (key == GLFW_KEY_DOWN)
    model_xrot -= 0.1;
  else if (key == GLFW_KEY_PAGE_UP)
    model_zrot += 0.1;
  else if (key == GLFW_KEY_PAGE_DOWN)
    model_zrot -= 0.1;
  else if(key == GLFW_KEY_A)
    model_xtrans += 0.1;
  else if(key == GLFW_KEY_D)
    model_xtrans -= 0.1;
  else if(key == GLFW_KEY_W)
    model_ytrans += 0.1;
  else if(key == GLFW_KEY_S)
    model_ytrans -= 0.1;
  else if(key == GLFW_KEY_Z)
    model_ztrans += 0.1;
  else if(key == GLFW_KEY_X)
    model_ztrans -= 0.1;
  else if(key == GLFW_KEY_P && action == GLFW_PRESS)
    save_file();
      
}
};  
  



