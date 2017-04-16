#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Dialog");
//  the main layout
    QVBoxLayout* main = new QVBoxLayout(this);
//  other layouts
    QHBoxLayout *firstInput = new QHBoxLayout;
    QHBoxLayout *secondInput = new QHBoxLayout;
    QGroupBox *sex = new QGroupBox("&Sex");
    QHBoxLayout *checkBoxes = new QHBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
//  set layouts and widgets
    setLayout(main);
    main->addLayout(firstInput);
    main->addLayout(secondInput);
    main->addWidget(sex);
    main->addLayout(checkBoxes);
    main->addLayout(buttons);
//  private class methods
    firstInputLayout(firstInput);
    secondInputLayout(secondInput);
    sexWidget(sex);
    checkBoxesLayout(checkBoxes);
    buttonsLayout(buttons);
//  connect signals with slots
    connect(m_btnExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_btnUpdate, SIGNAL(clicked()), this, SLOT(update()));
}

void Dialog::firstInputLayout(QHBoxLayout* firstInput){
    auto m_firstName = new QLabel("FirstName: ", this);
    m_first_name = new QLineEdit(this);
    firstInput->addWidget(m_firstName);
    firstInput->addWidget(m_first_name);
}
void Dialog::secondInputLayout(QHBoxLayout* secondInput){
    auto m_lastName = new QLabel("LastName: ", this);
    m_last_name = new QLineEdit(this);
    secondInput->addWidget(m_lastName);
    secondInput->addWidget(m_last_name);
}

void Dialog::sexWidget(QGroupBox* sex){
    btnMale = new QRadioButton("&Male", this);
    btnFemale = new QRadioButton("&Female", this);
    auto layoutOfSex = new QHBoxLayout(sex);
    layoutOfSex->addWidget(btnMale);
    layoutOfSex->addWidget(btnFemale);
    sex->setLayout(layoutOfSex);
}


void Dialog::checkBoxesLayout(QHBoxLayout* checkBoxes){
    btnOne = new QCheckBox("O&ne", this);
    btnTwo = new QCheckBox("T&wo", this);
    btnThree = new QCheckBox("Th&ree", this);
    checkBoxes->addWidget(btnOne);
    checkBoxes->addWidget(btnTwo);
    checkBoxes->addWidget(btnThree);
}

void Dialog::buttonsLayout(QHBoxLayout* buttons){
    m_btnUpdate = new QPushButton("&Update", this);
    m_btnExit = new QPushButton("&Exit", this);
    buttons->addWidget(m_btnUpdate);
    buttons->addWidget(m_btnExit);
}

void Dialog::update(){
    m_first_name->setText("Vasya");
    m_last_name->setText("Pupkin");
    btnMale->setChecked(true);
    btnOne->setChecked(false);
    btnTwo->setChecked(false);
    btnThree->setChecked(false);
}

Dialog::~Dialog()
{

}
