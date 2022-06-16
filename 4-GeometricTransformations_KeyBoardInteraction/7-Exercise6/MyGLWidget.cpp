
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  //modelTransform(false, 0);
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {
  makeCurrent();

  if (e->key() == Qt::Key_Left) {
    posx -= 0.1;
    angle += M_PI/4;
    angle2 -= M_PI/4;
  }
  else if (e->key() == Qt::Key_Right) {
    posx += 0.1;
    angle += M_PI/4;
    angle2 -= M_PI/4;
  }
  else if (e->key() == Qt::Key_Up) {
    posy += 0.1;
    angle += M_PI/4;
    angle2 -= M_PI/4;
  }
  else if (e->key() == Qt::Key_Down) {
    posy -= 0.1;
    angle += M_PI/4;
    angle2 -= M_PI/4;
  }
  else if (e->key() == Qt::Key_S) scale -= 0.01;
  else if (e->key() == Qt::Key_D) scale += 0.01;
  else e->ignore();
  update();
}

void MyGLWidget::modelTransform() {
  glm::mat4 TG(1);
  TG = glm::translate(TG, glm::vec3(posx - 0.5, posy, 0.5));
  TG = glm::scale(TG, glm::vec3(scale, scale*0.5, scale));
  TG = glm::rotate(TG, angle, glm::vec3(0, 0, 1));
  glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::modelTransform2() {
  glm::mat4 TG(1);
  TG = glm::translate(TG, glm::vec3(posx + 0.5, posy, 0.5));
  TG = glm::scale(TG, glm::vec3(scale, scale*0.5, scale));
  TG = glm::rotate(TG, angle2, glm::vec3(0, 0, 1));
  glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

  modelTransform();

  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Activem l'Array a pintar
  glBindVertexArray(VAO1);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  modelTransform2();



  // Activem l'Array a pintar
  glBindVertexArray(VAO1);

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void MyGLWidget::creaBuffers ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.0, 1.0, 0.0);

  glm::vec3 Colors[3];  // Tres vèrtexs amb X, Y i Z
  Colors[0] = glm::vec3(1, 0, 0);
  Colors[1] = glm::vec3(0, 1, 0);
  Colors[2] = glm::vec3(0, 0, 1);

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "ColorIN");
  matrixLoc = glGetUniformLocation (program->programId(), "TG");
}
