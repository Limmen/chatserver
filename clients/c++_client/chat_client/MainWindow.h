#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include "ChatWindow.h"
#include "ConnectWindow.h"
#include "DisconnectedWindow.h"
#include <QAction>
class MainWindow : public QMainWindow
{
    Q_OBJECT
 public:

    QAction *help;
    ChatWindow *chat;
    ConnectWindow *connect_window;
    DisconnectedWindow *disconnect;
    void delay();
    void chatFrame();
    void connectFrame();
    void disconnectFrame();
     
    MainWindow(QWidget *parent=0);

    private slots:
        void helpBox();
        void aboutBox(); 
    
};

#endif
