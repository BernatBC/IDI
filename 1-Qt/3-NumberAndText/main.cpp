#include <QApplication>
#include "NumberAndText.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  NumberAndText num_text;
  num_text.show();
  return app.exec();
}
