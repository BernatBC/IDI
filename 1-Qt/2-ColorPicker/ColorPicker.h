#include "ui_ColorPicker.h"

class ColorPicker : public QWidget {
  Q_OBJECT

public:
  ColorPicker(QWidget *parent = 0);

private:
  Ui::ColorPicker ui;
};
