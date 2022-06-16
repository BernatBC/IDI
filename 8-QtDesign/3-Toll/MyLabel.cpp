#include "MyLabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent) {

}

void MyLabel::newTruck() {
  if (open) {
    money += 4;
    displayMoney();
  }
}

void MyLabel::newCarMoto() {
  if (open) {
    ++money;
    displayMoney();
  }
}

void MyLabel::addVehicle() {
  if (open) {
    ++vehicles;
    setNum(vehicles);
  }
}

void MyLabel::openBarrier() {
  setStyleSheet("background-color: green");
  setText("OPENED");
}

void MyLabel::closeBarrier() {
  setStyleSheet("background-color: red");
  setText("CLOSED");
}

void MyLabel::setOpen() {
    open = true;
}

void MyLabel::setClose() {
    open = false;
}

void MyLabel::displayMoney() {
  setText(QString::number(money)+"€");
}
