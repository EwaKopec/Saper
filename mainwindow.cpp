#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(30);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons*NumDigitButtons; ++i)
        fields[i] = createButton(QString::number(0), SLOT(ButtonClicked()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    for (int i = 0; i < NumDigitButtons*NumDigitButtons; ++i) {
        int row = std::floor(i/NumDigitButtons);
        int column = i%NumDigitButtons;
        mainLayout->addWidget(fields[i], row, column);
    }
    setLayout(mainLayout);

    setWindowTitle(tr("Saper"));
}

Button *MainWindow::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


void MainWindow::ButtonClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    clickedButton->setText("1");
}
