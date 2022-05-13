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

    for (int i = 0; i < NumDigitButtons; ++i)
        for (int j = 0; j < NumDigitButtons; ++j){
            fields[i][j] = createButton(QString::number(0), SLOT(ButtonClicked()));
            fields[i][j]->x = i;
            fields[i][j]->y = j;
        }


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    for (int i = 0; i < NumDigitButtons; ++i) {
        for (int j = 0; j < NumDigitButtons; ++j)
        mainLayout->addWidget(fields[i][j], i, j);
    }
    GenerateMap();

    setLayout(mainLayout);

    setWindowTitle(tr("Saper"));
}

void MainWindow::RandValues ()
{
    time_t t;
    int poz_x, poz_y;
    int ilosc = 10;

    srand((unsigned)time(&t));

    while (ilosc>0)
    {
        poz_x = rand()%10;
        poz_y = rand()%10;

        if (fields[poz_x][poz_y]->value!=9)
        {
            SetMine(poz_x,poz_y);
            ilosc--;
        }
    }
}

void MainWindow::GenerateMap(){
    RandValues();
}

void MainWindow::ShowFields(int x, int y)
{
    if (x<0 || x>9) return; // poza tablicą wyjście
    if (y<0 || y>9) return; // poza tablicą wyjście
    if (fields[x][y]->is_Visible==true) return;  // już odkryte wyjście

    if(fields[x][y]->value!=9 && fields[x][y]->is_Visible==false)
    {
        fields[x][y]->is_Visible=true;   // odkryj!
        QString s = QString::number(fields[x][y]->value);
        fields[x][y]->setText(s);
    }
    if (fields[x][y]->value!=0) return; // wartość > 0 wyjście

    //wywołanie funkcji dla każdego sąsiada
    ShowFields(x-1,y-1);
    ShowFields(x-1,y);
    ShowFields(x-1,y+1);
    ShowFields(x+1,y-1);
    ShowFields(x+1,y);
    ShowFields(x+1,y+1);
    ShowFields(x,y-1);
    ShowFields(x,y);
    ShowFields(x,y+1);
}

bool MainWindow::SetMine(int poz_x, int poz_y)
{
    if (fields[poz_x][poz_y]->value!=9)
    {
        fields[poz_x][poz_y]->value = 9; //ustawiamy mine

        for (int k = -1; k<2; k++)
            for (int l = -1; l<2; l++)
            {
                if ((poz_x+l)<0 || (poz_y+k)<0 ) continue; //wyjdz bo krawedz
                if ((poz_x+l)>9 || (poz_y+k)>9 ) continue; //wyjdz bo krawedz

                if (fields[poz_x+l][poz_y+k]->value==9) continue; //wyjdz bo mina
                if (fields[poz_x+l][poz_y+k]->value>9) continue; //wyjdz bo jeblo
                fields[poz_x+l][poz_y+k]->value += 1; //zwieksz o 1
            }
    }

    return true;
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
    QString s = QString::number(clickedButton->value);
    clickedButton->setText(s);
    if(clickedButton->value == 9){
        QPixmap pixmap("C:/Users/Lab_admin/Documents/saper/bomb.png");
        QIcon ButtonIcon(pixmap);
        clickedButton->setIcon(ButtonIcon);
    }
    ShowFields(clickedButton->x, clickedButton->y);
}
