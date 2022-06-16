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
    bool backculling = false;

    GLint f = false;

    float posX = 0;
    float posY = 0;

    glm::vec3 posFocus;
    glm::vec3 colorFocus;
    glm::vec3 colorFocus2;

    GLuint CF_Loc, PF_Loc, F_Loc, CF_Loc2;

    void iniMaterialTerra ();
    void viewTransform();
    void carregaShaders();

    void initializeGL();
    void changeLights();
    void modelTransformPatricio();


  private:
    int printOglError(const char file[], int line, const char func[]);

};
