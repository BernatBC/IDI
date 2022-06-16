// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502:
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

void MyGLWidget::projMatrixTransform() {
  glm::mat4 project = glm::perspective(FOV, ra, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &project[0][0]);
}

void MyGLWidget::viewMatrixTransform() {
  glm::mat4 view = glm::lookAt(OBS, VRP, up);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

void MyGLWidget::ini_camera() {
  distance = 2*radi;
  OBS = glm::vec3(center[0], center[1], center[2] + distance);
  VRP = center;
  up = glm::vec3(0, 1, 0);
  FOV = 2*asin(radi/distance);
  znear = radi;
  zfar = 3*radi;
  ra = 1;
}

void MyGLWidget::resizeGL (int width, int height) {
  //BL2GLWidget::resizeGL(width, height);
  ra = (float)width/height;
  if (height > width) FOV = 2*glm::atan(glm::tan(asin(radi/distance))/ra);
  projMatrixTransform();
}

void MyGLWidget::initializeGL ( ) {
  BL2GLWidget::initializeGL();
  m.load("../models/HomerProves.obj");
  //initialize_min_max();
  calculate_center_distance();

  glEnable(GL_DEPTH_TEST);

  CreaBuffersHomer();
  CreaBuffersTerra();


  ini_camera();
  projMatrixTransform();
  viewMatrixTransform();
}

void MyGLWidget::carregaShaders () {
  BL2GLWidget::carregaShaders();
  projLoc = glGetUniformLocation(program->programId(), "projMatrix");
  viewLoc = glGetUniformLocation(program->programId(), "viewMatrix");
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();
  glBindVertexArray(VAO_homer);
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

  modelTransformTerra();
  glBindVertexArray(VAO_Terra);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray (0);
}

void MyGLWidget::CreaBuffersHomer() {
  glGenVertexArrays(1, &VAO_homer);
  glBindVertexArray(VAO_homer);

  GLuint VBO_Homer[2];
  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*9, m.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*9, m.VBO_matdiff(), GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  glBindVertexArray(0);
}

void MyGLWidget::CreaBuffersTerra() {
    // Dades de la caseta
    // Dos VBOs, un amb posició i l'altre amb color
    glm::vec3 posicio[6] = {
  	glm::vec3(0.5, 0.5, 0),
  	glm::vec3(-0.5,  0.5, 0),
  	glm::vec3(-0.5,  -0.5, 0),
    glm::vec3(0.5, 0.5, 0),
  	glm::vec3(-0.5,  -0.5, 0),
    glm::vec3(0.5,  -0.5, 0)
    };
    glm::vec3 color[6] = {
  	glm::vec3(0,1,0),
  	glm::vec3(0,1,0),
  	glm::vec3(0,1,0),
    glm::vec3(0,1,0),
  	glm::vec3(0,1,0),
  	glm::vec3(0,1,0)
    };

    //update_min_max(posicio);

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(2, VBO_Terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);
}

void MyGLWidget::calculate_center_distance() {
  max_value = glm::vec3(1, 1, 1);
  min_value = glm::vec3(-1, -1, -1);

  center = glm::vec3((min_value[0] + max_value[0])/2, (min_value[1] + max_value[1])/2, (min_value[2] + max_value[2])/2);
  radi = glm::sqrt((max_value[0] - center[0])*(max_value[0] - center[0]) + (max_value[1] - center[1])*(max_value[1] - center[1]) + (max_value[2] - center[2])*(max_value[2] - center[2]));
}
/*
void MyGLWidget::initialize_min_max() {
  std::cout << "initialize_min_max" << std::endl;
  min_value = glm::vec3(m.vertices()[0], m.vertices()[1], m.vertices()[2]);
  max_value = min_value;
  for (unsigned int i = 3; i < m.vertices().size(); i += 3) {
    if (m.vertices()[i] < min_value[0]) min_value[0] = m.vertices()[i];
    else if (m.vertices()[i] > max_value[0]) max_value[0] = m.vertices()[i];
    if (m.vertices()[i + 1] < min_value[1]) min_value[1] = m.vertices()[i + 1];
    else if (m.vertices()[i + 1] > max_value[1]) max_value[1] = m.vertices()[i + 1];
    if (m.vertices()[i + 2] < min_value[2]) min_value[2] = m.vertices()[i + 2];
    else if (m.vertices()[i + 2] > max_value[2]) max_value[2] = m.vertices()[i + 2];
  }
  std::cout << "(x, y, z) = (" << max_value[0] << ", " << max_value[1] << ", " << max_value[2] << ")" << std::endl;
  std::cout << "(x, y, z) = (" << min_value[0] << ", " << min_value[1] << ", " << min_value[2] << ")" << std::endl;
  }

void MyGLWidget::update_min_max(glm::vec3 posicio[]) {
  std::cout << "update_min_max" << std::endl;
  for (unsigned int i = 0; i < sizeof(posicio); ++i) {
    if (posicio[i][0] < min_value[0]) min_value[0] = posicio[i][0];
    else if (posicio[i][0] > max_value[0]) max_value[0] = posicio[i][0];
    if (posicio[i][1] < min_value[1]) min_value[1] = posicio[i][1];
    else if (posicio[i][1] > max_value[1]) max_value[1] = posicio[i][1];
    if (posicio[i][2] < min_value[2]) min_value[2] = posicio[i][2];
    else if (posicio[i][2] > max_value[2]) max_value[2] = posicio[i][2];
  }
  center = glm::vec3((min_value[0] + max_value[0])/2, (min_value[1] + max_value[1])/2, (min_value[2] + max_value[2])/2);
  float aux = glm::sqrt((max_value[0] - center[0])*(max_value[0] - center[0]) + (max_value[1] - center[1])*(max_value[1] - center[1]) + (max_value[2] - center[2])*(max_value[2] - center[2]));
  std::cout << "(x, y, z) = (" << max_value[0] << ", " << max_value[1] << ", " << max_value[2] << ")" << std::endl;
  std::cout << "(x, y, z) = (" << center[0] << ", " << center[1] << ", " << center[2] << ")" << std::endl;
  std::cout << "radi: " << aux << std::endl;
}*/

void MyGLWidget::modelTransform ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, rotation_angle, glm::vec3(0, 1, 0));
  transform = glm::scale(transform, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    }
    case Qt::Key_R: { // escalar a més petit
      rotation_angle += M_PI/4;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::modelTransformTerra() {
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(4, 1, 4));
  transform = glm::translate(transform, glm::vec3(0, -1, 0));
  transform = glm::rotate(transform, (float)M_PI/2, glm::vec3(1, 0, 0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

MyGLWidget::~MyGLWidget() {
}
