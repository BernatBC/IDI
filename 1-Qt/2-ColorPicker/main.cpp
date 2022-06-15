#include <QApplication>
#include "ColorPicker.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  ColorPicker cp;
  cp.show();
  return app.exec();
}
