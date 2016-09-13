#include "gl_framework.hpp"
#include "glm/vec3.hpp"

extern GLfloat xrot,yrot,zrot;
extern glm::vec3 trans;
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
      state = 0;
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        state = 1;
    
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        state = 2;
    
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        state = 3;
    
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
        state = 4;
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
        state = 5;
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
        state = 6;
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
        state = 7;
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
        state = 8;
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
      zrot -= 1.0;
    else if(key == GLFW_KEY_A)
      trans[0] += 0.1;
    else if(key == GLFW_KEY_D)
      trans[0] -= 0.1;
    else if(key == GLFW_KEY_W)
      trans[1] += 0.1;
    else if(key == GLFW_KEY_S)
      trans[1] -= 0.1;
    else if(key == GLFW_KEY_Z)
      trans[2] += 0.1;
    else if(key == GLFW_KEY_X)
      trans[2] -= 0.1;
    else if(key == GLFW_KEY_P && action == GLFW_PRESS)
      save_file();
  }
};  
  



