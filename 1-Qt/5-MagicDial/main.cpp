#include "QApplication"
#include "MagicDial.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  MagicDial md;
  md.show();
  return app.exec();
}
