#include <QPushButton>
#include <QKeyEvent>
#include <iostream>
#include <vector>

class MyPushButton: public QPushButton {
  Q_OBJECT

  public:
    MyPushButton(QWidget *parent);

  private:
    int nTriplets = 0;
    int value1, value2, value3;
    void check();

  public slots:
    void setColor(int num);
    void pressed1();
    void pressed2();
    void pressed3();
    void start();
    void reset();

  signals:
    void sendNum(int);
    void emit1(int);
    void emit2(int);
    void emit3(int);
};
