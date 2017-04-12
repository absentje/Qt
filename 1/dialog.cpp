#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <iostream>

Dialog::Dialog(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* main = new QVBoxLayout(this);

    QHBoxLayout *input = new QHBoxLayout(this);
    QHBoxLayout *buttons = new QHBoxLayout(this);

    main->addLayout(input);
    main->addLayout(buttons);

    auto m_Name = new QLabel("Name: ", this);
    auto m_name = new QLineEdit(this);
    auto m_btnOk = new QPushButton("OK", this);
    auto m_btnExit = new QPushButton("Exit", this);
    m_Name->setMaximumSize(QSize(150, 100));
    input->addWidget(m_Name);
    input->addWidget(m_name);
    buttons->addWidget(m_btnOk);
    buttons->addWidget(m_btnExit);
    main->addLayout(input);
    main->addLayout(buttons);
    connect(m_btnExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_btnOk, SIGNAL(clicked()), m_name, SLOT(clear()));
    setLayout(main);
}

Dialog::~Dialog()
{

}
