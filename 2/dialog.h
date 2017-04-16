#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

class Dialog : public QWidget
{
    Q_OBJECT

    QLineEdit* m_first_name;
    QLineEdit* m_last_name;
    QRadioButton* btnMale;
    QRadioButton* btnFemale;
    QCheckBox* btnOne;
    QCheckBox* btnTwo;
    QCheckBox* btnThree;
    QPushButton* m_btnUpdate;
    QPushButton* m_btnExit;

    void firstInputLayout(QHBoxLayout*);
    void secondInputLayout(QHBoxLayout*);
    void sexWidget(QGroupBox*);
    void checkBoxesLayout(QHBoxLayout*);
    void buttonsLayout(QHBoxLayout*);
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void update();
};

#endif // DIALOG_H
