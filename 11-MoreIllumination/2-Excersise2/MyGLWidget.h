// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    float angleX;

    glm::vec3 posFocus;
    glm::vec3 colorFocus;

    GLuint CF_Loc, PF_Loc;

    void iniMaterialTerra ();
    void viewTransform();
    void carregaShaders();

    void initializeGL();
    void changeLights();


  private:
    int printOglError(const char file[], int line, const char func[]);

};
