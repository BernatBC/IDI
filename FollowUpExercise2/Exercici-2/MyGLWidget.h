#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    void iniCamera();
    void projectTransform();
    void viewTransform();
    void paintGL();
    void patrTransform();
    void paret1Transform();
    void paret2Transform();
    void paret3Transform();
    void calculateRadi();
    void mouseMoveEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* event);
    float patrHeight();
    void rebotaParets();
    void tractamentGol();
    void resizeGL(int w, int h);

    float distance, proj_top, proj_bottom, proj_left, proj_right;
    float angleX = (float)M_PI/4;
    float angleY = 0;
    bool goal = false;
    bool prespective = true;
};
