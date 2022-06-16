#include "MyPushButton.h"

MyPushButton::MyPushButton(QWidget *parent):QPushButton(parent) {
  emit sendNum(0);
  emit emit1(-1);
  emit emit2(-1);
  emit emit3(-1);
}

void MyPushButton::setColor(int num) {
  if (num == -1) setStyleSheet("background: rgb(124, 124, 124)");
  else if (num == 0) setStyleSheet("background: red");
  else if (num == 1) setStyleSheet("background: yellow");
  else if (num == 2) setStyleSheet("background: blue");
  else setStyleSheet("background: green");
}

void MyPushButton::pressed1() {
  value1 = rand()%4;
  emit emit1(value1);
  check();
}

void MyPushButton::pressed2() {
  value2 = rand()%4;
  emit emit2(value2);
  check();
}

void MyPushButton::pressed3() {
  value3 = rand()%4;
  emit emit3(value3);
  check();
}


void MyPushButton::start() {
  value1 = rand()%4;
  emit emit1(value1);
  value2 = rand()%4;
  emit emit2(value2);
  value3 = rand()%4;
  emit emit3(value3);
  check();
}

void MyPushButton::reset() {
  nTriplets = 0;
  emit emit1(-1);
  emit emit2(-1);
  emit emit3(-1);
  emit sendNum(0);
}

void MyPushButton::check() {
  if (value1 == value2 and value2 == value3) {
    ++nTriplets;
    emit sendNum(nTriplets);
  }
}
