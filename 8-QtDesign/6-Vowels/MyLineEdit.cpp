#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget *parent):QLineEdit(parent) {
}

void MyLineEdit::setA() {
  if (shiftPressed) insert("A");
  else insert("a");
}
void MyLineEdit::setE() {
  if (shiftPressed) insert("E");
  else insert("e");
}
void MyLineEdit::setI() {
  if (shiftPressed) insert("I");
  else insert("i");
}
void MyLineEdit::setO() {
  if (shiftPressed) insert("O");
  else insert("o");
}
void MyLineEdit::setU() {
  if (shiftPressed) insert("U");
  else insert("u");
}
void MyLineEdit::shift() {
  shiftPressed = not shiftPressed;
}
