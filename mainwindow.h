#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void GenerateMap();
    void RandValues();
    bool SetMine(int poz_x, int poz_y);
    void ShowFields(int, int);


private slots:
    void ButtonClicked();

private:
    Button *createButton(const QString &text, const char *member);
    QLineEdit *display;
    enum { NumDigitButtons = 10 };
    Button *fields[NumDigitButtons][NumDigitButtons];

};
#endif // MAINWINDOW_H
