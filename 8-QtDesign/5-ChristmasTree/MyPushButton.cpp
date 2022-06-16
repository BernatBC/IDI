#include "MyPushButton.h"

MyPushButton::MyPushButton(QWidget *parent):QPushButton(parent) {
  num = rand()%4;
  setColor();
}

void MyPushButton::setRand() {
  num = rand()%4;
  setColor();
}

void MyPushButton::changeColor(int a) {
  adder = a;
  setColor();
}

void MyPushButton::setColor() {
  int c = (num + adder)%4;
  if (c == 0) setStyleSheet("background: pink");
  else if (c == 1) setStyleSheet("background: black");
  else if (c == 2) setStyleSheet("background: blue");
  else setStyleSheet("background: green");
}
