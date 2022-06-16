// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
  private:
    GLuint posLlum3Loc, colLlum1Loc, colLlum2Loc, colLlum3Loc;
    float rotation_angle = 0;
    glm::vec3 colLlum1 = glm::vec3(0.9, 0, 0.9);
    glm::vec3 colLlum2 = glm::vec3(0.9, 0.9, 0.9);
    glm::vec3 colLlum3 = glm::vec3(0.9, 0.9, 0.2);
    int printOglError(const char file[], int line, const char func[]);
    void modelTransformPatricio();
    void initializeGL();

    glm::mat4 TransformMatrixPatricio();
};
