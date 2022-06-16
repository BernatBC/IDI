#include <QPushButton>
#include <iostream>
#include <vector>

class MyPushButton: public QPushButton {
  Q_OBJECT

  public:
    MyPushButton(QWidget *parent);

  private:
    int num;
    int adder;

    void setColor();

  public slots:
    void setRand();
    void changeColor(int a);

  signals:
};
