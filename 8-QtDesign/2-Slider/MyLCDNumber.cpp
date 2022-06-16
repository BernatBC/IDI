#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent):QLCDNumber(parent) {

}

void MyLCDNumber::set_value_colored(int num) {
  if (not num) setStyleSheet("color: green");
  else if (num%2) setStyleSheet("color: blue");
  else setStyleSheet("color: red");

  display(num);
}

void MyLCDNumber::clear_LCD() {
  setStyleSheet("color: green");
  display(0);
}
