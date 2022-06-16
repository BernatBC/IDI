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

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::iniCamera(){
  calculateRadi();
  distance = 2*radiEscena;
  obs = {centreEscena.x, centreEscena.y, centreEscena.z + distance};
  vrp = centreEscena;
  up = glm::vec3(0, 1, 0);
  fov = 2*asin(radiEscena/distance);
  ra  = 1.0;
  znear = radiEscena;
  zfar = 3*radiEscena;

  proj_bottom = -radiEscena/ra;
  proj_top = radiEscena/ra;
  proj_left = -radiEscena*ra;
  proj_right = radiEscena*ra;

  viewTransform();
  projectTransform();
}

void MyGLWidget::projectTransform() {
  glm::mat4 Proj(1.0f);
  if (prespective) Proj = glm::perspective (fov, ra, znear, zfar);
  else Proj = glm::ortho(proj_left, proj_right, proj_bottom, proj_top, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform() {
  glm::mat4 view(1);
  if (prespective) {
    view = glm::translate(view, glm::vec3(0, 0, -distance));
    view = glm::rotate(view, angleX, glm::vec3(1, 0, 0));
    view = glm::rotate(view, -angleY, glm::vec3(0, 1, 0));
    view = glm::translate(view, -vrp);
  }
  else view = glm::lookAt({vrp.x, vrp.y + distance, vrp.z}, vrp, {-1, 0, 0});
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

void MyGLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Patricio
  glBindVertexArray (VAO_Patr);
  patrTransform();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pilota
  if (not goal) {
    glBindVertexArray (VAO_Pil);
    pilTransform();
    glDrawArrays(GL_TRIANGLES, 0, pil.faces().size()*3);
  }

  // Parets
  glBindVertexArray (VAO_Cub);
  //Paret1
  paret1Transform();
  glDrawArrays(GL_TRIANGLES, 0, 36);
  //Paret2
  paret2Transform();
  glDrawArrays(GL_TRIANGLES, 0, 36);
  //Paret3
  paret3Transform();
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::mouseMoveEvent( QMouseEvent* e )
{
    // The user is moving the cursor.
    // See if the user is pressing down the left mouse button.
makeCurrent();
    if ( e->buttons() & Qt::LeftButton )
    {
        angleY -= (float)factorAngleX*(e->pos().x() - xClick);
        angleX += (float)factorAngleY*(e->pos().y() - yClick);

        xClick = e->pos().x();
        yClick = e->pos().y();
        viewTransform();
    }

    update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { // moviment de la pilota
      if (posPilota[0] == 7.0)
        mourePilota ();
      break;
    }
    case Qt::Key_I: { // reinicia posició pilota
      iniciPilota ();
      goal = false;
      break;
    }
    case Qt::Key_Right: { // mou Patricio 0.5 unitats dreta
      if (posPorter.z > altPorter/2 - 7) posPorter.z -= 0.5;
      break;
    }
    case Qt::Key_Left: { // mou Patricio 0.5 unitats esquerra
      if (posPorter.z < 7 - altPorter/2) posPorter.z += 0.5;
      break;
    }
    case Qt::Key_C: { // canvia prespectiva
      prespective = not prespective;
      viewTransform();
      projectTransform();
      break;
    }
    case Qt::Key_W: { // incrementar alçada patricio
      if (altPorter < 6) ++altPorter;
      break;
    }
    case Qt::Key_S: { // disminuir alçada patricio
      if (altPorter > 2) --altPorter;
      break;
    }
    case Qt::Key_R: { // reiniciar escena
      altPorter = 4;
      prespective = true;
      angleX = (float)M_PI/4;
      angleY = 0;
      iniciPilota ();
      goal = false;
      viewTransform();
      projectTransform();
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::patrTransform ()
{
  float height = patrHeight();
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posPorter);
  TG = glm::scale(TG, {altPorter/height, altPorter/height, altPorter/height});
  TG = glm::rotate(TG, (float)-M_PI/2, {0, 1, 0});
  TG = glm::translate(TG, -centreBasePatr);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paret1Transform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, {0, 0, -6.9f});
  TG = glm::scale(TG, {20, 2, 0.2f});
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paret2Transform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, {0, 0, 6.9f});
  TG = glm::scale(TG, {20, 2, 0.2f});
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paret3Transform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, {-9.9f, 0, 0});
  TG = glm::scale(TG, {0.2f, 2, 14});
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::calculateRadi() {
  glm::vec3 max_value = glm::vec3(10, altPorter, 7);
  glm::vec3 min_value = glm::vec3(-10, 0, -7);
  centreEscena = glm::vec3((min_value[0] + max_value[0])/2, (min_value[1] + max_value[1])/2, (min_value[2] + max_value[2])/2);
  radiEscena = glm::sqrt((max_value[0] - centreEscena[0])*(max_value[0] - centreEscena[0]) + (max_value[1] - centreEscena[1])*(max_value[1] - centreEscena[1]) + (max_value[2] - centreEscena[2])*(max_value[2] - centreEscena[2]));
}

float MyGLWidget::patrHeight() {
  float minvalue = patr.vertices()[1];
  float maxvalue = minvalue;
  for (unsigned int i = 3; i < patr.vertices().size(); i += 3) {
    if (patr.vertices()[i + 1] < minvalue) minvalue = patr.vertices()[i + 1];
    else if (patr.vertices()[i + 1] > maxvalue) maxvalue = patr.vertices()[i + 1];
  }
  return maxvalue - minvalue;
}

void MyGLWidget::rebotaParets() {
  if (posPilota.x < -9) dirPilota.x = -dirPilota.x;
  else if (posPilota.z < -5.5 or posPilota.z > 5.5) dirPilota.z = -dirPilota.z;
}

void MyGLWidget::tractamentGol() {
  goal = true;
  timer.stop();
}

void MyGLWidget::resizeGL (int w, int h) {
  ra = (float)w/h;
  if (h > w) fov = 2*glm::atan(glm::tan(asin(radiEscena/distance))/ra);

  if (h > w) {
    proj_bottom = -radiEscena/ra;
    proj_top = radiEscena/ra;
  }
  else {
    proj_left = -radiEscena*ra;
    proj_right = radiEscena*ra;
  }

  factorAngleY = M_PI / w;
  factorAngleX = M_PI / h;

  projectTransform();
}
