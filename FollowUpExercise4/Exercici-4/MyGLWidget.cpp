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

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_C: {
    if (colLlum1.x == 0) colLlum1 = glm::vec3(0.9, 0, 0.9);
    else colLlum1 = glm::vec3(0, 0, 0);
    glUniform3fv(colLlum1Loc, 1, &colLlum1[0]);
    break;
	}
  case Qt::Key_E: {
    if (colLlum2.x == 0) colLlum2 = glm::vec3(0.9, 0.9, 0.9);
    else colLlum2 = glm::vec3(0, 0, 0);
    glUniform3fv(colLlum2Loc, 1, &colLlum2[0]);
    break;
	}
  case Qt::Key_P: {
    if (colLlum3.x == 0) colLlum3 = glm::vec3(0.9, 0.9, 0.2);
    else colLlum3 = glm::vec3(0, 0, 0);
    glUniform3fv(colLlum3Loc, 1, &colLlum3[0]);
    break;
	}
  case Qt::Key_Right: {
      rotation_angle -= M_PI/6;
      glm::vec3 pos = TransformMatrixPatricio()*glm::vec4(centreBasePatr.x, maxYPat, centreBasePatr.z, 1);
      glUniform3fv(posLlum3Loc, 1, &pos[0]);
    break;
	}
  case Qt::Key_Left: {
      rotation_angle += M_PI/6;
      glm::vec3 pos = TransformMatrixPatricio()*glm::vec4(centreBasePatr.x, maxYPat, centreBasePatr.z, 1);
      glUniform3fv(posLlum3Loc, 1, &pos[0]);
    break;
	}
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::modelTransformPatricio ()
{
  glm::mat4 TG = TransformMatrixPatricio();
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

glm::mat4 MyGLWidget::TransformMatrixPatricio() {
  glm::mat4 TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3(5,0,5));
  TG = glm::rotate(TG, rotation_angle, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(0, 0, -3));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::translate(TG, -centreBasePatr);
  return TG;
}

void MyGLWidget::initializeGL() {
  LL4GLWidget::initializeGL();

  posLlum3Loc = glGetUniformLocation (program->programId(), "posLlum3");
  colLlum1Loc = glGetUniformLocation (program->programId(), "colLlum1");
  colLlum2Loc = glGetUniformLocation (program->programId(), "colLlum2");
  colLlum3Loc = glGetUniformLocation (program->programId(), "colLlum3");

  glUniform3fv(colLlum1Loc, 1, &colLlum1[0]);
  glUniform3fv(colLlum2Loc, 1, &colLlum2[0]);
  glUniform3fv(colLlum3Loc, 1, &colLlum3[0]);
  std::cerr << centreBasePatr.x << " " << maxYPat << " " << centreBasePatr.z << std::endl;
  glm::vec3 pos = TransformMatrixPatricio()*glm::vec4(centreBasePatr.x, maxYPat, centreBasePatr.z, 1);
  glUniform3fv(posLlum3Loc, 1, &pos[0]);
}
