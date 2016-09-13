/*
  CSX75 Tutorial 3

  A program which opens a window and draws the "color cube."

  Use the arrow keys and +/-, PgUp,PgDn, Home,End, Ins,Del 
  keys to make the cube move.

  Use w/W to toggle between wireframe and solid models
  Use c/C to toggle backface culling on/off

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/


#include "03_colorcube_rotate.hpp"

GLuint shaderProgram;
GLuint vbo[4],vao[4];

glm::mat4 global_translation_matrix;
glm::mat4 global_rotation_matrix;
glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 translation_matrix;
glm::mat4 scaling_matrix;
glm::mat4 modelview_matrix;
glm::mat4 wcs_to_vcs_matrix;
glm::mat4 vcs_to_ccs_matrix;
glm::mat4 ccs_to_ndcs_matrix;
glm::mat4 ndcs_to_dcs_matrix;


GLuint uModelViewMatrix;
GLuint state_shader;

//-----------------------------------------------------------------

void load(std::string model, std::vector<glm::vec4> &model_positions, std::vector<glm::vec4> &model_colors){
  // model+=".raw";
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

void load_frustum(){
  glm::vec3 n=normalize(eye-lookAt);
  glm::vec3 u=normalize(cross(up,n));
  glm::vec3 v=cross(n,u);
  glm::vec3 e;
  e[0]=-dot(u,eye);
  e[1]=-dot(v,eye);
  e[2]=-dot(n,eye);
  wcs_to_vcs_matrix[0]=glm::vec4(u[0],v[0],n[0],0.0f);
  wcs_to_vcs_matrix[1]=glm::vec4(u[1],v[1],n[1],0.0f);
  wcs_to_vcs_matrix[2]=glm::vec4(u[2],v[2],n[2],0.0f);
  wcs_to_vcs_matrix[3]=glm::vec4(e[0],e[1],e[2],1.0f);
  std::vector <glm::vec4> frustum_vertices;
  N=-N;F=-F;
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(-L,-B,N,1.0f)));
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(-L,T,N,1.0f)));
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(R,T,N,1.0f)));
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(R,-B,N,1.0f)));

  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(-L*F/N,-B*F/N,F,1.0f)));
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(-L*F/N,T*F/N,F,1.0f)));
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(R*F/N,T*F/N,F,1.0f)));
  frustum_vertices.push_back(inverse(wcs_to_vcs_matrix)*(glm::vec4(R*F/N,-B*F/N,F,1.0f)));

  frustum_positions.push_back(frustum_vertices[1]);
  frustum_positions.push_back(frustum_vertices[2]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[2]);
  frustum_positions.push_back(frustum_vertices[3]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[3]);
  frustum_positions.push_back(frustum_vertices[0]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[0]);
  frustum_positions.push_back(frustum_vertices[1]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[5]);
  frustum_positions.push_back(frustum_vertices[6]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[6]);
  frustum_positions.push_back(frustum_vertices[7]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[7]);
  frustum_positions.push_back(frustum_vertices[4]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[4]);
  frustum_positions.push_back(frustum_vertices[5]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[1]);
  frustum_positions.push_back(frustum_vertices[5]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[2]);
  frustum_positions.push_back(frustum_vertices[6]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[0]);
  frustum_positions.push_back(frustum_vertices[4]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[3]);
  frustum_positions.push_back(frustum_vertices[7]);
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(0.0f,1.0f,1.0f,1.0f));

  //eye to nr plane
  frustum_positions.push_back(frustum_vertices[0]);
  frustum_positions.push_back(glm::vec4(eye,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[1]);
  frustum_positions.push_back(glm::vec4(eye,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[2]);
  frustum_positions.push_back(glm::vec4(eye,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));

  frustum_positions.push_back(frustum_vertices[3]);
  frustum_positions.push_back(glm::vec4(eye,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,1.0f,1.0f));

  frustum_positions.push_back(glm::vec4(eye,1.0f));
  frustum_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
  N=-N;F=-F;
}

void save_file()
{
  std::ofstream scene_saver;
  scene_saver.open("scene.pts", std::ios::out);
  // std::cout <<"kunal"<<std::endl;
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
  std::string model1,model2,model3;
  std::ifstream scene_loader;
  scene_loader.open("myscene1.scn");
  if(scene_loader.is_open()){
    scene_loader>>model1;
    load(model1,model1_positions,model1_colors);
    scene_loader>>scale1[0]>>scale1[1]>>scale1[2];
    scene_loader>>xrot1>>yrot1>>zrot1;
    scene_loader>>trans1[0]>>trans1[1]>>trans1[2];

    scene_loader>>eye[0]>>eye[1]>>eye[2];
    scene_loader>>lookAt[0]>>lookAt[1]>>lookAt[2];
    scene_loader>>up[0]>>up[1]>>up[2];

    scene_loader>>L>>R>>T>>B>>N>>F;
     N=N; F=F;
    load_frustum();

     L=-L;B=-B;

    vcs_to_ccs_matrix[0] = glm::vec4(2*N/(R-L), 0.0f, 0.0f, 0.0f);
    vcs_to_ccs_matrix[1] = glm::vec4(0.0f, 2*N/(T-B), 0.0f, 0.0f);
    vcs_to_ccs_matrix[2] = glm::vec4((R+L)/(R-L), (T+B)/(T-B), -(F+N)/(F-N), -1.0f);
    vcs_to_ccs_matrix[3] = glm::vec4(0.0f, 0.0f, -2*F*N/(F-N), 0.0f);

    glm::mat4 dcs1;
    dcs1[0] = glm::vec4((Rw-Lw)/2, 0.0f,0.0f,0.0f);
    dcs1[1] = glm::vec4(0.0f, (Tw-Bw)/2,0.0f,0.0f);
    dcs1[2] = glm::vec4(0.0f, 0.0f,0.5f,0.0f);
    dcs1[3] = glm::vec4(0.0f, 0.0f,0.0f,1.0f);

    glm::mat4 dcs2;
    dcs2[0] = glm::vec4(1.0f, 0.0f,0.0f,0.0f);
    dcs2[1] = glm::vec4(0.0f, 1.0f,0.0f,0.0f);
    dcs2[2] = glm::vec4(0.0f, 0.0f,1.0f,0.0f);
    dcs2[3] = glm::vec4((Rw+Lw)/2, (Tw+Bw)/2,0.5f,1.0f);

    ndcs_to_dcs_matrix = dcs2*dcs1;

  }
  else{std::cout<< "could not find file myscene.scn"<<std::endl;}

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
  glGenVertexArrays (4, vao);
  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (4, vbo);

   //Set it as the current array to be used by binding it
  glBindVertexArray (vao[0]);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);

  //Copy the points into the current buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBufferData (GL_ARRAY_BUFFER, model1_positions.size()*sizeof(glm::vec4)+ model1_colors.size()*sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, model1_positions.size()*sizeof(glm::vec4), &model1_positions[0]);
  glBufferSubData( GL_ARRAY_BUFFER, model1_positions.size()*sizeof(glm::vec4),model1_colors.size()*sizeof(glm::vec4), &model1_colors[0]);
 
  glEnableVertexAttribArray( vPosition );
 //  glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_ALWAYS);
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model1_positions.size()*sizeof(glm::vec4)) );
  

  //Model 2
  glBindVertexArray (vao[1]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[1]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBufferData (GL_ARRAY_BUFFER, model2_positions.size()*sizeof(glm::vec4)+ model2_colors.size()*sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, model2_positions.size()*sizeof(glm::vec4), &model2_positions[0]);
  glBufferSubData( GL_ARRAY_BUFFER, model2_positions.size()*sizeof(glm::vec4),model2_colors.size()*sizeof(glm::vec4), &model2_colors[0]);
 
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model2_positions.size()*sizeof(glm::vec4)) );

  //Model 3
  glBindVertexArray (vao[2]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[2]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBufferData (GL_ARRAY_BUFFER, model3_positions.size()*sizeof(glm::vec4)+ model3_colors.size()*sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, model3_positions.size()*sizeof(glm::vec4), &model3_positions[0]);
  glBufferSubData( GL_ARRAY_BUFFER, model3_positions.size()*sizeof(glm::vec4),model3_colors.size()*sizeof(glm::vec4), &model3_colors[0]);
 
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model3_positions.size()*sizeof(glm::vec4)) );

  //frustum
  glBindVertexArray (vao[3]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[3]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBufferData (GL_ARRAY_BUFFER, frustum_positions.size()*sizeof(glm::vec4)+ frustum_colors.size()*sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, frustum_positions.size()*sizeof(glm::vec4), &frustum_positions[0]);
  glBufferSubData( GL_ARRAY_BUFFER, frustum_positions.size()*sizeof(glm::vec4),frustum_colors.size()*sizeof(glm::vec4), &frustum_colors[0]);
 
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(frustum_positions.size()*sizeof(glm::vec4)) );

}

void renderGL(void){

  global_translation_matrix = glm::translate(glm::mat4(1.0f), trans);
  global_rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
  global_rotation_matrix = glm::rotate(global_rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
  global_rotation_matrix = glm::rotate(global_rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
  //MODEL 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  scaling_matrix = glm::scale(glm::mat4(1.0f), scale1);
  translation_matrix = glm::translate(glm::mat4(1.0f), trans1);
  rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot1, glm::vec3(1.0f,0.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, yrot1, glm::vec3(0.0f,1.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, zrot1, glm::vec3(0.0f,0.0f,1.0f));
  ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);



  modelview_matrix =  translation_matrix * scaling_matrix * rotation_matrix;
  if (state==0){
      modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix *modelview_matrix;}
  else if(state ==1){
    modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix * wcs_to_vcs_matrix * modelview_matrix;
  }
  else if (state==2 || state == 3){
    modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix *vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  }
  else if (state==4){
    modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix* ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  }
  else if (state==5){
    modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix * inverse(wcs_to_vcs_matrix);
  }
  else if (state==6){
    modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix* inverse(ndcs_to_dcs_matrix) * inverse(vcs_to_ccs_matrix) *inverse(wcs_to_vcs_matrix) * modelview_matrix;
  }
  else if (state==7){
    modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix* ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  }
  else if (state==8){
    modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix* ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  }
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniform1i(state_shader,state);

  glBindVertexArray (vao[0]);
  // glDrawArrays(GL_TRIANGLES, 0, model1_positions.size());
  glDrawArrays(GL_POINTS, 0, model1_positions.size());

  //MODEL 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // scaling_matrix = glm::scale(glm::mat4(1.0f), scale2);
  // translation_matrix = glm::translate(glm::mat4(1.0f), trans2);
  // rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot2, glm::vec3(1.0f,0.0f,0.0f));
  // rotation_matrix = glm::rotate(rotation_matrix, yrot2, glm::vec3(0.0f,1.0f,0.0f));
  // rotation_matrix = glm::rotate(rotation_matrix, zrot2, glm::vec3(0.0f,0.0f,1.0f));
  // ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);

  // modelview_matrix = translation_matrix * scaling_matrix * rotation_matrix;
  // if (state==0){
  //     modelview_matrix = ortho_matrix * global_translation_matrix * global_rotation_matrix*modelview_matrix;}
  // else if(state ==1){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* wcs_to_vcs_matrix * modelview_matrix;
  // }
  // else if (state==2 || state==3){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  // }
  // else if (state==4){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  // }
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // glUniform1i(state_shader,state);

  // glBindVertexArray (vao[1]);
  // glDrawArrays(GL_TRIANGLES, 0, model2_positions.size());

  //MODEL 3~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // scaling_matrix = glm::scale(glm::mat4(1.0f), scale3);
  // translation_matrix = glm::translate(glm::mat4(1.0f), trans3);
  // rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot3, glm::vec3(1.0f,0.0f,0.0f));
  // rotation_matrix = glm::rotate(rotation_matrix, yrot3, glm::vec3(0.0f,1.0f,0.0f));
  // rotation_matrix = glm::rotate(rotation_matrix, zrot3, glm::vec3(0.0f,0.0f,1.0f));
  // ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);

  // modelview_matrix =   translation_matrix * scaling_matrix * rotation_matrix;
  // if (state==0){
  //     modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* modelview_matrix;}
  // else if(state ==1){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* wcs_to_vcs_matrix * modelview_matrix;
  // }
  // else if (state==2|| state==3){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  // }
  // else if (state==4){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  // }
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // glUniform1i(state_shader,state);

  // glBindVertexArray (vao[2]);
  // glDrawArrays(GL_TRIANGLES, 0, model3_positions.size());

   //FRUSTUM~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);

  // modelview_matrix =  glm::mat4(1.0f) ;
  // if (state==0){
  //     modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix* modelview_matrix;
  // }
  // else if(state ==1){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix*wcs_to_vcs_matrix * modelview_matrix;
  // }
  // else if (state==2 || state==3){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix*vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  // }
  // else if (state==4){
  //   modelview_matrix = ortho_matrix *global_translation_matrix * global_rotation_matrix*ndcs_to_dcs_matrix * vcs_to_ccs_matrix *wcs_to_vcs_matrix * modelview_matrix;
  // }
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // glUniform1i(state_shader,state);

  // glBindVertexArray (vao[3]);
  // glDrawArrays(GL_LINES, 0, frustum_positions.size()-1);
  // glDrawArrays(GL_POINTS, frustum_positions.size()-1, frustum_positions.size());
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


