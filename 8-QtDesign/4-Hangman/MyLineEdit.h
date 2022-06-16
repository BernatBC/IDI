#include <QLineEdit>
#include <iostream>
#include <vector>

class MyLineEdit: public QLineEdit {
  Q_OBJECT

  public:
    MyLineEdit(QWidget *parent);

  private:
    int errors = 5;
    QString word = "DICCIONARI";
    QString guessed = "**********";
    QString letterEntered;

    bool checkRepeated(char letter);

  public slots:
    void enterLetter();
    void reset();

  signals:
    void sendNumber(int);
    void sendWord(QString);
};
