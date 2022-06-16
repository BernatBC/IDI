#include <QLineEdit>
#include <iostream>
#include <vector>

class MyLineEdit: public QLineEdit {
  Q_OBJECT

  public:
    MyLineEdit(QWidget *parent);

  private:
    bool shiftPressed = false;

  public slots:
    void setA();
    void setE();
    void setI();
    void setO();
    void setU();
    void shift();

  signals:
};
