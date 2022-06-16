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

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (v_pressed) {
    // Pintem el Patricio
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  else {
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.0, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    modelTransformCub (2.5, 2*M_PI/3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelTransformCub (3, 4*M_PI/3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  // Pintem el cub

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle)
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angle + rot*2*(float)M_PI/3, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 0));
  TG = glm::scale(TG, glm::vec3 (2*escala, 2*escala, 2*escala));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, -2*(cub - 1)*(float)M_PI/3 + rot*2*(float)M_PI/3, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 1));
  TG = glm::rotate(TG, -(float)M_PI/2, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3 (2*escala, 2*escala, 2*escala));
  TG = glm::translate(TG, glm::vec3(-centreBasePat.x, -centreBasePat.y, -centreBasePat.z));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    View = glm::lookAt (glm::vec3(centreEsc.x, centreEsc.y + 2*radiEsc, centreEsc.z), centreEsc, glm::vec3(0,0,1));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 Proj = glm::ortho (-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, 3*radiEsc);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);

  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      v_pressed = not v_pressed;
    break;
	}
  case Qt::Key_1: {
      cub = 1;
      emit send1(true);
      emit send2(false);
      emit send3(false);
    break;
	}
  case Qt::Key_2: {
      cub = 2;
      emit send1(false);
      emit send2(true);
      emit send3(false);
    break;
	}
  case Qt::Key_3: {
      cub = 3;
      emit send1(false);
      emit send2(false);
      emit send3(true);
    break;
	}
  case Qt::Key_F: {
      if (colFoc.y == 1) colFoc.y = 0;
      else colFoc.y = 1;
      glUniform3fv (colfocusLoc, 1, &colFoc[0]);
    break;
	}
  case Qt::Key_C: {
      camPlanta = not camPlanta;
      emit sendc1(not camPlanta);
      emit sendc2(camPlanta);
      viewTransform();
      projectTransform();
    break;
	}
  case Qt::Key_Right: {
      ++rot;
    break;
	}
  case Qt::Key_Left: {
      --rot;
    break;
	}
  case Qt::Key_R: {
      initializeGL();
      emit send1(true);
      emit send2(false);
      emit send3(false);
      emit sendc1(true);
      emit sendc2(false);
      v_pressed = false;
      cub = 1;
      rot = 0;
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::Cub1() {
  makeCurrent();
  cub = 1;
  update();
}

void MyGLWidget::Cub2() {
  makeCurrent();
  cub = 2;
  update();
}

void MyGLWidget::Cub3() {
  makeCurrent();
  cub = 3;
  update();
}

void MyGLWidget::cam1() {
  makeCurrent();
  camPlanta = false;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::cam2() {
  makeCurrent();
  camPlanta = true;
  viewTransform();
  projectTransform();
  update();
}
