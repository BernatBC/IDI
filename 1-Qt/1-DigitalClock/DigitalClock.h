#include "ui_DigitalClock.h"

class DigitalClock : public QWidget {
  Q_OBJECT

public:
  DigitalClock(QWidget * parent = 0);

private:
  Ui::DigitalClock ui;
};
