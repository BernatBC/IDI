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
    virtual void resizeGL (int width, int height);

    Model m;

    GLuint projLoc, viewLoc, VAO_homer, VAO_Terra;

    glm::vec3 OBS, VRP, up, min_value, max_value, center;
    float FOV, ra, znear, zfar, radi, distance, proj_top, proj_bottom, proj_left, proj_right;
    float rotation_angle = 0;
    bool perspective_view = true;

  private:
    int printOglError(const char file[], int line, const char func[]);
    void projMatrixTransform();
    void viewMatrixTransform();
    void ini_camera();
    void CreaBuffersHomer();
    void CreaBuffersTerra();
    void modelTransformTerra();
    void initialize_min_max();
    //void update_min_max(glm::vec3 posicio[]);
    void calculate_center_distance();
};
