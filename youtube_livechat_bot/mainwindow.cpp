#include <QtWidgets>
#include <QtWebEngineWidgets>

#include "mainwindow.h"
#include <chrono>
#include <thread>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include <functional>

using namespace std::chrono_literals;
using std::this_thread::sleep_for;

const char CLASS_NAME_OF_WINDOW[] = "Qt5QWindowIcon";

template<typename Arg, typename R, typename C>
struct InvokeWrapper {
    R *receiver;
    void (C::*memberFun)(Arg);
    void operator()(Arg result) {
        (receiver->*memberFun)(result);
    }
};

template<typename Arg, typename R, typename C>
InvokeWrapper<Arg, R, C> invoke(R *receiver, void (C::*memberFun)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = {receiver, memberFun};
    return wrapper;
}

void MainWindow::viewSource()
{
    QTextEdit* textEdit = new QTextEdit(NULL);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->adjustSize();
    textEdit->move(this->geometry().center() - textEdit->rect().center());
    textEdit->show();

    view->page()->toHtml(invoke(textEdit, &QTextEdit::setPlainText));
}

void MainWindow::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void MainWindow::changeLocation()
{
    QUrl url = QUrl::fromUserInput(locationEdit->text());
    view->load(url);
    view->setFocus();
}

void MainWindow::setProgress(int p)
{
    progress = p;
}

void MainWindow::finishLoading(bool)
{
    progress = 100;
    view->page()->runJavaScript(jQuery);
}

void KeySpacePress(){
    BYTE keyState[256];

    GetKeyboardState((LPBYTE)&keyState);
    if ((true && !(keyState[VK_SPACE] & 1)) ||
        (!true && (keyState[VK_SPACE] & 1)))
    {
        // Simulate a key press
        keybd_event(VK_SPACE,
            0x45,
            KEYEVENTF_EXTENDEDKEY | 0,
            0);
    }
}

MainWindow::MainWindow(const QUrl& url):
    OurThread(std::bind(&MainWindow::thread_loop, this)),
    bIsActiveBot(false)
{
    setWindowTitle_();
    hWnd = FindWindowA(CLASS_NAME_OF_WINDOW, windowTitle().toUtf8());

    setAttribute(Qt::WA_DeleteOnClose, true);
    progress = 0;

    // jQuery
    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();

    view = new QWebEngineView(this);
    view->load(url);
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebEnginePage::Back));
    toolBar->addAction(view->pageAction(QWebEnginePage::Forward));
    toolBar->addAction(view->pageAction(QWebEnginePage::Reload));
    toolBar->addAction(view->pageAction(QWebEnginePage::Stop));
    toolBar->addWidget(locationEdit);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    QAction* viewSourceAction = new QAction("Page Source", this);
    connect(viewSourceAction, SIGNAL(triggered()), SLOT(viewSource()));
    viewMenu->addAction(viewSourceAction);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(tr("Start Bot"), this, SLOT(startBot()));
    toolsMenu->addAction(tr("End Bot"), this, SLOT(endBot()));
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    OurThread.detach();
}

void MainWindow::startBot()
{
    bIsActiveBot = true;
}

void MainWindow::endBot()
{
    bIsActiveBot = false;
}

void MainWindow::setWindowTitle_()
{
    while(true){
        srand(time(0));
        int i = 100 + rand() % 999;
        const QString BASE_NAME_OF_WINDOW("QtWebWindow");
        HWND hWnd = FindWindowA(CLASS_NAME_OF_WINDOW,
                                (BASE_NAME_OF_WINDOW + QString::number(i)).toUtf8());
        if(!hWnd){
            setWindowTitle(BASE_NAME_OF_WINDOW + QString::number(i));
            break;
        }
    }
}

void MainWindow::thread_loop()
{
    while (true){
        if (bIsActiveBot){
            sendMessageToLiveChatYoutube("Hello, guys!!!");
        }
        sleep_for(5s);
    }
}

void MainWindow::sendVKMessage(QString message)
{
    QString code1 = QString("qt.jQuery(\"[class='im_editable im-chat-input--text _im_text']\").text('")
                    + message + QString("');");

    view->page()->runJavaScript(code1);

    sleep_for(1s);
    QString code2 = "qt.jQuery(\"[class='im_editable im-chat-input--text _im_text']\").focus();";
    view->page()->runJavaScript(code2);

    sleep_for(1s);
    postKeyDownMessage(VK_RETURN);
}

void MainWindow::sendMessageToLiveChatYoutube(QString message)
{
    //  Add message on tag
    QString code1 = QString("qt.jQuery(\"[class='style-scope yt-live-chat-text-input-field-renderer style-scope yt-live-chat-text-input-field-renderer']\").text('")
                    + message + QString("');");
    view->page()->runJavaScript(code1);

    sleep_for(1s);
    //  Focus on text box
    QString code2 = "qt.jQuery(\"[class='style-scope yt-live-chat-text-input-field-renderer style-scope yt-live-chat-text-input-field-renderer']\").focus();";
    view->page()->runJavaScript(code2);

    sleep_for(1s);

    //  Press SpaceKey
    postKeyDownMessage(VK_SPACE);

    sleep_for(1s);

    //  Press EnterKey
    postKeyDownMessage(VK_RETURN);
}

void MainWindow::postKeyDownMessage(WPARAM wParam_Key)
{
    if (!hWnd) {
        hWnd = FindWindowA(CLASS_NAME_OF_WINDOW, windowTitle().toUtf8());
    }
    if (hWnd) {
        PostMessage(hWnd, WM_KEYDOWN, wParam_Key, 0);
    }
}





