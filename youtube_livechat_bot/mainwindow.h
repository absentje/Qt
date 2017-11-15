#include <QtWidgets>
#include <thread>
#include <memory>

QT_BEGIN_NAMESPACE
class QWebEngineView;
class QLineEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);
    ~MainWindow();

protected slots:
    void adjustLocation();
    void changeLocation();
    void setProgress(int p);
    void finishLoading(bool);

    void viewSource();

    void startBot();
    void endBot();
public:
    void thread_loop();
private:
    void setWindowTitle_();
    void postKeyDownMessage(WPARAM wParam_Key);
    void sendVKMessage(QString message = "message");
    void sendMessageToLiveChatYoutube(QString message = "message");

    HWND hWnd;
    std::thread OurThread;
    bool bIsActiveBot;

    QString jQuery;
    QWebEngineView *view;
    QLineEdit *locationEdit;
    QAction *rotateAction;
    int progress;
};
