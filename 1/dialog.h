#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Dialog : public QWidget
{
    Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
};

#endif // DIALOG_H
