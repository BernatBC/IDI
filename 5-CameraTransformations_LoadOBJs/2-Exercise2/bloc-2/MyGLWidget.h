// MyGLWidget.h
#include "BL2GLWidget.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void carregaShaders ();
    virtual void initializeGL ( );

    GLuint projLoc, viewLoc;

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar;

  private:
    int printOglError(const char file[], int line, const char func[]);
    void projMatrixTransform();
    void viewMatrixTransform();
    void ini_camera();
};
