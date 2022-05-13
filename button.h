#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

//! [0]
class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = nullptr);
    QSize sizeHint() const override;
    bool is_Visible;
    int value;
    int x,y;
};
//! [0]

#endif
