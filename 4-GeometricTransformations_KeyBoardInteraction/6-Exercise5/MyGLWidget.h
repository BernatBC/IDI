#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <QKeyEvent>

#define GLM_FORCE_RADIANS

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();

    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);

    virtual void keyPressEvent(QKeyEvent *e);

  private:
    void creaBuffers ();
    void carregaShaders ();
    void modelTransform();

    float scale = 0;
    GLfloat posx = 0;
    GLfloat posy = 0;
    GLfloat angle = 0;

    // attribute locations
    GLuint vertexLoc;
    GLuint scaleLoc;
    GLuint matrixLoc;
    GLuint colorLoc;

    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1;
    GLint ample, alt;
};
