#include "ui_MagicDial.h"

class MagicDial:public QWidget {
  Q_OBJECT

public:
  MagicDial(QWidget *parent = 0);

private:
  Ui::MagicDial ui;
};
