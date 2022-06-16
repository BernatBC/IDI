#include <QLCDNumber>

class MyLCDNumber: public QLCDNumber {
  Q_OBJECT

  public:
    MyLCDNumber(QWidget *parent);

  private:

  public slots:
  void set_value_colored(int num);
  void clear_LCD();

  signals:
};
