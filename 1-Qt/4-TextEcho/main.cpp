#include "QApplication"
#include "TextEcho.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  TextEcho te;
  te.show();
  return app.exec();
}
