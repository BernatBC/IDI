#include "MyLabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent) {
  //connect(this,SIGNAL(updateString()),this,SLOT(saveString()));
    //connect(this,SIGNAL(updateString()),this,SLOT(saveInteger()));
}

void MyLabel::send_string() {
  truncked_text = original_text;
  truncked_text.truncate(original_text.size() - num);
  setText(truncked_text);
}

void MyLabel::saveString(QString received_text) {
  original_text = received_text;
  send_string();
}

void MyLabel::saveInteger(int received_num) {
  num = received_num;
  send_string();
}
