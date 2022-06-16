// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"
#define GLM_FORCE_RADIANS

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void carregaShaders ();
    virtual void initializeGL ( );
    virtual void paintGL ( );
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void modelTransform ();

    Model m;

    GLuint projLoc, viewLoc, VAO_homer, VAO_Terra;

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar;
    float rotation_angle = 0;

  private:
    int printOglError(const char file[], int line, const char func[]);
    void projMatrixTransform();
    void viewMatrixTransform();
    void ini_camera();
    void CreaBuffersHomer();
    void CreaBuffersTerra();
    void modelTransformTerra();
};
