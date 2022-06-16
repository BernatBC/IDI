#include <QLabel>
#include <string>

class MyLabel: public QLabel {
  Q_OBJECT

  public:
    MyLabel(QWidget *parent);

  private:
    int vehicles = 0;
    int money = 0;
    bool open = true;

    void displayVehicles();
    void displayMoney();

  public slots:
    void newTruck();
    void newCarMoto();
    void addVehicle();
    void openBarrier();
    void closeBarrier();
    void setOpen();
    void setClose();


  signals:
};
