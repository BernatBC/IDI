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
  OBS = glm::vec3(0, 0, 1);
  VRP = glm::vec3(0, 0, 0);
  up = glm::vec3(0, 1, 0);
  FOV = float(M_PI)/2.0f;
  ra = 1.0f;
  znear = 0.4f;
  zfar = 3.0f;
  projMatrixTransform();
  viewMatrixTransform();
}

void MyGLWidget::initializeGL ( ) {
  BL2GLWidget::initializeGL();
  m.load("../models/HomerProves.obj");

  glEnable(GL_DEPTH_TEST);

  CreaBuffersHomer();
  CreaBuffersTerra();

  ini_camera();
}

void MyGLWidget::carregaShaders () {
  BL2GLWidget::carregaShaders();
  projLoc = glGetUniformLocation(program->programId(), "projMatrix");
  viewLoc = glGetUniformLocation(program->programId(), "viewMatrix");
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els par??metres del viewport, descomenteu la crida seg??ent i
// useu els par??metres que considereu (els que hi ha s??n els de per defecte)
//  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformaci?? de model
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
    // Dos VBOs, un amb posici?? i l'altre amb color
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

    // Creaci?? del Vertex Array Object per pintar
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

void MyGLWidget::modelTransform ()
{
  // Matriu de transformaci?? de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, rotation_angle, glm::vec3(0, 1, 0));
  transform = glm::scale(transform, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a m??s gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a m??s petit
      escala -= 0.05;
      break;
    }
    case Qt::Key_R: { // escalar a m??s petit
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
