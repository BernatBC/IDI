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

void MyGLWidget::viewTransform ()
{

    changeLights();

  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::carregaShaders()
{
    BL3GLWidget::carregaShaders();

    CF_Loc = glGetUniformLocation (program->programId(), "colorFocus");
    PF_Loc = glGetUniformLocation (program->programId(), "posFocus");
    F_Loc = glGetUniformLocation (program->programId(), "f");
    CF_Loc2 = glGetUniformLocation (program->programId(), "colorFocusAmb");
}

void MyGLWidget::initializeGL(){
    BL3GLWidget::initializeGL();

    colorFocus = glm::vec3(0.8, 0.8, 0.8);
    colorFocus2 = glm::vec3(0.8, 0.8, 0.8);
    posFocus = glm::vec3(0,0.5f,0); // En SCA

    changeLights();
}

void MyGLWidget::changeLights(){
    //std::cout << colorFocus.x << colorFocus.y << colorFocus.z << std::endl;
    glUniform3fv(CF_Loc, 1, &colorFocus[0]);
    glUniform3fv(PF_Loc, 1, &posFocus[0]);
    glUniform3fv(CF_Loc2, 1, &colorFocus2[0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / alt;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}


void MyGLWidget::iniMaterialTerra ()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.2,0,0.2);
  diff = glm::vec3(0,0,0.8);
  spec = glm::vec3(1,1,1);
  shin = 100;
}


void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
      case Qt::Key_F:
        f = not f;
        glUniform1i (F_Loc, f);
        break;
      case Qt::Key_Left:
        posX -= 0.02;
        posFocus = glm::vec3(posFocus.x - .02f, posFocus.y, posFocus.z);
        changeLights();
        break;
      case Qt::Key_Right:
        posX += 0.02;
        posFocus = glm::vec3(posFocus.x + .02f, posFocus.y, posFocus.z);
        changeLights();
        break;
      case Qt::Key_Up:
        posY -= 0.02;
        posFocus = glm::vec3(posFocus.x, posFocus.y, posFocus.z - 0.02f);
        changeLights();
        break;
      case Qt::Key_Down:
        posY += 0.02;
        posFocus = glm::vec3(posFocus.x, posFocus.y, posFocus.z + 0.02f);
        changeLights();
        break;
      case Qt::Key_1:
        if (colorFocus.x == 0) colorFocus = glm::vec3(0.8, 0.8, 0.8);
        else colorFocus = glm::vec3(0, 0, 0);
        changeLights();
        break;
      case Qt::Key_2:
        if (colorFocus2.x == 0) colorFocus2 = glm::vec3(0.8,0.8, 0.8);
        else colorFocus2 = glm::vec3(0, 0, 0);
        changeLights();
        break;
    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::modelTransformPatricio ()
{
  glm::mat4 TG = glm::mat4(1);
  TG = glm::translate(TG, glm::vec3(posX, -0.85, posY));
  TG = glm::scale(TG, glm::vec3(0.3*escala/2, 0.3*escala/2, 0.3*escala/2));
  TG = glm::translate(TG, -centrePatr);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}
