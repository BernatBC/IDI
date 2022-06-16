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
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);

    bool v_pressed = false;
    int cub = 1;
    int rot = 0;

    int left, right, bottom, top;

    public slots:
      void Cub1();
      void Cub2();
      void Cub3();
      void cam1();
      void cam2();

    signals:
      void send1(bool);
      void send2(bool);
      void send3(bool);
      void sendc1(bool);
      void sendc2(bool);

};
