#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include "ChatWindow.h"
#include "ConnectWindow.h"
#include "DisconnectedWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
 public:

    ChatWindow *chat;
    ConnectWindow *connect;
    DisconnectedWindow *disconnect;
    void delay();
    void chatFrame();
    void connectFrame();
    void disconnectFrame();
    void aboutBox();
    void helpBox();
     
    MainWindow(QWidget *parent=0);

    private slots:

    
};
