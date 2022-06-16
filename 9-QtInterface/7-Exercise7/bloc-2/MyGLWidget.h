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
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void modelTransform1 ();
    virtual void modelTransform2 ();
    virtual void modelTransform3 ();
    virtual void resizeGL (int width, int height);
    virtual void mouseMoveEvent( QMouseEvent* event );

    Model m, l;

    GLuint projLoc, viewLoc, VAO_homer, VAO_Terra, VAO_Legoman, VBO_Terra[2];

    glm::vec3 OBS, VRP, up, min_value, max_value, center, patricioCenter, legomanCenter;
    glm::vec3 floorColor = {0, 1, 0};
    glm::vec3 backgroundColor = {0.5, 0.7, 1.0};
    QPoint ini_pos;
    float FOV, ra, znear, zfar, radi, distance, proj_top, proj_bottom, proj_left, proj_right, prewidth, preheight, patricioScale, legomanScale;
    float rotation_angle = 0;
    float angle_x = 0;
    float angle_y = 0;
    float inc = 0;
    bool perspective_view = true;
    bool patricio_activat = true;

  private:
    int printOglError(const char file[], int line, const char func[]);
    void projMatrixTransform();
    void viewMatrixTransform();
    void ini_camera();
    void CreaBuffersHomer();
    void CreaBuffersLegoman();
    void CreaBuffersTerra();
    void modelTransformTerra();
    void initialize_min_max();
    void initialize_min_max2();
    //void update_min_max(glm::vec3 posicio[]);
    void calculate_center_distance();
    void zoom();
    void updateFloorColor();
    void updateBackgroundColor();

    public slots:
      void setZoom(int num);
      void setPatricio();
      void setLegoman();
      void setPerspective();
      void setOrthographic();
      void setScale(int num);
      void setXAxis(int num);
      void setYAxis(int num);
      void setR(int num);
      void setG(int num);
      void setB(int num);
      void setbR(int num);
      void setbG(int num);
      void setbB(int num);

    signals:
      void getZoom(int);
      void sendPerspective(bool);
      void sendOrthographic(bool);
      void getScale(int);
      void getXAxis(int);
      void getYAxis(int);
};
