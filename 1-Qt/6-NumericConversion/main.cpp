#include <QApplication>
#include "NumericConversion.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  NumericConversion nc;
  nc.show();
  return app.exec();
}
