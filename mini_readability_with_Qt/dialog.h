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
#include <QTextEdit>

class Dialog : public QWidget
{
    Q_OBJECT

    QLineEdit* m_url;
    QRadioButton* btnHttp;
    QRadioButton* btnHttps;
    QTextEdit* textFromUrl;
    QPushButton* m_btnGetText;
    QPushButton* m_btnClear;
    QPushButton* m_btnExit;

    void inputLayout(QHBoxLayout*);
    void protocolWidget(QGroupBox*);
    void textLayout(QVBoxLayout* text);
    void buttonsLayout(QHBoxLayout*);
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void clearText();
    void getText();
};

#endif // DIALOG_H
