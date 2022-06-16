#include <QLabel>

class MyLabel: public QLabel {
  Q_OBJECT

  public:
    MyLabel(QWidget *parent);

  private:
    int num = 0;
    QString original_text = "";
    QString truncked_text = "";

    void send_string();

  public slots:
    void saveInteger(int);
    void saveString(QString);

  signals:
    void updateString(const QString &);
};
