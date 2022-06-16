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

void MyGLWidget::iniEscena ()
{
  creaBuffersPatricio();
  creaBuffersTerra();
  creaBuffersCub();
  creaBuffersEsfera();

  // Paràmetres de l'escena - arbitraris
  centreEsc = glm::vec3 (15, 2, 10);
  radiEsc = sqrt(15*15+10*10+2*2);

  enviaPosFocus();
}

void MyGLWidget::enviaPosFocus()
{
  focus = not focus;
  if (focus) posFoc = glm::vec3(0,0,0);
  else posFoc = glm::vec3(View*glm::vec4(15,10,10,1));
  glUniform3fv (posfocusLoc, 1, &posFoc[0]);
}

void MyGLWidget::iniCamera ()
{
  angleY = 0;
  angleX = 0;
  camPlanta = false;
  ra = float(width())/height();
  fov = float(M_PI/3.0);
  zn = 15;
  zf = 65;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray (VAO_Patr);
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pintem l'arbre
  pintaArbre (glm::vec3(10,0,10));
  pintaArbre (glm::vec3(20,0,5));
  pintaArbre (glm::vec3(25,0,10));

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3 (10, 0, 10));
  TG = glm::rotate(TG, -rot*2*(float)M_PI/32, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3 (5, 0, 0));
  TG = glm::scale(TG, glm::vec3 (2*escala, 2*escala, 2*escala));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (!camPlanta) {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, glm::vec3(-centreEsc));
} else
  {
    View = glm::lookAt (glm::vec3(centreEsc.x, centreEsc.y + 2*radiEsc, centreEsc.z), centreEsc, glm::vec3(0, 0, -1));
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  if (!camPlanta) {
    Proj = glm::perspective(fov, ra, zn, zf);
} else
  {
    Proj = glm::ortho (-radiEsc, radiEsc, -radiEsc, radiEsc, zn, zf);
  }
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      rot = (rot + 1)%32;
      emit setAngle(rot);
    break;
	}
  case Qt::Key_F: {
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      camPlanta = not camPlanta;
      emit setCam1(not camPlanta);
      emit setCam2(camPlanta);
      viewTransform();
      projectTransform();
    break;
	}
  case Qt::Key_R: {
    initializeGL();
      rot = 0;
      iniCamera();
      emit setAngle(rot);
      emit setCam1(not camPlanta);
      emit setCam2(camPlanta);
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camPlanta)
  {
    // Fem la rotació
    angleX += (e->y() - yClick) * M_PI / alt;
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::Cam1() {
  makeCurrent();
  camPlanta = false;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::Cam2() {
  makeCurrent();
  camPlanta = true;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::Rotation(int r) {
  makeCurrent();
  rot = r;
  update();
}
