#include "dialog.h"
#include "make_full_html_file.h"
#include "html_parser.h"
#include <fstream>
#include <cstdio>


Dialog::Dialog(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Readability");
//  the main layout
    QVBoxLayout* main = new QVBoxLayout(this);
//  other layouts
    QHBoxLayout *input = new QHBoxLayout;
    QGroupBox *protocol = new QGroupBox("&Protocol");
    QVBoxLayout *text = new QVBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
//  set layouts and widgets
    setLayout(main);
    main->addLayout(input);
    main->addWidget(protocol);
    main->addLayout(text);
    main->addLayout(buttons);
//  private class methods
    inputLayout(input);
    protocolWidget(protocol);
    textLayout(text);
    buttonsLayout(buttons);
//  connect signals with slots
    connect(m_btnExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_btnClear, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(m_btnGetText, SIGNAL(clicked()), this, SLOT(getText()));
}

void Dialog::inputLayout(QHBoxLayout* firstInput){
    auto m_url_ = new QLabel("URL: ", this);
    m_url = new QLineEdit(this);
    firstInput->addWidget(m_url_);
    firstInput->addWidget(m_url);
}

void Dialog::protocolWidget(QGroupBox* sex){
    btnHttp = new QRadioButton("&Http", this);
    btnHttps = new QRadioButton("Http&s", this);
    auto layoutOfSex = new QHBoxLayout(sex);
    layoutOfSex->addWidget(btnHttp);
    layoutOfSex->addWidget(btnHttps);
    sex->setLayout(layoutOfSex);
}

void Dialog::textLayout(QVBoxLayout* text){
    auto labelText = new QLabel("Text: ", this);
    textFromUrl = new QTextEdit(this);
    text->addWidget(labelText);
    text->addWidget(textFromUrl);
}

void Dialog::buttonsLayout(QHBoxLayout* buttons){
    m_btnGetText = new QPushButton("&Get text", this);
    m_btnClear = new QPushButton("&Clear", this);
    m_btnExit = new QPushButton("&Exit", this);
    buttons->addWidget(m_btnGetText);
    buttons->addWidget(m_btnClear);
    buttons->addWidget(m_btnExit);
}

void Dialog::clearText(){
    m_url->clear();
    textFromUrl->clear();
}

void Dialog::getText(){
    string url(m_url->text().toStdString());
    string protocol;
    if (btnHttp->isChecked()){
        protocol = "http";
    }
    else{
        if (btnHttps->isChecked()){
            protocol = "https";
        }
        else{
            textFromUrl->setText("Select protocol");
            return;
        }
    }
    try{
        MakeFullHtmlFile a(url, protocol);
        HtmlParser parser(a.getFile());
        QString text(parser.getClTextWithoutLineBreaks().c_str());
        textFromUrl->setText(text);
        remove(a.getFile().c_str());
    }
    catch(std::exception&){
        textFromUrl->setText("Некорректный URL");
    }
}

Dialog::~Dialog()
{

}
