#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void modelTransformPatricio ();
    virtual void enviaPosFocus ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);
    // Matriu de posició i orientació
    glm::mat4 View;
    // Matriu de transformació del model
    glm::mat4 TG;
    glm::vec3 posFoc;
    int rot = 0;
    bool focus = true;

    public slots:
    void Cam1();
    void Cam2();
    void Rotation(int r);

    signals:
    void setCam1(bool);
    void setCam2(bool);
    void setAngle(int);
};
