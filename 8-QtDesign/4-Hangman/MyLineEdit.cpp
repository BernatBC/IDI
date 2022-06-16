#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget *parent):QLineEdit(parent) {
  emit sendNumber(errors);
}

bool MyLineEdit::checkRepeated(char letter) {
  for (int i = 0; i < letterEntered.size(); ++i) if (letterEntered.toStdString()[i] == letter) return true;
  letterEntered += letter;
  return false;
}

void MyLineEdit::enterLetter() {
  char inserted = text().toStdString()[0];
  backspace();
  if (errors <= 0 or checkRepeated(inserted)) return;

  bool selected = false;
  for (int i = 0; i < word; ++i) {
    if (word.toStdString()[i] == inserted or word.toStdString()[i] - 'A' + 'a' == inserted) {
      guessed[i] = word[i];
      selected = true;
    }
  }
  if (not selected) --errors;

  emit sendNumber(errors);
  emit sendWord(guessed);
}

void MyLineEdit::reset() {
  errors = 5;
  guessed = "**********";
  letterEntered = "";
  emit sendNumber(errors);
  emit sendWord(guessed);
}
